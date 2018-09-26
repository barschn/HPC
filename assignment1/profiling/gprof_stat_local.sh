#!/bin/bash
echo "averaging the gprof results"
cd ~/COURSEWORK/TMA881/github/HPC/assignment1/locality
echo "Running locality0 to get gmon.out"
./locality0
mv gmon.out gmon.sum
for i in {1..500}
do
	echo $i
	#./locality0
	#gprof -s ./locality0 gmon.out gmon.sum
done
gprof ./locality0 gmon.sum > ~/COURSEWORK/TMA881/github/HPC/assignment1/profiling/averaged.txt
cd ~/COURSEWORK/TMA881/github/HPC/assignment1/profiling
cat averaged.txt
