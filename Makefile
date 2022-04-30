CC = g++
MPI = mpic++

all:: main

main: main.cpp
	${MPI} -o chess main.cpp -I.

run:
	make; mpirun -q -np 4 chess

clean:
	rm chess; rm *.csv

stats:
	rm chess; rm *.csv
	make
	mpirun -q -np 3 chess t
	mpirun -q -np 5 chess t
	mpirun -q -np 9 chess t
	mpirun -q -np 17 chess t
