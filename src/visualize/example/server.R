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
      
    # for POC we assume the first column is x-axis
    # and second column is y-axis
    x <- dat[,1]
    y <- dat[,2]
    if(input$geom == "bar") {
        qplot(x = x, y = y, geom = "bar", stat = "identity")
      } else {
        qplot(x = x, y = y, geom = "line")
      }
    })

 })
