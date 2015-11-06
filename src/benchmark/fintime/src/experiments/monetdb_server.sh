if [ $# -ne 1 ]; then
	echo "Usage: -start | -stop"
	exit 1
fi

if [ $1 == "-start" ];
	then
		monetdbd create tables/monetdb
		monetdbd start tables/monetdb
		monetdb create fintime
		monetdb release fintime
		# Set up monetdb config file with monetdb user
		echo -e "user=monetdb\npassword=monetdb" > .monetdb
fi

if [ $1 == "-stop" ];
	then
		monetdbd stop tables/monetdb
fi		