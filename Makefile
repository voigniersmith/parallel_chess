CC = g++
MPI = mpic++

all:: main

main: main.cpp
	${MPI} -o chess main.cpp -I.

run:
	make; mpirun -np 2 chess

clean:
	rm chess; rm *.csv
