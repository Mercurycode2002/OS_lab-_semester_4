for i in {1..5}
do
	name="test$i"
#	for j in {1..2}
#	do
#		cd $j
#		rm test.txt
#		cd ..
#		rm -d $j
#	done
	rm -r $name
done
