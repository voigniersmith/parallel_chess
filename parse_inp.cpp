// Bot makes next best move.
void bot_make_move() {

}


// Function to parse the input
int parse_inp(char* s) {

  if (strcmp(s, "q") == 0 || strcmp(s, "exit") == 0) {  // Quit.
    return 1;
  } else if (strchr(s, '/') != NULL) {  // Check for FEN.
    strcpy(b->layout, s);
    fen_to_board();
    return 0;
  } else if (strcmp(s, "on") == 0) {  // Bot make next move.
    bot_make_move();
  } else {  // Human make next move.

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

    char cur_color = get_color(b->board[row_from * 8 + col_from]);

    // Validate Move
    if(!validate(row_from * 8 + col_from,
          row_to * 8 + col_to)) {
      printf("Illegal Move\n");
      return 0;
    }

    // Update Board Representation
    b->board[row_to * 8 + col_to] = b->board[row_from * 8 + col_from];
    b->board[row_from * 8 + col_from] = 0;

    // Update Layout (FEN Notation)
    board_to_fen();

  }

  return 0;
}
