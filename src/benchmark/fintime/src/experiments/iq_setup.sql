
-- PATHS RELATIVE TO tables/sybase/fintime
CREATE DATABASE 'fintime.db'
   CASE IGNORE
   DBA USER 'DBA'
   DBA PASSWORD 'sql'
   IQ PATH 'iq_files/fintime_01.iq'  
   IQ SIZE 1000           
   IQ RESERVE 1500
   TEMPORARY PATH 'iq_files/fintime_01.iqtmp'
   TEMPORARY SIZE 500
   TEMPORARY RESERVE 500;