for i in {1..5}
do
	name="test$i"
	mkdir $name
	cd $name
	for j in {1..2}
	do
		mkdir $j
		cd $j
		date > test.txt
		cd ..
	done
	cd ..
done
#for i in {1..5}
#do
	#name="test$i"
#	rm -rf $i
#done
