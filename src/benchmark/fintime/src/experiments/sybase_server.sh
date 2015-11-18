
if [ $1 == "-init" ]
  then
  mkdir -p sybase/fintime/iq_files
  export IQLOGDIR16=sybase/fintime/
  # create config file
  echo -e "-n fintime\n-iqmc 1000\n-iqtc 1500" > /sybase/fintime/params.cfg
  
  dbisql -nogui "
  CREATE DATABASE 'fintime.db'
    BLANK PADDING ON
    DBA USER 'DBA'
    DBA PASSWORD 'sql'
    CASE IGNORE
    IQ PATH 'iq_files/fintime.iq'
    TEMPORARY PATH 'iqdemo.iqtmp'
  "

if [ $1 == "-start" ]
then
 start_iq @sybase/fintime/fintime.cfg sybase/fintime/fintime.db
fi


if [ $1 == "-stop" ]
then
 stop_iq -n fintime
fi


 
