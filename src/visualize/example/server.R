library(shiny)
library(ggplot2)


# Load q server functionality
source("../qserver.R", chdir = TRUE)


# server logic for plotting tool
shinyServer(function(input, output) {

  # Collect info about q connection from user input and create handle
  qHandle <- reactive({
    host <- input$host
    port <- input$port
    open_connection(host, port)
  })

  aqQuery <- reactive({
    input$query
  })
  
  # default data frame in case not connected when launched
  # or provided q/aquery command that doesn't return a table
  # (i.e. not plottable as default)
  default_data <- data.frame(c1 = c(1,2,3), c2 = c(10, 20, 30))
  
  output$plot <- renderPlot({
    # TODO: display error message if connection doesn't work
    h <- qHandle()
    dat <- tryCatch(execute(h, aqQuery()), error = function(e) {
        print(paste("Caught error, using default dataframe: ", e))
        default_data
     })
    
    # Default to dummy data if query result is not a dataframe
    if(!is.data.frame(dat)) {
      dat <- default_data
    }
      
    # for POC we assume the first column is x-axs and everything else is to 
    # be plotted as a separate series
    cols <- names(dat)
    base_plot <- ggplot(data = dat, aes_string(x = cols[1]))
    
    if(input$geom == "bar") {
        add_ys_plot(base_plot, geom_bar, cols)
      } else {
        add_ys_plot(base_plot, geom_line, cols)
      }
    })

 })

# Some helper functions
add_ys_plot <- function(p, geom, cols) {
  # ugly hack until I figure out aes_string
  colors <- c("red", "blue", "yellow", "green", "black")
  for (i in 2:length(cols)) {
    col <- cols[i]
    p <- p + geom(aes_string(y = col), fill = colors[i-1], stat = "identity", position = "dodge")
  }
  p
}
                  

