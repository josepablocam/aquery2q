FINTIME_OPS="uid=DBA;pwd=sql;dbn=fintime"
UTILITY_OPS="uid=DBA;pwd=sql;dbn=utility_db"

if [ $1 == "-create" ]
  then
  # stop any servers created by user
  stop_iq -stop all
  mkdir -p tables/sybase/fintime/iq_files
  cd tables/sybase/fintime ; \
  export IQLOGDIR16=$(pwd); \
  start_iq -n fintime; \
  dbisql -nogui -c=${UTILITY_OPS} ../../../iq_setup.sql; \
  stop_iq -stop all ; \
  echo -e "-n fintime\n-iqmc 1000\n-iqtc 1500" > fintime.cfg ; \
  start_iq @./fintime.cfg ./fintime.db ; \
  dbisql -nogui -c=${FINTIME_OPS} -onerror continue ../../../make_tables_iq.sql; \
  stop_iq -stop all
fi

if [ $1 == "-start" ]
  then
  stop_iq -stop all
  start_iq @./tables/sybase/fintime/fintime.cfg ./tables/sybase/fintime/fintime.db
fi

if [ $1 == "-stop" ]
  then
  stop_iq -stop all
fi

  
  