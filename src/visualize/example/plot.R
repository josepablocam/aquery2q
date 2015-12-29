# Plotting utilities for visualization interface
library(ggplot2)

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
         dot = geom_point(aes_details),
         line = geom_line(aes_details),
         bar = geom_bar(aes_details, stat = "identity", position = "dodge"),
         histo = geom_histogram(aes_details, position = "dodge"),
         area = geom_area(aes_details),
         boxplot = geom_boxplot(aes_details)
  )
}
         


# Add all but first column as y series
plot_all_series <- function(p, cols, geom_name, plot_details) {
  for (i in 2:length(cols)) {
    col <- cols[i]
    plot_aes <- assemble_aes(col, plot_details)
    geom <- pick_geom(geom_name, plot_aes)
    p <- p + geom
  }
  p + labs(x = p$mapping$x, y = "y-value", color = "legend", fill = "legend")
}





