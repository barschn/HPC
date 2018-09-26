echo "averaging the gprof results"
cd /home/tobias/GIT/HPC/assignment1/locality
echo "Running fast0 to get gmon.out"
./locality0
mv gmon.out gmon.sum
for i in {1..5} ; do
	echo $i
	./locality0
	gprof -s ./locality0 gmon.out gmon.sum
done
gprof ./locality0 gmon.sum > /home/tobias/GIT/HPC/assignment1/profiling/averaged.txt
cd /home/tobias/GIT/HPC/assignment1/profiling
cat averaged.txt
