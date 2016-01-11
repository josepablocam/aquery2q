# update library path to include dependencies folder 
# necessary for systems without packages by default (.e.g CIMS machines)
.libPaths(c('./Rdeps',.libPaths()))
library(shiny)

# Define UI for application
shinyUI(fluidPage(

  # Application title
  titlePanel("AQuery to Make Your Fortune"),

  
  # Sidebar with inputs
  sidebarLayout(
    sidebarPanel(
      # Connection information
      textInput("host", "Q connection hostname:", "localhost"),
      numericInput("port", "Q connection port number: ", 7089),
      
      # Aquery information
      textInput("query", "AQuery function wrapper or q command"),
      
      selectInput("predefined_queries", "Predefined queries",
                  choices = list("None" = -1,
                        "Moving Variance" = 0,
                                 "Correlation Pairs" = 1,
                                 "Crossing Moving Averages" = 2,
                                 "Perfect Knowledge Profit" = 3),
                  selected = -1
      ),
                                 
    
      actionButton("run_query", "Run Query"),
     
     
      # Check box if plot each with different geom
      checkboxInput("single_geom", "Plot as single geom", value = TRUE),
      
      uiOutput("geom_choices"),
      
      # Using column values to group in plotting
      checkboxGroupInput("groupcols", label = h4("Group Columns"), 
                         choices = list("Choice 1" = 1, "Choice 2" = 2, "Choice 3" = 3),
                         selected = 1)
    ),
    
    
    

    # Show a plot of the generated distribution
    mainPanel(
      plotOutput("plot"),
      downloadButton("save_plot"),
      tableOutput("data")
    )
  )
))
