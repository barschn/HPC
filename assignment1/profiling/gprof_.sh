echo "gprof-ing locality"
cd /home/tobias/GIT/HPC/assignment1/locality
make
echo "Running fast0 to get gmon.out"
./locality_fast0
echo "gprof of fast0"
gprof locality_fast0
echo "Running fast2 to get gmon.out"
./locality_fast2
echo "gprof of fast2"
gprof locality_fast2
