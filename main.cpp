#include "includes.h"
#include "board_rep.cpp"
#include "board.cpp"
#include "parallel.cpp"
#include "parse_inp.cpp"
#include "init.cpp"

// Global Variables.
struct board* b;
int directionOffsets[] = {-8, 8, -1, 1, -9, 9, -7, 7};
int numSquaresToEdge[64][8];
std::vector<struct move> moves;
char board_start[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w";
int moves_ctr = 0;
struct move best_move;

// Driver code
int main (int argc, char** argv) {

  srand(time(NULL));

	printf("Welcome to chess!\n");

  play();

	printf("Thanks for playing!\n");
}

