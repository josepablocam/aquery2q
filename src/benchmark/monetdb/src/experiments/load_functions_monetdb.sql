/*
	define embedded python functions needed for quantiles
*/


CREATE FUNCTION quantile(v double, q double) RETURNS double LANGUAGE PYTHON {
	return numpy.percentile(v, q)
};
