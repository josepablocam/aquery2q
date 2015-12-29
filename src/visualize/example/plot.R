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


# Add all but first column as y series
add_ys_plot <- function(p, cols, geom, plot_details) {

  for (i in 2:length(cols)) {
    col <- cols[i]
    plot_aes <- assemble_aes(col, plot_details)
    p <- p + geom(plot_aes, stat = "identity", position = "dodge")
  }
  p + labs(x = "x-value", y = "y-value", color = "legend", fill = "legend")
}





