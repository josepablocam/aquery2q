# Create AQuery queries based on user input from R

# Formatting function helpers according to how q process likes constants
format_float <- function(x) sprintf("%.2f", x)
format_int <- function(x) sprintf("%d", x)
format_date <- function(x) format(x, "%Y.%m.%d")
format_sym <- function(x) sprintf("`%s", x)


PERFECT_STRATEGY <- 3
perfect_params <- function(ticker, amt, dateRange) {
  ticker <- format_sym(ticker)
  amt <- format_float(amt)
  startDate <- format_date(dateRange[1])
  endDate <- format_date(dateRange[2])
  parameters <- sprintf("ticker:{%s}; amt:{%s}; startDate:{%s}; endDate:{%s};", ticker, amt, startDate, endDate)
  parameters
}

BUY_CHEAP_STRATEGY <- 4
buy_cheap_params <- function(amt, startDate, threshold, period) {
  # format string parameters appropriately
  amt <- format_float(amt)
  startDate <- format_date(startDate)
  threshold <- format_float(threshold)
  period <- format_int(period)
  
  # create command to replace parameters
  parameters <- sprintf("amt:{%s}; startDate:{%s}; returns_threshold:{%s};holding_period:{%s};",
                        amt, startDate, threshold, period)
  parameters
}
  
TECHNICAL_STRATEGY <- 5
technical_params <- function(ticker, amt, dateRange, windowsRange) {
  ticker <- format_sym(ticker)
  amt <- format_float(amt)
  startDate <- format_date(dateRange[1])
  endDate <- format_date(dateRange[2])
  shortWindow <- format_int(windowsRange[1])
  longWindow <- format_int(windowsRange[2])
  parameters <- sprintf("ticker:{%s}; amt:{%s}; startDate:{%s}; endDate:{%s}; 
                        short_window:{%s}; long_window:{%s};", 
                        ticker, amt, startDate, endDate, shortWindow, longWindow)
  parameters
}

PAIRS_STRATEGY <- 6
pairs_params <- function(ticker, buyTicker, amt, startDate, holdPeriod, minCorr, lenBefore, lenAfter) {
 ticker <- format_sym(ticker)
 buyTicker <- format_sym(buyTicker)
 amt <- format_float(amt)
 startDate <- format_date(startDate)
 holdPeriod <- format_int(holdPeriod)
 minCorr <- format_float(minCorr)
 lenBefore <- format_int(lenBefore)
 lenAfter <- format_int(lenAfter)
 parameters <- sprintf("ticker:{%s}; buyTicker:{%s}; amt:{%s};
    startDate:{%s}; holdPeriod:{%s}; minCorr:{%s}; lenBefore:{%s};
    lenAfter:{%s};", ticker, buyTicker, amt, startDate, holdPeriod,
                       minCorr, lenBefore, lenAfter)
 
 parameters
}
  
  
  
  