# update library path to include dependencies folder 
# necessary for systems without packages by default (.e.g CIMS machines)
.libPaths(c('./Rdeps',.libPaths()))
library(shiny)
library(ggplot2)
source("plot.R")
source("trading_strategies.R")


# Load q server functionality
source("../qserver.R", chdir = TRUE)


# Simple function to distinguish between predefined queries that
# take parameters and those that do not
takes_parameters <- function(x) {
  x >= 4
}

# server logic for plotting tool
shinyServer(function(input, output, session) {

  # Collect info about q connection from user input and create handle
  qHandle <- reactive({
    host <- input$host
    port <- input$port
    open_connection(host, port)
  })
  
  
  # pick appropriate parameter re-definition functions
  # TODO
  query_params <- reactive({
    id <- input$predefined_queries
    if (takes_parameters(id)) {
      if(id == BUY_CHEAP_STRATEGY) {
        buy_cheap_params(input$amt, input$startDate, input$threshold, input$period)
      }
    }
  })
  
  
  aqQuery <- reactive({
    if(input$predefined_queries == -1){
      input$query
    } else if (takes_parameters(input$predefined_queries)) {
      # select appropriate one
      params <- query_params()
      query <- paste0(".aq.q", input$predefined_queries, "[]")
      full_query <- paste(params, query, sep = ";")
      print(full_query)
    } else {
      query <- paste0(".aq.q", input$predefined_queries, "[]")
      print(query)
    }
  })
  
  # default data frame in case not connected when launched
  # or provided q/aquery command that doesn't return a table
  # (i.e. not plottable as default)
  default_data <- data.frame(c1 = c(1,2,3), c2 = c(10, 20, 30))
  
  # Avoid running query each time
  run_query <- reactive({
    # establish dependency
    input$run_query
    # only rerun when the button is fired
    
    isolate({
    print("Running query again")
    # TODO: display error message if connection doesn't work
    h <- tryCatch(qHandle(), error = function(e) {
       print("Unable to connect to q session")
       -1
    })
    

    dat <- tryCatch(execute(h, aqQuery()), error = function(e) {
      print(paste("Caught error, using default dataframe: ", e))
      default_data
      })
    
      # Default to dummy data if query result is not a dataframe
      if(!is.data.frame(dat)) {
        dat <- default_data
      }
      
      return(dat)
    })
    })

  # Show a bit of the data.frame head
  output$data <- renderTable(head(run_query()), 
                             caption = "Head of Data",
                             caption.placement = getOption("xtable.caption.placement", "top"),
                             caption.width = getOption("xtable.caption.width", NULL)
                             )
  

  # Update group columns
  observe({
    data <- run_query()
    choices <- as.list(names(data))
    names(choices) <- names(data)
    updateCheckboxGroupInput(session, inputId = "groupcols", choices = choices)
  })
  
  # Create tick boxes for each column (to decide what geom to use for
  # use for each)

  output$geom_choices <- renderUI({
    if (input$single_geom) {
      selectInput("geom1","Plot style:", choices = POSS_GEOMS, DEF_GEOM)
    } else {
    data <- run_query()
    columns <- names(data)
    # recall first column is always X column
    y_columns <- columns[2:length(columns)]
    
    lapply(1:length(y_columns), function(x) {
      selectInput(paste0("geom", x), paste(y_columns[x], "plot style:"), choices = POSS_GEOMS, DEF_GEOM)
      })
    }
  })
  
  # Create parameter menus for pre-defined trading strategies
  output$trading_strategy_params <- renderUI({
    if (takes_parameters(input$predefined_queries)) {
      if (input$predefined_queries == BUY_CHEAP_STRATEGY) {
        
        amt_gui <- sliderInput("amt", "Amount Invested Daily", min = 100e3, max = 1e6, step = 100e3, value = 100e3)
        period_gui <- sliderInput("period", "Holding Period (days)", min = 1, max = 100, step = 1, value = 2)
        threshold_gui <- sliderInput("threshold", "Returns threshold (underperformance)", min = -0.10, max = 0.0, value = -0.02)
        date_gui <- dateInput("startDate", "Start date", min = "2000-01-01", max = "2016-01-01", value = "2000-01-01")
        list(amt_gui, period_gui, threshold_gui, date_gui)
      }
    }
  })
  
  
  # plot function
  plotInput <- reactive({
    # for POC we assume the first column is x-axs and everything else is to 
    # be plotted as a separate series
    #cols <- names(output$table)
    #dat <- default_data
    dat <- run_query()
    
    # for predefined queries, we want to make sure we don't try to plot before
    # we have the data, so make it depend on the action button too
    if(input$predefined_queries != -1 && input$run_query > 0) {
      return(plot_predefined(dat, input$predefined_queries))
    }

    cols <- names(dat)
    ncols <- length(cols)
    groupcols <- input$groupcols
    base_plot <- ggplot(data = dat, aes_q(x = as.name(cols[1])))
    
    
    if (is.null(groupcols)) {
      groups <- NULL
    } else {
      groups <- groupify(groupcols)
    }
    
    # assemble aesthetics
    plot_details <- list("group" = groups)
    
    y_cols <- cols[! cols %in% groupcols]
    
    # geoms
    if (is.null(input$single_geom) || is.null(input$geom1)) {
      # case: just initialized, nothing yet selected
      geom_names <- rep("dot", ncols - 1)
    } else if (input$single_geom) {
      # case: all with same geom
      geom_names <- rep(input$geom1, ncols - 1)
    } else {
      # case: potentially different geoms for each column
      geom_names <- sapply(1:(ncols - 1), function(x) {
        geom <- input[[paste0("geom", x)]]
        ifelse(is.null(geom), DEF_GEOM, geom)
      })
    }
    
    plot_all_series(base_plot, y_cols, geom_names, plot_details)
  })
  
  # render plot
  output$plot <- renderPlot({
    plotInput()
    })


# Download plot
output$save_plot <- downloadHandler(
  filename = "plot.png",
  content = function(file) {
    device <- function(..., width, height) {
      grDevices::png(..., width = width, height = height,
                     res = 300, units = "in")
    }
    ggsave(file, plot = plotInput(), device = device)
  })
 })


                  

