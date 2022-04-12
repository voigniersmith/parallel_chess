CC = gcc
MPI = mpicc

all:: main

main: main.c
	${CC} -o chess main.c -I.

run:
	chess

clean:
	rm chess
