# File to read in, modify, compile and execute aquery code from the
# visual interface
AQUERY_DIR = "../aquery/"
PREDEF_FILE_NAMES <- c(NA, "moving_variance.a", "correlation_pairs.a", "moving_avgs.a", "hindsight_strategy.a",
               "buy_cheap_strategy.a", "technical_strategy.a", "pairs_strategy.a")
names(PREDEF_FILE_NAMES) <- -1:6
SOURCE_AQUERY_PATH <- paste0(AQUERY_DIR, "current.a", collapse = "/")
COMPILED_AQUERY_PATH <- paste0(AQUERY_DIR, "current.q", collapse = "/")


# to display in interface
get_code <- function(id) {
  file_name <- PREDEF_FILE_NAMES[as.character(id)]
  if(is.na(file_name)) {
    "//AQuery code here"
  } else {
    path <- paste0(AQUERY_DIR, file_name, collapse = "/")
    paste(readLines(path), collapse = "\n")
  }
}

compile <- function(code) {
  # put code into a temporary file
  file.create(SOURCE_AQUERY_PATH)
  src_file <- file(SOURCE_AQUERY_PATH, open = "wr")
  writeLines(code, con = src_file)
  close(src_file)
  system2("a2q", args = c("-c", "-a 1", "-o", COMPILED_AQUERY_PATH, SOURCE_AQUERY_PATH), stdout = TRUE)
}

compilation_ok <- function(x) { (length(x) == 0) || is.na(attr(x, "status")) }
compilation_error <- function(x) { paste(attr(x, "status")[1:2], collapse ="\n") }



         