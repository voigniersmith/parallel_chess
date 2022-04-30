
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
 
  printf("Rank = %d\n", myrank);
  print_board();
  fflush(stdout);

  if (depth == 0) {
    return evaluate();
  }

  printf("1\n");

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


// Compare function for sorting.
bool compare(const std::pair<int, struct move>&i, const std::pair<int, struct move>&j) { 
  return i.first > j.first; 
} 



// Reorder moves for quicker ab pruning.
void move_ordering() {
  
  int pVal = 100;
  int nVal = 300;
  int bVal = 300;
  int rVal = 500;
  int qVal = 900;
  
  std::vector<struct move> my_moves = moves;
  std::vector<std::pair<int, struct move>> pair_vec;
  
  for (struct move m : my_moves) {
    int move_score_guess = 0;
    char piece = tolower(b->board[m.start]);
    char target_piece = tolower(b->board[m.target]);
    int piece_val = 0;
    int target_val = 0;

    switch(piece) {
      case 'p':
        piece_val += pVal;
        break;
      case 'n':
        piece_val += nVal;
        break;
      case 'b':
        piece_val += bVal;
        break;
      case 'r':
        piece_val += rVal;
        break;
      case 'q':
        piece_val += qVal;
        break;
    }
    
    switch(target_piece) {
      case 'p':
        target_val += pVal;
        break;
      case 'n':
        target_val += nVal;
        break;
      case 'b':
        target_val += bVal;
        break;
      case 'r':
        target_val += rVal;
        break;
      case 'q':
        target_val += qVal;
        break;
    }

    // Prioritize capturing valuable pieces with worthless pieces.
    if (target_piece != 0) {
      move_score_guess = 10 * target_val - piece_val;
    }

    // Penalize moving to square attacked my pawn.

    // Generate other guys pawn attack squares.
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    moves.clear();
    for (int i = 0 ; i < 64 ; i++) {
      generate_pawn_moves(i, b->board[i]);
    }
    std::vector<struct move> opp_pawn_moves = moves;
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    moves = my_moves;
    
    // See if pawn can attack our move.
    for (struct move opp_m : opp_pawn_moves) {
      if (opp_m.target == m.target) {
        move_score_guess -= piece_val;
      }
    }

    pair_vec.push_back(std::make_pair(move_score_guess, m));
  }

  std::sort(pair_vec.begin(), pair_vec.end(), compare);
  moves.clear();
  for (std::pair<int, struct move> p : pair_vec) {
    moves.push_back(p.second);
  }

}


// Alpha Beta.
int ab_search(int depth, int start_depth, int alpha, int beta) {

  if (depth == 0) {
    return evaluate();
  }

  generate_moves();
  prune_moves();
  move_ordering();

  if (moves.size() == 0) {
    if (in_check()) {
      return INT_MIN;
    }
    return 0;
  }

  std::vector<struct move> cur_moves = moves;
  for (struct move m : cur_moves) {
    char p = make_move(m.start, m.target);
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    int eval = -1 * ab_search(depth - 1, start_depth, -1 * beta, -1 *alpha);

    unmake_move(m.start, m.target, p);
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    
    if (eval >= beta) {
      return beta;
    }
      
    if (eval >= alpha) {
      alpha = eval;
      if (depth == start_depth) {
        best_move = m;
      }
    }
  }
  return alpha;
}


// Capture-Search Alpha Beta.
int ab_cap_search(int depth, int start_depth, int alpha, int beta) {

  if (depth == 0) {
    return evaluate();
  }

  generate_moves();
  prune_moves();

  // Prune Moves that don't capture.
  std::vector<struct move> cur_moves = moves;
  moves.clear();
  bool can_cap = false;
  for (struct move m : cur_moves) {
    if (b->board[m.target] != 0) {
      can_cap = true;
      moves.push_back(m);
    }
  }
  if (!can_cap) {
    moves = cur_moves;
  }
  move_ordering();

  if (moves.size() == 0) {
    if (in_check()) {
      return INT_MIN;
    }
    return 0;
  }

  cur_moves = moves;
  for (struct move m : cur_moves) {
    char p = make_move(m.start, m.target);
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    int eval = -1 * ab_search(depth - 1, start_depth, -1 * beta, -1 *alpha);

    unmake_move(m.start, m.target, p);
    b->turn = b->turn == 'z' ? 'Z' : 'z';
    
    if (eval >= beta) {
      return beta;
    }
      
    if (eval >= alpha) {
      alpha = eval;
      if (depth == start_depth) {
        if (best_move.start == -1) {
          best_move = m;
        } else {
          best_move = rand() % 2 == 1 ? m : best_move;
        }
      }
    }
  }
  return alpha;
}





