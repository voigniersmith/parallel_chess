#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct board {
	char* layout;
	char turn;
	char* castling;
	char* enpassant;
	int halfmove;
	int fullmove;
};

int parse_inp (char*);
void print_board (char*);

// Driver code
int main (int argc, char* argv) {
	printf("Welcome to chess!\n");

	int exit_status = 0;
	struct board* b = (struct board*) malloc(sizeof(struct board));
	b->layout = (char*) malloc(sizeof(char) * 100);
	strcpy(b->layout, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR\0");
	
	while (exit_status == 0) {
		print_board(b->layout);
		printf("chess > ");
		scanf("%s", b->layout);
		exit_status = parse_inp(b->layout);
	}

	printf("Thanks for playing!\n");

	return 0;
}

// Function to parse the input
int parse_inp(char* s) {
	if (strcmp(s, "exit") == 0) return 1;

	if (s[0] < 'a' || s[0] > 'h' ||
		s[1] < '0' || s[1] > '9' ||
		s[2] < 'a' || s[2] > 'h' ||
		s[3] < '0' || s[3] > '9')
		return 1;



	return 0;
}

// Function to print the board based on the layout
void print_board (char* layout) {
	int rows = 7, columns = 0, spaces = 0;
	int size = strlen(layout);
	
	printf("\t  +------------------------+\n");

	for (int i = 0; i < size; i++) {
		printf("\t%d |", rows--);
		while(layout[i] != '/' && i != size) {
			if (isdigit(layout[i])) {
				spaces = atoi(&layout[i]);
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
				printf(" %c ", layout[i++]);
				columns++;
			}
		}
		printf("|\n");
		columns = 0;
	}

	printf("\t=>+------------------------+\n");
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
