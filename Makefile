CC = g++
MPI = mpicc

all:: main

main: main.cpp
	${CC} -o chess main.cpp -I.

compile:
	make; clear; chess

run:
	chess

clean:
	rm chess
