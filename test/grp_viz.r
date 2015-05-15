library(plyr)
library(ggplot2)
setwd("/Users/josecambronero/MS/S15/aquery/test")
data <- read.csv("group_sorting.csv")
data$nr <- data$nr / 1e6
data$ngrps <- as.factor(data$ngrps)

full_graph <- ggplot(data = data, aes(x = ngrps, y = time, group = strat)) + 
  geom_line(aes(color = strat)) + 
  facet_wrap( ~  nc, scales="free_y") +
  theme(axis.text.x = element_text(angle = 90)) +
  labs(x = "# of groups", y = "running time (ms)", title="Full comparison: Note cases w/ group # >=10k")

reduced_graph <- full_graph %+% subset(data, !ngrps %in% c("100000","1000000"))
reduced_graph <- reduced_graph + labs(title="Reduced comparison,excludes cases with >10k groups")
                                       
pdf(file = "/Users/josecambronero/MS/S15/aquery/test/grp_viz.pdf")                                     
print(full_graph)
print(reduced_graph)
dev.off()
