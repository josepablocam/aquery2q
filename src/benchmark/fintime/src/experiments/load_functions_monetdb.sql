/*
	define embedded python functions needed for benchmarking
*/

/*
	We implement a moving average function
	given
	https://www.monetdb.org/pipermail/users-list/2015-October/008487.html
	assumes we've sorted columns to be able to partition
	along a given column(id)
*/
-- CREATE FUNCTION mavg(v double, win integer, part char(30)) RETURNS double LANGUAGE PYTHON {
--   weights = numpy.repeat(1.0, win) / win
--   ma = numpy.zeros(numpy.size(v))
--   start = win - 1
--   ma[start:] = numpy.convolve(v, weights, 'valid')
--   # now recalc the edges of each group
--   edge = numpy.append([0], (numpy.where(part[:-1] != part[1:])[0] + 1))
--
--   for i in edge:
--     local_ix = numpy.arange(i, i + start)
--     vals = v[local_ix]
--     ma[local_ix] = numpy.cumsum(vals) / numpy.arange(1, win)
--
--   return ma
-- };

-- Similarly to the pandas case, we default to the fastest possible option
-- for calculating moving averages, meaning the semantics of mavg at positions < win
-- are that it is nan 
CREATE FUNCTION mavg(v double, win integer, part char(30)) RETURNS double LANGUAGE PYTHON {
	weights = numpy.repeat(1.0, win) / win
	ma = numpy.zeros(numpy.size(v))
	start = win - 1
	ma[start:] = numpy.convolve(v, weights, 'valid')
	# now recalc the edges of each group
	edge = numpy.append([0], (numpy.where(part[:-1] != part[1:])[0] + 1))

	for i in edge:
		local_ix = numpy.arange(i, i + start)
		ma[local_ix] = numpy.nan

	return ma	 
};

/*
	We also calculate a correlation function, as the
	builtin correlation function continues to result in the following error
	TypeException:user.s39_3[31]:'aggr.subcorr' undefined in:     X_49:bat[:oid,:dbl] := aggr.subcorr(X_45:bat[:oid,:dbl],X_48:bat[:oid,:dbl],X_37:bat[:oid,:oid],r1_37:bat[:oid,:oid],true:bit);
	program contains errors
*/
CREATE AGGREGATE pairs_corr(x double, y double) RETURNS DOUBLE LANGUAGE PYTHON {
	unique = numpy.unique(aggr_group)
	result = numpy.zeros(shape=(unique.size))
	for i in range(0, unique.size):
		v1 = x[aggr_group == unique[i]]
		v2 = y[aggr_group == unique[i]]
		result[i] = numpy.corrcoef(v1, v2)[0][1]

	return result;z
};

-- shift back, type specific
CREATE FUNCTION prev_char(id char(30)) RETURNS char(30) LANGUAGE PYTHON { 
  # using dummy string in place of none
	end = numpy.size(id) - 1
	return numpy.append('<null>', id[0:end])
 };  

CREATE FUNCTION prev_double(v double) RETURNS double LANGUAGE PYTHON {	
	end = numpy.size(v) - 1
	return numpy.append(numpy.nan, v[0:end])
}; 


CREATE AGGREGATE last_boolean(v boolean) RETURNS boolean LANGUAGE PYTHON {
	unique = numpy.unique(aggr_group)
	result = numpy.zeros(shape=(unique.size))
	for i in range(0, unique.size):
		vals = v[aggr_group == unique[i]]
		result[i] = vals[-1]
	return result
};

 
CREATE AGGREGATE execute_strategy(buy_signal boolean, px double) RETURNS double LANGUAGE PYTHON {
  # taken from definitions_pandas.py, with slight modifications
  # note that ~ and indexing directly with masked array was not working for some reason
  # in certain place
  unique = numpy.unique(aggr_group)
  result = numpy.zeros(shape=(unique.size))
  for i in range(0, unique.size):
    ix = aggr_group == unique[i]
    buy_signal_ix = buy_signal[ix]
    hasSeenBuy = numpy.cumsum(buy_signal_ix) > 0

    if (not hasSeenBuy.any()):
      result[i] = 1.0 # we never got to trade
    else:
      # make sure we copy, don't want to overwrite px
      px_ix = px[ix]
      sell = px_ix.copy()
      sell[buy_signal_ix == True] = 0.0
      # when we buy action is how many stocks can we get for the price
      buy = (1.0 / px_ix)
      buy[buy_signal_ix == False] = 0.0
      multiplier = numpy.maximum(buy, sell) # 0s will be replaced with appropriate action
      multiplier[hasSeenBuy == False] = 1.0 # if we haven't seen a buy, we stay put
      result[i] = numpy.prod(multiplier)
  return result
 };
 
 
 