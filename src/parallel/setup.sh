# create a comma-separated list from a space-separated list
function comma_sep {
  echo $(seq $1 $2) | tr ' ' ,
}

# consume user arguments and set values for the startup of the
# q processes
function consume_args {
  if [[ $# < 1 ]] || [[ $1 == '-h' ]] || [[ $1 == "--help" ]]
    then
      help
      exit 0
  fi

  while [[ $# -ge 1 ]]
  do
  key="$1"

  case $key in
      -x|--xterm)
      XTERM=1
      ;;
      -m|--masters)
      NUM_MASTERS="$2"
      shift # past argument
      ;;
      -w|--workers)
      NUM_WORKERS_PER_MASTER="$2"
      shift # past argument
      ;;
      -t|--time)
      TIME=1
      ;;
      *)
      SCRIPT=$key        # assume any unknown option is the script to run
      ;;
  esac
  shift # past argument or value
  done

  # set some defaults if no options provided
  if [ -z $NUM_MASTERS ]; then NUM_MASTERS=3; fi
  if [ -z $NUM_WORKERS_PER_MASTER ];then NUM_WORKERS_PER_MASTER=10; fi

  echo "Setup with options:"
  ! [ -z $XTERM ] && echo "xterm: true"
  echo "# masters:$NUM_MASTERS"
  echo "# workers per master:$NUM_WORKERS_PER_MASTER"
  ! [ -z $TIME ] && echo "timed: true"
  echo "running:$SCRIPT"
}

function help {
  echo "Usage: ./setup.sh [-x] [-m #] [-w #] [-t] <script-for-supermaster>"
  echo "-x|--xterm: Run each process in xterm"
  echo "-m|--masters: number of master processes (default 2)"
  echo "-w|--workers: number of workers per master process (default 10)"
  echo "-t|--time: call time on super-master process execution"
}


function startup {
  local num_workers=$(($NUM_WORKERS_PER_MASTER * $NUM_MASTERS))
  local worker_start=7000
  local worker_end=$(($worker_start + $num_workers - 1))

  local master_start=8000
  local master_end=$(($master_start + $NUM_MASTERS - 1))

  # setting up q command
  if  [ -z $XTERM ]
    then
      local q="rlwrap q"
    else
      local q="xterm -fa monaco -fs 10 -e rlwrap q"
  fi

  # open up worker processes
  echo "Initializing $NUM_WORKERS_PER_MASTER workers per cohort"
  for worker in $(seq $worker_start $worker_end)
  do
    nohup $q parallel.q -p $worker < /dev/null &
  done

  # sleep to allow workers to be setup
  sleep $((1 + $num_workers / 100))

  # open up masters and setup number of workers
  echo "Initializing $NUM_MASTERS masters"
  for master in $(seq $master_start $master_end)
  do
    nohup $q parallel.q -s -${NUM_WORKERS_PER_MASTER} -p $master < /dev/null &
  done

  # sleep to allow masters to be setup
  sleep $((1 + $NUM_MASTERS / 3))

  # set up lists of csv port numbers
  local worker_ports=$(comma_sep $worker_start $worker_end)
  local master_ports=$(comma_sep $master_start $master_end)

  echo "Initializing super-master"
  if [ -z $TIME ]
    then
      $q $SCRIPT -s -${NUM_MASTERS} -workers $worker_ports -masters $master_ports
    else
      time $q $SCRIPT -s -${NUM_MASTERS} -workers $worker_ports -masters $master_ports
  fi

  for port in $(echo "$worker_ports,$master_ports" | tr , ' ')
  do
    lsof -i tcp:$port | awk 'NR!=1 {print $2}' | xargs kill
  done
  exit 0
}

consume_args "$@"
startup
