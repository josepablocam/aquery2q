function startup {
  
  #local workers="7090 7091 7092 7093 7094 7095 7096 7097 7098 7099 7100 7101"
  local masters="7080 7081 7082"
  local NUM_WORKERS_PER_MASTER=10
  local NUM_MASTERS=3

  local q="xterm -fa monaco -fs 10 -e rlwrap q"
  # open up worker processes
  for worker in {7090..7120}
  do
    $q parallel.q -p $worker -hold &
  done
  
  sleep 3
  # open up masters w/ 10 workers each
  for master in $masters
  do
    $q parallel.q -s -${NUM_WORKERS_PER_MASTER} -p $master -hold &
  done
  
  # open up super-master with 3 masters
  sleep 3
  
  if [ "$2" == "--time" ]
    then 
      time $q $1 -s -${NUM_MASTERS} -hold
    else
      $q $1 -s -${NUM_MASTERS} -hold
  fi
  killall xterm
  exit 0
}

startup $1 $2
