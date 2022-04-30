#include "includes.h"
#include "board_rep.cpp"
#include "board.cpp"
#include "search.cpp"
#include "parallel.cpp"
#include "parse_inp.cpp"
#include "init.cpp"

// Global Variables.
struct board b;
int directionOffsets[] = {-8, 8, -1, 1, -9, 9, -7, 7};
int numSquaresToEdge[64][8];
std::vector<struct move> moves;
char board_start[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w";
int moves_ctr = 0;
struct move best_move;
int global_depth = 5;
int myrank, npes;
int parallel = 0;
bool global_stats = false;

// Driver code.
int main (int argc, char** argv) {
  if (argc > 1) {
    global_stats = true;
  }

  srand(time(NULL));
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &npes);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

  if (myrank == 0) {
    if (!global_stats) {
      printf("Final Project for Parallel Computing.\n");
      printf("Developed by Team AAA.\n\n");
      printf("Welcome to chess!\n");
      printf("Type 'help' for a list of commands.\n");
    }

    play();

    if (!global_stats) {
      printf("Thanks for playing!\n");
    }
  } else {
    init();
    consumer();
  }
  MPI_Finalize();
}

