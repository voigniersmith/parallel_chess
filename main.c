#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_board (char*);

// Driver code
int main (int argc, char* argv) {
	printf("Welcome to chess!\n");
	
	char* layout = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR\0";
	print_board(layout);

	char inp[100];
	while(strcmp(inp, "exit") != 0) {
		printf("Enter a layout: ");
		scanf("%s", inp);
		// Need to check input here
		print_board(inp);
	}

	return 0;
}

// Function to print the board based on the layout
void print_board (char* layout) {
	int rows = 8, columns = 0, spaces = 0;
	int size = strlen(layout);
	
	printf("\t  +------------------------+\n");

	for (int i = 0; i < size; i++) {
		printf("\t%d |", rows--);
		while(layout[i] != '/' && i != size) {
			if (isdigit(layout[i])) {
				spaces = atoi(&layout[i]);
				while (spaces > 0) {
					if (columns % 2 == 0 && rows % 2 == 0) {
						printf(":::");
					} else if (columns % 2 == 1 && rows % 2 == 1) {
						printf(":::");
					}else {
						printf("   ");
					}
					spaces--;
					columns++;
				}
				i++;
			} else {
				if (isupper(layout[i]))
					printf("<%c>", layout[i++]);
				else
					printf("[%c]", layout[i++]);
				columns++;
			}
		}
		printf("|\n");
		columns = 0;
	}

	printf("\t=>+------------------------+\n");
	printf("\t    a  b  c  d  e  f  g  h  \n");
	
	// The Standard Layout	
	// printf("\t8 |[r][n][b][q][k][b][n][r]|\n");
	// printf("\t7 |[p][p][p][p][p][p][p][p]|\n");
	// printf("\t6 |   :::   :::   :::   :::|\n");
	// printf("\t5 |:::   :::   :::   :::   |\n");
	// printf("\t4 |   :::   :::   :::   :::|\n");
	// printf("\t3 |:::   :::   :::   :::   |\n");
	// printf("\t2 |<P><P><P><P><P><P><P><P>|\n");
	// printf("\t1 |<R><N><B><Q><K><B><N><R>|\n");
}
