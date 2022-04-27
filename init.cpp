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


void play() {

	int exit_status = 0;
	b = (struct board*) malloc(sizeof(struct board));
	char inp[100];
	b->layout = (char*) malloc(sizeof(char) * 100);
	strcpy(b->layout, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
	b->board = (int*) calloc(64, sizeof(int));
	fen_to_board();

  precomputeBoardOffsets();

	while (exit_status == 0) {
    generate_moves();
    print_moves();
		print_board();
		printf("chess > ");
		fgets(inp, 100, stdin);
    inp[strlen(inp) - 1] = 0;
		exit_status = parse_inp(inp);
	}

}
