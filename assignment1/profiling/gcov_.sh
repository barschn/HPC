echo "gprof-ing locality"
cd /home/tobias/GIT/HPC/assignment1/locality
make
echo "executing"
./locality_fast0_cov
echo "gcov-ing"
gcov locality_fast.c
cat locality_fast.c.gcov
