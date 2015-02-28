/*
	This file contains functions necessary for aquery optimizations
*/

/*
	Optim 1: sorting only necessary columns


obs: we only sort expressions that are order dependent
obs: all top level results in a projection are assumed to be order dependent
	Meaning, we should make sure the resulting expressions are sorted....
obs: once sorted a column remains sorted....
obs: we want to delay sorts to after selections, so if we need to sort for filtering
	we only want to sort those columns that are necessary


Possible strategies:
1 - update all columns that ever require order to their sorted variants
	--> downside: also need to update any columns that they interact with,
		which might otherwise not been sorted, if the other columns had not been updated
	---> upside: avoid reindexing when unnecessary
2 - apply indices in each location when needed
	--> downside: reindexing into the same columns over and over 

		consider:
			prev(c2) = 1, c3 = max(c1 + c2)
	  			--> the prev(c2) means we have to sort c2
				--> assume c2:sort(c2)
				--> now, for c1 + c2 to yield the same result, we need to sort(c1) (c1:sort(c1))
				--> the comparison with c3 yields a boolean vector, which needs to be
					aligned with that of prev(c2) = 1, so  we need to sort c3 (c3:sort(c3))
				--> we performed 3 sorts total
		vs
			--> we use indices to index c2 and apply sort and comparison
			--> we now add c1 and c2 (neither of which is sorted) and apply max
			--> we apply sorting indices to c3 and perform the comparison
			--> we performed 2 sorts total (using indices)

However, if column c2 was used heavily in expressions that required order, then
	we would have repeatedly indexed into the same values over and over....


Option 2 also requires only local knowledge...I know what I need to sort based solely on my
	parent's info and my own...
Option 1 requires global knowledge (does columnX ever interact with a sorted columnY, if so I need to sort as well...)


2 possible ways to sort


obs: for where statements, if we sort the results of one column, we need to sort others, or revert to original sorting, because booleans need to line up
obs: a similar statement is true for grouping as well

There are 2 options in general to handle the above:
	- desort sorted calculations
	- sort everything else....

And we still need to desort certain things, for example where expression needs to be de_sorted



Approach
	When building from bottom up, every expression is marked as OD, and only becomes OI if there is an OI operator applied to it. At every parent node, we take OD if either child is OD, otherwise it is OI.


New strategy:
	- for filter_where, we solely sort if necessary (and directly indexing), and de sort at end 
	- if there is a group-by
			if group-by is OI and projection is OI (ie only aggregates)
					no sort necessary
			if group-by is OD or projection is OD
				- calculate sorting index
				- sort all columns referenced with an update (we want to align data)
	-if there is no group-by
		- each projection expression should be analyzed separately by traversing the tree
		 and indexing directly. Assume when entering tree that you need to sort
		any column found. Continue assuming this until you hit an annihilator, in which case	don't sort anything until you hit another OD node.....

	In projection, to figure out if it is order dependent or not,
	it is not enough to check the tyep of the head node
	because consider that c1 + c2 is usually marked as order independent
	except that in a projection c1 + c2 the order matters. So we must
	count any references to columns that occur in a tree not associated
	with an order-independent operator....




for projection OI means every expression is OI, so top nodes are things like
max(c1) *  min(c2), avg(c4)



Create a new query plan node
compute_sort_ix takes order and table, and just returns table, and assigns a value to sort_ix as a side effect and a value to desort_ix, after that we can use both freely
so a query plan could be 
table -> compute_sort_ix -> filter(expressions) -> group_by(expressions) -> 



---->
if group-by
	if group-by order dependent || projection order dependent
			find all referenced cols (not just those that are order dependent) and sort them
	else
			nothing to do :)
else
	if projection order-dependent
		find all order-dependent cols using similar pattern as in where, but instead of indexing, return list, create sort update and then compute
	else
		nothing to do :)


Argument for why group-by complicates:
	assume we group. Now assume a projection expression e_1 is OD. for e_1 to align correctly with groups, we need to sort groups. Which in turn means we need to sort non-OD data.
	---> conclusion: Note that the argument only relies on e_1 or g_1 being order dependent, either one messes things up.....

	




*/
#include <stdio.h>
#include "stdlib.h"
#include "aquery_types.h"
#include "ast.h"
#include "ast_print.h"


#define OPTIM_DEBUG 0
#define OPTIM_PRINT_DEBUG(str) if(OPTIM_DEBUG) printf("---->OPTIM DEBUGGING: %s\n", str)
#define OPTIM_1 1

