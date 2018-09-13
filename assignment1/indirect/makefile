.PHONY: all check clean

CFLAGS=-std=c11 -march=native
CO0=$(CFLAGS) -O0
CO2=$(CFLAGS) -O2

all : indirect_v1 indirect_v2 direct

indirect_v1 : indirect_v1.c
	gcc $(CO0) -o indirect_v10 indirect_v1.c
	gcc $(CO2) -o indirect_v12 indirect_v1.c

indirect_v2 : indirect_v2.c
	gcc $(CO0) -o indirect_v20 indirect_v2.c
	gcc $(CO2) -o indirect_v22 indirect_v2.c

direct : direct.c
	gcc $(CO0) -o direct0 direct.c
	gcc $(CO2) -o direct2 direct.c

clean :
	rm -f indirect_v10 indirect_v12 indirect_v20 indirect_v22 direct
	rm -f *.o

check :
	echo "Indirect"
	echo "V1"
	./indirect_v10
	./indirect_v12
	echo "V2"
	./indirect_v20
	./indirect_v22
	echo "Direct"
	./direct0
	./direct2

