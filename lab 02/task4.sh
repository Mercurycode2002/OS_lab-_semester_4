for i in {1..5}
do
	name="test$i"
	cd $name
	for j in {1..2}
	do
		cd $j
		ls >> /home/student/filename.txt 
		cd ..
	done
	cd ..
done
