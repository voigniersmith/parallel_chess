void precomputeBoardOffsets() {
  
  for (int i = 0 ; i < 8 ; i++) {
    for (int j = 0 ; j < 8 ; j++) {
    
      int numE = 7 - j;
      int numW = j;
      int numN = i;
      int numS = 7 - i;

      int idx = i * 8 + j;

      numSquaresToEdge[idx][0] = numN;
      numSquaresToEdge[idx][1] = numS;
      numSquaresToEdge[idx][2] = numW;
      numSquaresToEdge[idx][3] = numE;
      numSquaresToEdge[idx][4] = min(numN, numW);
      numSquaresToEdge[idx][5] = min(numS, numE);
      numSquaresToEdge[idx][6] = min(numN, numE);
      numSquaresToEdge[idx][7] = min(numS, numW);

    }
  }
}


// Parallelize!
void prune_moves() {
  std::vector<struct move> m2;
  std::vector<struct move> moves_cpy = moves;
  for (struct move m : moves_cpy) {
    if (validate(m.start, m.target)) {
      m2.push_back(m);
    }
  }
  moves = m2;
}


// Check if end game.
bool check_if_end() {

  // Stalemate.
  std::vector<struct move> my_moves = moves;
  b->turn = b->turn == 'z' ? 'Z' : 'z';
  generate_moves();
  std::vector<struct move> opp_moves = moves;
  moves = my_moves;
  b->turn = b->turn == 'z' ? 'Z' : 'z';

  // Find my king and check.
  int king_pos = 0;
  bool check = false;
  char cur_color = b->turn;
  for (int i = 0 ; i < 64 ; i++) {
    if ((cur_color == 'Z' && b->board[i] == 'K') || 
        (cur_color == 'z' && b->board[i] == 'k')) {
      king_pos = i;
      break;
    }
  }

  for (struct move m : opp_moves) {
    if (m.target == king_pos) {
      check = true;
    }
  }

  if ((moves.size() == 0 && opp_moves.size() == 0) ||
     (moves.size() == 0 && !check)) {
    printf("Stalemate!\nEnd Board:\n");
    print_board();
    return true;
  }
  
  // Checkmate.
  if (moves.size() == 0) {
    const char *c = b->turn == 'z' ? "White" : "Black";
    printf("%s wins!\nEnd Board:\n", c);
    print_board();
    return true;
  }

  // Draw.
  if (moves_ctr >= 100) {
    printf("You can stop now.\nEnd Board:\n");
    print_board();
    return true;
  }
  
  return false;
}


void play() {

	int exit_status = 0;
	b = (struct board*) malloc(sizeof(struct board));
	char inp[100];
  char str[] = "autobot";
	b->layout = (char*) malloc(sizeof(char) * 100);
	strcpy(b->layout, board_start);
	b->board = (int*) calloc(64, sizeof(int));
	fen_to_board();

  precomputeBoardOffsets();

  struct timeval start, end;

  FILE *file = fopen("minmax_stats.csv", "w+");
  fprintf(file, "moves, time, depth\n");
	
  while (exit_status < 1) {
    gettimeofday(&start, NULL);
    generate_moves();

    // Output moves sise to file.
    fprintf(file, "%ld, ", moves.size());

    prune_moves();
    //print_moves();
    if (check_if_end()) {
      printf("\nReseting Board.\n\n");
      strcpy(b->layout, board_start);
      fen_to_board();
      moves_ctr = 0;
      exit_status = 0;
    }
		print_board();
    if (exit_status != -1) {
		  printf("chess > ");
		  fgets(inp, 100, stdin);
      inp[strlen(inp) - 1] = 0;
		  exit_status = parse_inp(inp);
    } else {
      exit_status = parse_inp(str);
    }
    gettimeofday(&end, NULL);

    float dif_ms = ((end.tv_sec - start.tv_sec) * 1000000 
      + end.tv_usec - start.tv_usec) / 1000;

    fprintf(file, "%f, %d\n", dif_ms, global_depth);
    printf("Time to think = %f ms\n", dif_ms);
	}

  fclose(file);

}
