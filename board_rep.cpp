// Print Moves
void print_moves() {
  for (int i = 0; i < moves.size(); i++) {
    char startNum = '8' - moves.at(i).start / 8;
    char startAlp = 'a' + moves.at(i).start % 8;
    char endNum = '8' - moves.at(i).target / 8;
    char endAlp = 'a' + moves.at(i).target % 8;
    printf("Move '%d': '%c%c%c%c'\n", i, startAlp,
      startNum, endAlp, endNum);
  }
}


// FEN to representation function.
void fen_to_board() {
	int row = 0;
	int col = 0;
	int b_width = 8;
	for (int i = 0; i < strlen(b->layout); i++) {
    if (b->layout[i] == ' ') {
      if (b->layout[i + 1] == 'w') {
        b->turn = 'Z';
      } else {
        b->turn = 'z';
      }
      break;
		} else if (b->layout[i] == '/') {
			row++;
			col = 0;
		} else if (isdigit(b->layout[i])) {
			int spaces = atoi(&b->layout[i]);
			for (int j = 0; j < spaces; j++) {
				b->board[row * b_width + col] = 0;
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
		if (b->board[spot] == 0) {
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
			else temp[pos++] = ' ';
		}
	}

  if (b->turn == 'Z') {
    temp[pos] = 'b';
    b->turn = 'z';
  } else {
    temp[pos] = 'w';
    b->turn = 'Z';
  }
  temp[++pos] = 0;

	printf("%s\n", temp);

	strcpy(b->layout, temp);
}


// Function to print the board based on the layout
void print_board () {
	int rows = 8, columns = 0, spaces = 0;
	int size = strlen(b->layout) - 2;

  if (b->turn == 'z')
	  printf("\t->+------------------------+\n");
  else
	  printf("\t  +------------------------+\n");

	for (int i = 0; i < size; i++) {
		printf("\t%d |", rows--);
		while(b->layout[i] != '/' && i != size) {
			if (isdigit(b->layout[i])) {
				spaces = atoi(&b->layout[i]);
				while (spaces > 0) {
					if (columns % 2 == 0 && rows % 2 == 1) {
						printf(":::");
					} else if (columns % 2 == 1 && rows % 2 == 0) {
						printf(":::");
					} else {
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

  if (b->turn == 'Z')
	  printf("\t->+------------------------+\n");
  else
	  printf("\t  +------------------------+\n");
	printf("\t    a  b  c  d  e  f  g  h  \n");
	
}

