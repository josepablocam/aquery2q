# update library path to include dependencies folder 
# necessary for systems without packages by default (.e.g CIMS machines)
.libPaths(c('./Rdeps',.libPaths()))
library(shiny)

# Define UI for application
shinyUI(fluidPage(

  # Application title
  titlePanel("Proof of Concept for AQuery visualization"),

  
  # Sidebar with inputs
  sidebarLayout(
    sidebarPanel(
      # Connection information
      textInput("host", "Q connection hostname:", "localhost"),
      numericInput("port", "Q connection port number: ", 7089),
      
      # Aquery information
      textInput("query", "AQuery function wrapper or q command"),
     
      # Bar or line plot
      selectInput("geom", "Plot style:", 
                  choices = c("dot", "line"), "dot"
      ),
       # delay evaluation until user requests
      submitButton("plot")
    ),

    # Show a plot of the generated distribution
    mainPanel(
      plotOutput("plot")
    )
  )
))
