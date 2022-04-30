CC = g++
MPI = mpic++

all:: main

main: main.cpp
	${MPI} -o chess main.cpp -I.

run:
	make; mpirun -np 4 chess

clean:
	rm chess; rm *.csv

stats:
	rm chess; rm *.csv
	touch stats.csv
	make
	mpirun -np 2 chess
	mpirun -np 4 chess
	mpirun -np 8 chess
	mpirun -np 16 chess
