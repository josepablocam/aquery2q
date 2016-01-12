# Plotting utilities for visualization interface
library(ggplot2)
library(reshape2)

# SOME CONSTANTS USED THROUGHOUT
#possible geoms
POSS_GEOMS <- c("dot", "line", "bar", "histo", "area", "boxplot", "vline", "hline")
DEF_GEOM <- "dot"

# add aes
`+.uneval` <- function(a,b) {
  `class<-`(modifyList(a,b), "uneval")
}

# Create groups based on a list of column names
# returns a string of interactions (to be parsed by aes_string) in ggplot
groupify <- function(x) {
  combined <- paste0("interaction(", paste0(x, collapse = ","), ")")
}


# Assemble aesthetics general
assemble_aes <- function(col, details) {
  no_group <- is.null(details$group)
  if(no_group) {
    parsed_aes <- aes_q(color = col, fill = col)
  } else {
    group_str <- details$group
    parsed_aes <- aes_string(group = group_str, color = group_str, fill = group_str)
  }
  y <- as.name(col)
  aes_q(y = y) + parsed_aes
}





# pick geom along with some basic defaults
pick_geom <- function(geom_name, aes_details) {
  switch(geom_name,
         dot = geom_point(aes_details + aes_q(shape = as.character(aes_details$y))),
         line = geom_line(aes_details),
         bar = geom_bar(aes_details, stat = "identity", position = "dodge"),
         histo = geom_histogram(aes_details, position = "dodge"),
         area = geom_area(aes_details),
         boxplot = geom_boxplot(aes_details),
         vline = geom_vline(aes_string(xintercept = aes_details$y)),
         hline = geom_hline(aes_string(yintercept = aes_details$y))
  )
}
         


# Add all but first column as y series
plot_all_series <- function(p, cols, geom_names, plot_details) {
  for (i in 2:length(cols)) {
    col <- cols[i]
    geom_name <- geom_names[i-1]
    
    plot_aes <- assemble_aes(col, plot_details)
    geom <- pick_geom(geom_name, plot_aes)
    p <- p + geom
  }
  p + labs(x = p$mapping$x, y = "y-value", color = "legend", fill = "legend", shape = "legend")
}


# Plotting predefined queries
plot_predefined <- function(dat, query_num) {
  if(query_num == 0) {
    # Moving variance query
    ggplot(dat, aes(x = Date, y = mv, group = ID)) +
      geom_line(aes(group = ID, color = ID)) +
      labs(x = "Date", y = "Variance", color = "Ticker" , title = "Moving Variance Query")
  } else if(query_num == 1) {
    # Correlation pairs query
    ggplot(dat, aes(x = ID1, y = ID2)) + 
      geom_point(aes(size = coef, color = coef)) +
      labs(x = "Ticker", y = "Ticker Pair", color = "Correlation", size = "Correlation",
           title = "Returns Correlation Pairs")
  } else if (query_num == 2) {
    # Crossing moving averages query
    ggplot(dat, aes(x = Date, y = Price)) + 
      geom_line(aes(color = "Price")) +
      geom_line(aes(y = m21, color = "21-day avg")) + 
      geom_line(aes(y = m5, color = "5-day avg")) +
      geom_point(aes(y = BuySignal, color = "Buy signal", shape = "Buy signal"), size = 4) +
      geom_point(aes(y = SellSignal, color = "Sell signal", shape = "Sell signal"), size = 4) +
      labs(x = "Date", y = "Price", color = "Series", shape = "Indicators", title = "Crossing-moving averages trade")
              
  } else if (query_num == 3) {
    # Perfect knowledge trading strategy
    priceDat <- dat
    # NULL out irrelevant stuff
    priceDat$Profit <- NA
    priceDat$SeriesName <- "Price"
    # Profit Data
    profitDat <- dat
    profitDat$Price <- NA
    profitDat$BestBuyPrice <- NA
    profitDat$BestSellPrice <- NA
    profitDat$SeriesName <- "Profit"
    # Combine them into 1 data frame
    repdat <- rbind(priceDat, profitDat)
    # plot away!
    ggplot(repdat, aes(x = Date)) + 
      geom_line(aes(y = Price, color = "Price")) +
      geom_bar(aes(y = BestBuyPrice, fill = "Best buy"), stat = "identity") +
      geom_bar(aes(y = BestSellPrice, fill = "Best sell"), stat = "identity") + 
      geom_area(aes(y = Profit, fill = "Profit")) +
      facet_wrap(~ SeriesName, scales = "free_y", ncol = 1) + 
      labs(x = "Date", y = "USD", title = "Perfect knowledge trade", color = "", fill = "Indicators") + 
      theme(strip.text.x = element_blank())
  } else if (query_num == BUY_CHEAP_STRATEGY) {
    ggplot(dat, aes(x = Date, y = runningProfit)) +
      geom_line(aes(color = "Running profit/loss")) +
      labs(x = "Investment Date", y = "USD", title = "'Buy cheap' trading strategy", color = "")
  }
  else {
    print("undefined")
  }
}


