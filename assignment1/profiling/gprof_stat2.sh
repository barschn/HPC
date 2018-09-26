echo "averaging the gprof results"
cd /home/tobias/GIT/HPC/assignment1/locality
echo "Running fast0 to get gmon.out"
./locality2
mv gmon.out gmon.sum
for i in {1..5} ; do
	echo $i
	./locality2
	gprof -s ./locality2 gmon.out gmon.sum
done
gprof ./locality2 gmon.sum > /home/tobias/GIT/HPC/assignment1/profiling/averaged.txt
cd /home/tobias/GIT/HPC/assignment1/profiling
cat averaged.txt
