# update library path to include dependencies folder 
# necessary for systems without packages by default (.e.g CIMS machines)
library(shiny)
library(shinyAce)
library(ggplot2)
source("aquery_code.R")
source("plot.R")
source("trading_strategies.R")
# Load q server functionality
source("qserver.R", chdir = TRUE)


#SP 500 tickers
sp_tickers <- as.character(read.csv("../data/sp500_tickers.csv")$Ticker)
sp_tickers <- sp_tickers[order(sp_tickers)]
sp_tickers <- as.list(sp_tickers)
names(sp_tickers) <- sp_tickers

MIN_DATE <- as.Date("2000-01-01")
MAX_DATE <- as.Date("2016-06-01")


# Simple function to distinguish between predefined queries that
# take parameters and those that do not
takes_parameters <- function(x) {
  x >= 3
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
      if (id == PERFECT_STRATEGY) {
        perfect_params(input$ticker, input$amt, input$date_range)
      } else if(id == BUY_CHEAP_STRATEGY) {
        buy_cheap_params(input$amt, input$startDate, input$threshold, input$period)
      }else if (id == TECHNICAL_STRATEGY) {
        technical_params(input$ticker, input$amt, input$date_range, input$windows_range)
      } else if(id == PAIRS_STRATEGY) {
        pairs_params(input$ticker, input$ticker2, input$amt, input$startDate, input$period, input$threshold, input$len_before, input$len_after)
      } else {
        print("undefined query with parameters")
      }
    }
  })
  
  
  
  compiled_code <- reactive({
    input$run_query # dependency established
    code <- input$code
    status <- compile(code)
    if (!compilation_ok(status)) {
      stop(compilation_error(status))
    }
  })
  
  # Most queries just require that we run 1 command .aq.q0[]
  # However, other strategies, like pairs correlation
  # are more involved and thus have more interesting components that the
  # user might want to run to tweak their strategy
  get_query_run_command <- reactive({
    if(input$predefined_queries != PAIRS_STRATEGY) {
        ".aq.q0[]"
    } else {
     # figure out the right query to run and visualize 
      paste0(".aq.q", input$pairs_trading_component, "[]")
    }
  })
  
  
  aqQuery <- reactive({
    compiled_code()
    load_stmt <- paste('"l ', COMPILED_AQUERY_PATH, '"', sep ="")
    command <- paste("system", load_stmt, ";") 
    
    # if appropriate, then allow widgets to overwrite code based parameters
    if (takes_parameters(input$predefined_queries) && input$use_widgets) {
      params_command <- query_params()
      command <- paste(command, params_command)
    }
    
    query_run_command <- get_query_run_command()
    
    paste(command, query_run_command)
  })
  
  # Update code displayed
  observe({
    input$reset_query  # establish dependency
    updateAceEditor(session, editorId = "code", value = get_code(input$predefined_queries))
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
  
  # User custom plotting options, only possible when not using a predefined query
  output$user_plot_options <- renderUI({
    if(which_predefined_query() == -1) {
      # Check box if plot each with different geom
      single_geom <- checkboxInput("single_geom", "Plot as single geom", value = TRUE)
      
      # geom choices defined before
      
      # Using column values to group in plotting
      groups <- checkboxGroupInput("groupcols", label = h4("Group Columns"), 
                                   choices = list("Choice 1" = 1, "Choice 2" = 2, "Choice 3" = 3),
                                   selected = 1)
      list(single_geom, uiOutput("geom_choices"), groups)
    }
  })
  
  
  # Ticker GUI
  ticker_gui <- selectInput("ticker", "Ticker for strategy", choices = sp_tickers, selected = "AAPL")
  ticker2_gui <- selectInput("ticker2", "Buy Ticker for strategy", choices = sp_tickers, selected = "HP")
  
  
  # Create parameter menus for pre-defined trading strategies
  output$use_widgets <- renderUI({
    if (takes_parameters(input$predefined_queries)) {
    checkboxInput("use_widgets", label = "Visual parameters", value = FALSE)
    }
  })
  
  output$trading_strategy_params <- renderUI({
    if (takes_parameters(input$predefined_queries)) {
      if (input$predefined_queries == PERFECT_STRATEGY) {
        amt_gui <- sliderInput("amt", "Single investment amount", min = 100e3, max = 1e6, step = 100e3, value = 100e3)
        date_range_gui <- dateRangeInput("date_range", "Date Range for Strategy", min = MIN_DATE, max = MAX_DATE, start = MIN_DATE, end = MAX_DATE)
        gui <- list(ticker_gui, date_range_gui, amt_gui)
      } else if (input$predefined_queries == BUY_CHEAP_STRATEGY) {
        amt_gui <- sliderInput("amt", "Amount Invested Daily", min = 100e3, max = 1e6, step = 100e3, value = 100e3)
        period_gui <- sliderInput("period", "Holding Period (days)", min = 1, max = 100, step = 1, value = 2)
        threshold_gui <- sliderInput("threshold", "Returns threshold (underperformance)", min = -0.10, max = 0.0, value = -0.02)
        date_gui <- dateInput("startDate", "Start date", min = MIN_DATE, max = MAX_DATE, value = MIN_DATE)
        gui <- list(amt_gui, period_gui, threshold_gui, date_gui)
      } else if (input$predefined_queries == TECHNICAL_STRATEGY){
        amt_gui <- sliderInput("amt", "Amount invested per opportunity", min = 100e3, max = 1e6, step = 100e3, value = 100e3)
        date_range_gui <- dateRangeInput("date_range", "Date Range for Strategy", min = MIN_DATE, max = MAX_DATE, start = MIN_DATE, end = MAX_DATE)
        windows_gui <- sliderInput("windows_range", label = "Moving average windows", min = 1, max = 180, value = c(5, 21))
        gui <- list(ticker_gui, date_range_gui, amt_gui, windows_gui)
      } else if (input$predefined_queries == PAIRS_STRATEGY) {
        amt_gui <- sliderInput("amt", "Amount Invested Daily", min = 100e3, max = 1e6, step = 100e3, value = 100e3)
        # offset so that we can account for possible historical observation period
        date_gui <- dateInput("startDate", "Start date", min = MIN_DATE + 366, max = MAX_DATE, value = MIN_DATE + 366)
        period_gui <- sliderInput("period", "Holding Period (days)", min = 1, max = 100, step = 1, value = 31)
        threshold_gui <- sliderInput("threshold", "Correlation threshold (minimum)", min = 0.0, max = 1.0, value = 0.1)
        len_before_gui <- sliderInput("len_before", "Period for historical correlation (days)", min = 1, max = 365, step = 1, value = 31 * 6)
        len_after_gui <- sliderInput("len_after", "Period for recent correlation (days)", min = 1, max = 365, step = 1, value = 31)
        gui <- list(ticker_gui, ticker2_gui, amt_gui, date_gui, period_gui, threshold_gui, len_before_gui, len_after_gui)
      } else {
        print("Undefined parameter gui")
      }
      
      if(!is.null(input$use_widgets) && input$use_widgets) {
        gui
      }
    }
  })
  
  
  # We have multiple query components for pair trading, as it is the most involved strategy
  # we allow the user to visualize each of these separately by picking from a drop down menu
  output$pairs_trading_gui <- renderUI({
    if (input$predefined_queries == PAIRS_STRATEGY) {
            selectInput("pairs_trading_component", label = h4("Strategy Component"), 
              choices = list("Explore correlations" = 0, "Visualize pairs' prices" = 1, "Run trading strategy" = 2), 
              selected = 0)
    }
  })
  
  # wait on button
  which_pairs_component <- eventReactive(input$run_query, {
    input$pairs_trading_component
  }, ignoreNULL = FALSE)
  
  # wait on button
  which_predefined_query <- eventReactive(input$run_query, {
    input$predefined_queries
  }, ignoreNULL = FALSE)
  
  # plot function
  plotInput <- reactive({
    # we assume the first column is x-axs and everything else is to 
    # be plotted as a separate series
    dat <- run_query()
    
    if(which_predefined_query() != -1 && input$run_query > 0) {
      if (which_predefined_query() != PAIRS_STRATEGY) {
        return(plot_predefined(dat, which_predefined_query()))
      } else {
        # also send along info about which compoennt to plot
        return(plot_predefined(dat, which_predefined_query(), component = which_pairs_component()))
      }
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
  filename = "plot.pdf",
  content = function(file) {
    device <- function(..., width, height) {
      grDevices::png(..., width = width, height = height,
                     res = 300, units = "in")
    }
    ggsave(file, plot = plotInput(), device = device)
  })


# Download code
output$download_code <- downloadHandler(
  filename = "user_code.a",
  content = function(file) {
    write_code(input$code, file)
  }
)

# END OF SERVER CODE
 })



