// Includes here.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <iostream>
#include <vector>

// Preprocessor directives here.
#ifndef max
#define max(a,b) ((a > b) ? a : b)
#endif

#ifndef min
#define min(a,b) ((a > b) ? b : a)
#endif


// Struct Declarations.
struct board {
	int* board; // Actual board.
	char* layout; // FEN representation.
  char turn;  // White is Z, Black is z.
};

struct move {
  int start, target;
};


// Global variables.
extern struct board* b; // My board.
extern int directionOffsets[];  // Numbers to add to move in dir.
extern int numSquaresToEdge[64][8];  // Bounds of board from any piece.
extern std::vector<struct move> moves;  // All possible moves.
