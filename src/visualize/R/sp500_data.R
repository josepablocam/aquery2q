# Collect data on SP500 constituents
.libPaths(c("../Rdeps", .libPaths()))
library(quantmod)
library(plyr)
START_DATE <- as.Date("2000-01-01")
END_DATE <- as.Date("2016-01-08")
SRC <- "yahoo"
tickers <- as.character(read.csv("../data/sp500_tickers.csv")$Ticker)
sp500 <- new.env()

# Following the approach in http://statmath.wu.ac.at/~hornik/QFS1/quantmod-vignette.pdf
wrapped_download <- function(sym, env) {
    status <- tryCatch(getSymbols(sym, env = env, src = SRC, from = START_DATE, to = END_DATE),
                       error = identity)
     if(inherits(status, "error")) {
       cat("Symbol '", sym, "' failed\n", sep = "")
     }
}
  
# Download data using wrapper  
for(sym in tickers) {
   wrapped_download(sym, sp500)
}

clean_col_names <- function(x) sub("[A-Za-z]+\\.", "", x)

dat <- lapply(ls(sp500), function(x) {
   d <- as.data.frame(sp500[[x]])
   d$ID <- x
   d$Date <- row.names(d)
   names(d) <- clean_col_names(names(d))
   d
})

dat <- do.call(rbind, dat)
#write.csv(dat, file = "../data/sp500_eod.csv", row.names = FALSE)


# We want tickers that have all the dates (complete time series)
cts <- ddply(dat, .(ID), summarize, ct = length(Volume))
cts <- cts[order(-cts$ct), ]

# Complete data subset
complete_syms <- with(cts, ID[ct == max(ct)])
complete_dat <- subset(dat, ID %in% complete_syms)
write.csv(complete_dat, file = "../data/sp500_eod_complete_data.csv", row.names = FALSE)




