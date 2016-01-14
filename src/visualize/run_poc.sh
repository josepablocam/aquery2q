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
AQUERYDIR=./aquery/

# if there is no folder for q, copy over what we brought 
if [ ! -d $HOME/q/ ]
  then
    cp -r ./q/ $HOME/q/
fi

Q=$HOME/q/m32/q

# compile aquery file
$A2Q -a 1 -c -o ${AQUERYDIR}/setup.q ${AQUERYDIR}/setup.a

# launch q process with port (launch it with respect to R folder)
# NOTE: (runs in background and killed upon exit of R process)
$Q $SETUP_SCRIPT -p $PORT &
# save down PID to kill
q_pid=$!

# launch R shiny application
R -e '.libPaths(c("./Rdeps",.libPaths())); shiny::runApp(appDir = "R/", launch.browser = TRUE)'


# terminate q process
kill $q_pid


