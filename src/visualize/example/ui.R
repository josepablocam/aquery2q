# update library path to include dependencies folder 
# necessary for systems without packages by default (.e.g CIMS machines)
.libPaths(c('./Rdeps',.libPaths()))
library(shiny)

# Define UI for application
shinyUI(fluidPage(

  # Application title
  titlePanel("Simple AQuery visualization"),

  
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
                  choices = c("dot", "line", "bar", "histo", "area", "boxplot"), "dot"
      ),
      
      # Using column values to group in plotting
      checkboxGroupInput("groupcols", label = h4("Group Columns"), 
                         choices = list("Choice 1" = 1, "Choice 2" = 2, "Choice 3" = 3),
                         selected = 1),
      
      actionButton("query_button", "Query"),
       # plotting button
      submitButton("plot")
      
    ),
    

    # Show a plot of the generated distribution
    mainPanel(
      plotOutput("plot"),
      downloadButton("save_plot"),
      tableOutput("data")
    )
  )
))
