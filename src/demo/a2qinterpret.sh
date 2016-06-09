if [ $# -ne 1 ]
  then
    echo "Usage: ./a2qinterpret.sh <port-number>"
    exit 1
fi

src_path=$( cd "$(dirname "${BASH_SOURCE}")" ; pwd -P )
q -p $1 > /dev/null &
sleep 1s
python ${src_path}/a2qinterpret.py localhost $1 ""
killall q
