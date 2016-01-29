repos=c("http://cran.r-project.org" , "https://cran.rstudio.com/")
folder = "../Rdeps"
# ggplot2 dependencies, not downloading even though dependencies = TRUE
install.packages("ggplot2", repos = repos, lib = folder, dependencies = TRUE)
install.packages("digest", repos = repos, lib = folder, dependencies = TRUE)
install.packages("gtable", repos = repos, lib = folder, dependencies = TRUE)
install.packages("MASS", repos = repos, lib = folder, dependencies = TRUE)
install.packages("plyr", repos = repos, lib = folder, dependencies = TRUE)
install.packages("reshape2", repos = repos, lib = folder, dependencies = TRUE)
install.packages("scales", repos = repos, lib = folder, dependencies = TRUE)
install.packages("proto", repos = repos, lib = folder, dependencies = TRUE)
install.packages("stringr", repos = repos, lib = folder, dependencies = TRUE)
install.packages("munsell", repos = repos, lib = folder, dependencies = TRUE)
install.packages("labeling", repos = repos, lib = folder, dependencies = TRUE)
install.packages("colorspace", repos = repos, lib = folder, dependencies = TRUE)

# shiny dependencies, not downloading even though dependencies = TRUE
install.packages("shiny",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("methods",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("utils",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("httpuv",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("mime",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("jsonlite",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("xtable",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("htmltools",  repos = repos, lib = folder, dependencies = TRUE)
install.packages("R6",  repos = repos, lib = folder, dependencies = TRUE)

# install shiny ace
install.packages("shinyAce", repos = repos, lib = folder, dependencies = TRUE)

install.packages("Rcpp",  repos = repos, lib = folder, dependencies = TRUE)


# install quantmod
install.packages("quantmod", repos = repos, lib = folder, dependencies = TRUE)