extern const char *ExprNodeTypeName[];

int is_sortable(ExprNodeType type)
{ //can we sort this
	OPTIM_PRINT_DEBUG("checking sortability");
	return type == ID_EXPR || type == ROWID_EXPR || type == COLDOTACCESS_EXPR;
}

/* only sorting what is necessary: optim 1 */
ExprNode *make_singleColSort(ExprNode *expr)
{
	OPTIM_PRINT_DEBUG("making single column sort");
	ExprNode *new_node = make_EmptyExprNode(SINGLE_COL_IX_SORT);
	new_node->first_child = make_EmptyExprNode(SORT_IX);
	new_node->first_child->next_sibling = expr;
	//transfer sibling relationship to indexing node
	new_node->next_sibling = expr->next_sibling;
	expr->next_sibling = NULL; 
	return new_node;
}

ExprNode *make_singleColDeSort(ExprNode *expr)
{
	OPTIM_PRINT_DEBUG("making single column sort");
	ExprNode *new_node = make_EmptyExprNode(SINGLE_COL_IX_SORT);
	new_node->first_child = make_EmptyExprNode(DE_SORT_IX);
	new_node->first_child->next_sibling = expr;
	return new_node;
}

//Sorts one column 
LogicalQueryNode *make_computeSortIx(LogicalQueryNode *ord)
{
	OPTIM_PRINT_DEBUG("making computed sorting index");
	LogicalQueryNode *ix = make_EmptyLogicalQueryNode(COMPUTE_SORT_IX);
	ix->params.order = ord->params.order;
	ix->arg = ord->arg;
	return ix;
}



// minimize sorting necessary in where clause
ExprNode *minsort_ixSortExpr(ExprNode *node, int create_ix)
{
	if(node != NULL)
	{
		OPTIM_PRINT_DEBUG("min sorting expression");
		//printf("node:type:%s\n", ExprNodeTypeName[node->node_type]);
		//printf("order dep:%d\n", node->order_dep);
		
		if(node->node_type == CALL_EXPR)
		{ //only operators can change sorting behavior
			//if we encounter a function that is order independent, we don't sort subtree for now, until we encounter a different operator
			//until we encounter a function that is order dependent
			OPTIM_PRINT_DEBUG("min sorting expression: found operator");
			create_ix = node->first_child->order_dep; 
			OPTIM_PRINT_DEBUG("explore arguments subtree");
			node->first_child = minsort_ixSortExpr(node->first_child, create_ix);
			node->next_sibling = minsort_ixSortExpr(node->next_sibling, create_ix);	
		}
		else if(is_sortable(node->node_type) && create_ix)
		{
			node = make_singleColSort(node);
			node->next_sibling = minsort_ixSortExpr(node->next_sibling, create_ix | node->order_dep);
		}
		else
		{
			OPTIM_PRINT_DEBUG("recursing sortability");
			node->first_child = minsort_ixSortExpr(node->first_child, create_ix | node->order_dep);
			node->next_sibling = minsort_ixSortExpr(node->next_sibling, create_ix | node->order_dep);
		}
		
	}
	
	return node;
}



LogicalQueryNode *minsort_where(LogicalQueryNode *where, LogicalQueryNode *order)
{ //assume there is actually an order
	
	if(where != NULL && order != NULL && where->order_dep)
	{
		OPTIM_PRINT_DEBUG("min sorting where");
		LogicalQueryNode *computing_ix = make_computeSortIx(order); //calc and store sorting indices
		where->params.exprs = minsort_ixSortExpr(where->params.exprs, 1); //sort any columns in expressions
		where->params.exprs = make_singleColDeSort(where->params.exprs); //desort final result
		where->arg = computing_ix;
		return where;
		
	}
	
	return where;
	
}

LogicalQueryNode *assemble_optim1(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
	LogicalQueryNode *plan = from;
	//removing unnecessary sorting in where
	where = minsort_where(where, order);
	plan = pushdown_logical(where, plan);
	plan = pushdown_logical(grouphaving, plan);
	return pushdown_logical(proj, plan);
	
}

LogicalQueryNode *assemble_plan(LogicalQueryNode *proj, LogicalQueryNode *from, LogicalQueryNode *order, LogicalQueryNode *where, LogicalQueryNode *grouphaving)
{
	//printf("%d\n", OPTIM_1);
	if(OPTIM_1)
	{
		return assemble_optim1(proj, from, order, where, grouphaving);
	}
	else
	{
		return assemble_base(proj, from, order, where, grouphaving);
	}
}







