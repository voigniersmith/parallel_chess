#include "includes.h"
#include "board_rep.cpp"
#include "board.cpp"
#include "parse_inp.cpp"
#include "init.cpp"

// Global Variables.
struct board* b;

int directionOffsets[] = {-8, 8, -1, 1, -9, 9, -7, 7};
int numSquaresToEdge[64][8];
std::vector<struct move> moves;


// Driver code
int main (int argc, char** argv) {
	printf("Welcome to chess!\n");

  play();

	printf("Thanks for playing!\n");
}

