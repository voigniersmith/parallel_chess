
// Baseline evaluation based on pieces and values on board.
int evaluate() {
  
  int pVal = 100;
  int nVal = 300;
  int bVal = 300;
  int rVal = 500;
  int qVal = 900;

  int white_total = 0;
  int black_total = 0;

  for (int i = 0 ; i < 64 ; i++) {
    char piece = b->board[i];
    if (piece != 0) {
      if (isupper(piece)) {
        switch(piece) {
          case 'p':
            white_total += pVal;
            break;
          case 'n':
            white_total += nVal;
            break;
          case 'b':
            white_total += bVal;
            break;
          case 'r':
            white_total += rVal;
            break;
          case 'q':
            white_total += qVal;
            break;
        }
          
      } else {
        piece = tolower(piece);
        switch(piece) {
          case 'p':
            black_total += pVal;
            break;
          case 'n':
            black_total += nVal;
            break;
          case 'b':
            black_total += bVal;
            break;
          case 'r':
            black_total += rVal;
            break;
          case 'q':
            black_total += qVal;
            break;
        }

      }
    }
  } // end for.

  int eval = white_total - black_total;
  int p = b->turn == 'Z' ? 1 : -1;
  return eval * p;
}


// Minimax search.
int search(int depth, int start_depth) {
  
  if (depth == 0) {
    return evaluate();
  }

  generate_moves();
  prune_moves();

  if (moves.size() == 0) {
    if (in_check()) {
      return INT_MIN;
    }
    return 0;
  }

  int best_eval = INT_MIN;

  std::vector<struct move> cur_moves = moves;
  for (struct move m : cur_moves) {
    char p = make_move(m.start, m.target);
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    int eval = -1 * search(depth - 1, start_depth);
    if (eval >= best_eval) {
      best_eval = eval;
      if (depth == start_depth) {
        best_move = m;
      }
    }

    unmake_move(m.start, m.target, p);
    b->turn = b->turn == 'z' ? 'Z' : 'z';
  }
  return best_eval;
}










