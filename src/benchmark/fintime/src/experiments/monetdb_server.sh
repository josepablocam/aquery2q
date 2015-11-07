if [ $# -ne 1 ]; then
	echo "Usage: -init -start | -stop"
	exit 1
fi

# initialize for the first time
if [ $1 == "-init" ];
	then
		# create databases and set embedded python permission
		monetdbd create tables/monetdb
		monetdbd start tables/monetdb
		monetdb create fintime
		monetdb set embedded_py=true fintime
		monetdb release fintime
		# Set up monetdb config file with monetdb user
		echo -e "user=monetdb\npassword=monetdb" > .monetdb
		monetdbd stop tables/monetdb	
fi		


# start mserver5 with embedded python
if [ $1 == "-start" ];
	then
		if [ ! -d tables/monetdb ]; then
			echo "Must run ./monetdb_server.sh -init first"
			exit 1
		fi
	monetdbd start tables/monetdb
fi

if [ $1 == "-stop" ];
	then
		monetdbd stop tables/monetdb
fi		