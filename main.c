#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Funct Declarations
void fen_to_board ();
void board_to_fen ();
int parse_inp (char*);
void print_board ();

// Struct Declarations
struct board {
	int* board;
	char* layout;
	char turn;
	char* castling;
	char* enpassant;
	int halfmove;
	int fullmove;
};

// Global Variables
struct board* b;

// Driver code
int main (int argc, char* argv) {
	printf("Welcome to chess!\n");

	int exit_status = 0;
	b = (struct board*) malloc(sizeof(struct board));
	char inp[100];
	b->layout = (char*) malloc(sizeof(char) * 100);
	strcpy(b->layout, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	b->board = (int*) malloc(sizeof(int) * 64);
	fen_to_board();

	while (exit_status == 0) {
		print_board();
		printf("chess > ");
		scanf("%s", inp);
		exit_status = parse_inp(inp);
	}

	printf("Thanks for playing!\n");

	return 0;
}

// Notation to Representation Function
void fen_to_board() {
	int row = 0;
	int col = 0;
	int b_width = 8;
	for (int i = 0; i < strlen(b->layout); i++) {
		if (b->layout[i] == '/') {
			row++;
			col = 0;
		} else if (isdigit(b->layout[i])) {
			int spaces = atoi(&b->layout[i]);
			for (int j = 0; j < spaces; j++) {
				b->board[row * b_width + col] = ' ';
				col++;
			}
		} else {
			b->board[row * b_width + col] = b->layout[i];
			col++;
		}
	}
}

// Board Representation to FEN Function
void board_to_fen() {
	char temp[100];
	int spaces = 0;
	int row = 0;
	int col = 0;
	int pos = 0;
	for (int spot = 0; spot < 64; spot++) {
		if (b->board[spot] == ' ') {
			spaces++;
		} else {
			if (spaces != 0) {
				temp[pos++] = spaces + '0';
				spaces = 0;
			}
			temp[pos++] = b->board[spot];
		}

		col++;
		if (col == 8) {
			row++;
			col = 0;
			if (spaces != 0) {
				temp[pos++] = spaces + '0';
				spaces = 0;
			}
			if (spot != 63) temp[pos++] = '/';
			else temp[pos++] = 0;
		}
	}

	printf("%s\n", temp);

	strcpy(b->layout, temp);
}

// Function to parse the input
int parse_inp(char* s) {
	// Other commands check here
	if (strcmp(s, "exit") == 0) return 1;

	// Check for FED Notation
	if (strchr(s, '/') != NULL) {
		strcpy(b->layout, s);
		return 0;
	}

	// Assume Input to be Coordinate Notation
	if (s[0] < 'a' || s[0] > 'h' ||
		s[1] < '0' || s[1] > '9' ||
		s[2] < 'a' || s[2] > 'h' ||
		s[3] < '0' || s[3] > '9') {
		printf("Illegal Move\n");
		return 0;
	}

	int col_from = s[0] - 'a';
	int row_from = s[1] - '0' - 1;
	row_from = 7 - row_from;
	int col_to = s[2] - 'a';
	int row_to = s[3] - '0' - 1;
	row_to = 7 - row_to;

	// Update Board Representation
	b->board[row_to * 8 + col_to] = b->board[row_from * 8 + col_from];
	b->board[row_from * 8 + col_from] = ' ';

	// Update Layout (FEN Notation)
	board_to_fen();

	return 0;
}

// Function to print the board based on the layout
void print_board () {
	int rows = 7, columns = 0, spaces = 0;
	int size = strlen(b->layout);
	
	printf("\t  +------------------------+\n");

	for (int i = 0; i < size; i++) {
		printf("\t%d |", rows-- + 1);
		while(b->layout[i] != '/' && i != size) {
			if (isdigit(b->layout[i])) {
				spaces = atoi(&b->layout[i]);
				while (spaces > 0) {
					if (columns % 2 == 0 && rows % 2 == 1) {
						printf(":::");
					} else if (columns % 2 == 1 && rows % 2 == 0) {
						printf(":::");
					}else {
						printf("   ");
					}
					spaces--;
					columns++;
				}
				i++;
			} else {
				printf(" %c ", b->layout[i++]);
				columns++;
			}
		}
		printf("|\n");
		columns = 0;
	}

	printf("\t  +------------------------+\n");
	printf("\t    a  b  c  d  e  f  g  h  \n");
	
	// The Standard Layout	
	// printf("\t8 | r  n  b  q  k  b  n  r |\n");
	// printf("\t7 | p  p  p  p  p  p  p  p |\n");
	// printf("\t6 |   :::   :::   :::   :::|\n");
	// printf("\t5 |:::   :::   :::   :::   |\n");
	// printf("\t4 |   :::   :::   :::   :::|\n");
	// printf("\t3 |:::   :::   :::   :::   |\n");
	// printf("\t2 | P  P  P  P  P  P  P  P |\n");
	// printf("\t1 | R  N  B  Q  K  B  N  R |\n");
}
