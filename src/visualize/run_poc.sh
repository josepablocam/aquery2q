# Takes port for q process as argument
if [ ! $# -eq 1 ] 
  then
    echo "Usage: <port-number-for-q-process>"
    exit 1
fi

# AQuery compiler
A2Q=../a2q
# Port for q process
PORT=$1

# compile aquery file
$A2Q -a 1 -c -o poc.q poc.a

# launch q process with port 
# NOTE: (runs in background and killed upon exit of R process)
q poc.q -p $PORT &
# save down PID to kill
q_pid=$!

# launch R shiny application
R -e 'shiny::runApp(appDir = "example/", launch.browser = TRUE)'

# terminate q process
kill -9 $q_pid


