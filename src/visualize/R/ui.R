# update library path to include dependencies folder 
# necessary for systems without packages by default (.e.g CIMS machines)
library(shiny)
library(shinyAce)
source('aquery_code.R')




# Define UI for application
shinyUI(fluidPage(

  # Application title
  titlePanel("AQuery to Make Your Fortune"),

  
  # Sidebar with inputs
  sidebarLayout(
    sidebarPanel(
      selectInput("predefined_queries", "Queries",
                  choices = list("Custom" = -1,
                        "Moving Variance" = 0,
                                 "Correlation Pairs" = 1,
                                 "Crossing Moving Averages" = 2,
                                 "Trading Strategy: Perfect Knowledge" = 3,
                                 "Trading Strategy: Buy Cheap" = 4,
                                 "Trading Strategy: Crossing Moving Averages" = 5,
                                 "Trading Strategy: Pairs Trading" = 6),
                  selected = -1
      ),
      aceEditor("code", mode = 'aquery', value = get_code(-1)),
      actionButton("reset_query", "Reset Code"),
      actionButton("run_query", "Run Code"),
      downloadButton("download_code", label = "Download code"),
      
        
      # Widget-based parameters
      uiOutput("pairs_trading_gui"),
      uiOutput("use_widgets"),
      uiOutput("trading_strategy_params"),
      
      # Custom plotting can (should) only be done when not a predefined query
      uiOutput("user_plot_options"), 
      # Connection information
      textInput("host", "Q connection hostname:", "localhost"),
      numericInput("port", "Q connection port number: ", 7089)
    ),
    
    
    

    # Show a plot of the generated distribution
    mainPanel(
      plotOutput("plot"),
      downloadButton("save_plot", label = "Download plot"),
      tableOutput("data")
    )
  )
))
