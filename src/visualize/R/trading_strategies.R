# Create AQuery queries based on user input from R

# Formatting function helpers according to how q process likes constants
format_float <- function(x) sprintf("%.2f", x)
format_int <- function(x) sprintf("%d", x)
format_date <- function(x) format(x, "%Y.%m.%d")

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
  

  
  
  