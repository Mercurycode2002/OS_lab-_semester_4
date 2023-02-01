echo "Num 1: $1"
echo "Num 2: $2"
echo "Num 3: $3"
if [ $1 -lt $3 ] && [ $1 -lt $3 ]
then
	echo "$1 is the smallest"
elif [ $2 -lt $3 ] && [ $2 -lt $1 ]
then
	echo "$2 is the smallest"
else 
	echo "$3 is the smallest"
fi
