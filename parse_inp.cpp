void upd_and_move(struct move m) {
  // Update counter and make move.
  moves_ctr++;

  if (tolower(b.board[m.start]) == 'p') {
    moves_ctr = 0;
  }
  char piece = make_move(m.start, m.target);
  if (piece != 0) {
    moves_ctr = 0;
  }

  // Update Layout (FEN Notation)
  board_to_fen();
}

// Bot makes next best move.
void bot_make_move() {
  if (parallel > 2) {
    upd_and_move(producer());
  } else {
    if (parallel == 0) {
      search(global_depth, global_depth);
    } else if (parallel == 1) {
      ab_search(global_depth, global_depth, INT_MIN, INT_MAX);
    } else {
      ab_cap_search(global_depth, global_depth, INT_MIN, INT_MAX);
    }
    struct move m = best_move;
    upd_and_move(m);  
  }
}


// Update bot type.
void update(int new_type) {
  parallel = new_type;
}


// Output help screen.
void print_help() {
  printf("This is the help screen. A list of commands are below.\n\n");
  printf("Options:\n");
  printf("\t'help'\t\tDisplays this screen.\n");
  printf("\t'c' || 'clear'\tResets the board.\n");
  printf("\t'q' || 'exit'\tCleanly exit the program.\n");
  printf("\t'd %%d'\t\tChange bot search depth to integer.\n");
  printf("\t't %%d'\t\tChange bot search type using integer.\n");
  printf("\t'bot'\t\tLet the computer make next move.\n");
  printf("\t'autobot'\tLet computer finish the game.\n");
  printf("\t'%%c%%d%%c%%d'\tFrom-To Coordinate notation.\n");
  printf("\tForsyth-Edwards notation is allowed.\n");

  printf("\nType Usage for 't':\n");
  printf("\t0: Serial MinMax Search.\n");
  printf("\t1: Serial MinMax Search with Alpha-Beta Pruning.\n");
  printf("\t2: Serial MinMax Search with Alpha-Beta Pruning and Move Ordering.\n");
  printf("\t3: Parallel MinMax Search.\n");
  printf("\t4: Parallel MinMax Search with Alpha-Beta Pruning.\n");
  printf("\t5: Parallel MinMax Search with Alpha-Beta Pruning and Move Ordering.\n");
  printf("\n");

  fflush(stdout);
}

// Function to parse the input
int parse_inp(char* s) {
  if (strcmp(s, "help") == 0) {
    print_help();
  } else if (strcmp(s, "q") == 0 || strcmp(s, "exit") == 0) {  // Quit.
    terminate();
    return 1;
  } else if (strchr(s, '/') != NULL) {  // Check for FEN.
    strcpy(b.layout, s);
    fen_to_board();
    return 0;
  } else if (strcmp(s, "c") == 0 || strcmp(s, "clear") == 0) {
    strcpy(b.layout, board_start);
    fen_to_board();
    return 0;
  } else if (strncmp(s, "d ", 2) == 0) {
    global_depth = atoi(&s[2]);
    printf("Depth set to: %d\n", global_depth);
  } else if (strcmp(s, "autobot") == 0) {
    bot_make_move();
    return -1;
  } else if (strcmp(s, "bot") == 0) {  // Bot make next move.
    bot_make_move();
  } else if (strncmp(s, "t ", 2) == 0) { // Update bot type.
    update(atoi(&s[2]));
    printf("Bot type set to: %d\n", atoi(&s[2]));
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

    char cur_color = get_color(b.board[row_from * 8 + col_from]);

    // Validate Move
    if(!validate(row_from * 8 + col_from,
          row_to * 8 + col_to)) {
      printf("Illegal Move\n");
      return 0;
    }

    // Update counter and make move.
    moves_ctr++;

    if (tolower(b.board[row_from * 8 + col_from]) == 'p') {
      moves_ctr = 0;
    }
    char piece = make_move(row_from * 8 + col_from, row_to * 8 + col_to);
    if (piece != 0) {
      moves_ctr = 0;
    }

    // Update Layout (FEN Notation)
    board_to_fen();

  }

  return 0;
}
