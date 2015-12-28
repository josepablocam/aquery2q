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

# if there is no folder for q, copy over what we brought 
if [ ! -d $HOME/q/ ]
  then
    cp -r ./q/ $HOME/q/
fi

Q=$HOME/q/m32/q

# compile aquery file
$A2Q -a 1 -c -o poc.q poc.a

# launch q process with port 
# NOTE: (runs in background and killed upon exit of R process)
$Q poc.q -p $PORT &
# save down PID to kill
q_pid=$!

# launch R shiny application
R -e '.libPaths(c("./Rdeps",.libPaths())); shiny::runApp(appDir = "example/", launch.browser = TRUE)'


# terminate q process
kill $q_pid


