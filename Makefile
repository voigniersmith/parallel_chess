CC = g++
MPI = mpic++

all:: main norm

main: main.cpp
	${MPI} -o chess main.cpp -I.

norm: main.cpp
	${CC} -o ser_chess main.cpp -I.

compile:
	make; clear; chess

serrun:
	ser_chess

run:
	mpirun -np 4 chess

clean:
	rm chess; rm *.csv
