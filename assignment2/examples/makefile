.PHONY : all check clean

TARGETS = llnl_ex_helloworld

all : $(TARGETS)

llnl_ex_helloworld : llnl_ex_helloworld.c
	gcc -O3 -march=native -std=c11 llnl_ex_helloworld.c -o llnl_ex_helloworld -lpthread

clean :
	rm -f $(TARGETS)
