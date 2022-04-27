// Check if current move is my move.
bool is_color(char piece, char turn) {
  if (turn == 'Z' && isupper(piece)) {
    return true;
  } else if (turn == 'z' && islower(piece)) {
    return true;
  }
  return false;
}


// Is a sliding piece.
bool is_sliding_piece(char piece) {
  char c = tolower(piece);
  return (c == 'b' || c == 'r' || c == 'q');
}


// Is a pawn.
bool is_pawn(char piece) {
  char c = tolower(piece);
  return (c == 'p');
}


// Is a king.
bool is_king(char piece) {
  char c = tolower(piece);
  return (c == 'k');
}


// Is a knight.
bool is_knight(char piece) {
  char c = tolower(piece);
  return (c == 'n');
}

// Gets piece's color.
char get_color(char piece) {
  if (islower(piece))
    return 'z';
  if (isupper(piece))
    return 'Z';
  return 0;
}


// Generates & add move to moves.
void add_move(int start, int target) {
  struct move m;
  m.start = start;
  m.target = target;
  moves.push_back(m);
}


// Generate sliding moves.
void generate_sliding_moves(int start, char piece) {
  int start_dir_idx = tolower(piece) == 'b' ? 4 : 0;
  int end_dir_idx = tolower(piece) == 'r' ? 4 : 8;

  for (int i = start_dir_idx; i < end_dir_idx; i++) {
    for (int j = 0; j < numSquaresToEdge[start][i]; j++) {
      int target = start + directionOffsets[i] * (j + 1);
      int target_piece = b->board[target];
      if(is_color(target_piece, get_color(piece))) {
        break;
      }

      add_move(start, target);

      if (is_color(target_piece, get_color(piece))) {
        break;
      }
    }
  }
}


// Generate pawn moves. TODO: En Passant & Upgrades
void generate_pawn_moves(int start, char piece) {
  char cur_color = get_color(piece);

  if (cur_color == 'Z') {
    // Check if pawn can move forward
    if (!b->board[start + directionOffsets[0]]) {
      add_move(start, start + directionOffsets[0]);

      // Check if pawn hasn't moved.
      if (start >= 48 && start <= 55) {
         if (!b->board[start + (2 * directionOffsets[0])]) {
           add_move(start, start + (2 * directionOffsets[0]));
         }
      }
    }

    // Check frontleft & frontright.
    if (numSquaresToEdge[start][4] > 0) {
      char frontleft = b->board[start + directionOffsets[4]];
      if (frontleft && cur_color != get_color(frontleft)) {
        add_move(start, start + directionOffsets[4]);
      }
    }

    if (numSquaresToEdge[start][6] > 0) {
      char frontright = b->board[start + directionOffsets[6]];
      if (frontright && cur_color != get_color(frontright)) {
        add_move(start, start + directionOffsets[6]);
      }
    }
  } else if (cur_color == 'z') {
    // Check if pawn can move forward
    if (!b->board[start + directionOffsets[1]]) {
      add_move(start, start + directionOffsets[1]);

      // Check if pawn hasn't moved.
      if (start >= 8 && start <= 15) {
        if (!b->board[start + (2 * directionOffsets[1])]) {
          add_move(start, start + (2 * directionOffsets[1]));
        }
      }
    }

    // Check frontleft & frontright.
    if (numSquaresToEdge[start][5] > 0) {
      char frontleft = b->board[start + directionOffsets[5]];
      if (frontleft && cur_color != get_color(frontleft)) {
        add_move(start, start + directionOffsets[5]);
      }
    }

    if (numSquaresToEdge[start][7] > 0) {
      char frontright = b->board[start + directionOffsets[7]];
      printf("Front Right: '%c' '%d'\n", frontright, directionOffsets[7]);
      if (frontright && cur_color != get_color(frontright)) {
        add_move(start, start + directionOffsets[7]);
      }
    }
  }
}


// Generate King moves. TODO: Castling
void generate_king_moves(int idx, char piece) {
  for (int i = 0; i < 8; i++) {
    if (numSquaresToEdge[idx][i] > 0) {
      int target = idx + directionOffsets[i];
      int target_piece = b->board[target];

      if(!is_color(target_piece, get_color(piece))) {
        add_move(idx, target);
      }
    }
  }
}


// Generate Knight moves.
void generate_knight_moves(int idx, char piece) {
  std::vector<int> l;

  // North East
  if (numSquaresToEdge[idx][0] >= 2 && numSquaresToEdge[idx][3] >= 1)
    l.push_back(idx - 15);
  
  // North West
  if (numSquaresToEdge[idx][0] >= 2 && numSquaresToEdge[idx][2] >= 1)
    l.push_back(idx - 17);
  
  // East North
  if (numSquaresToEdge[idx][3] >= 2 && numSquaresToEdge[idx][0] >= 1)
    l.push_back(idx - 6);
  
  // East South
  if (numSquaresToEdge[idx][3] >= 2 && numSquaresToEdge[idx][1] >= 1)
    l.push_back(idx + 10);
  
  // South East
  if (numSquaresToEdge[idx][1] >= 2 && numSquaresToEdge[idx][3] >= 1)
    l.push_back(idx + 17);
  
  // South West
  if (numSquaresToEdge[idx][1] >= 2 && numSquaresToEdge[idx][2] >= 1)
    l.push_back(idx + 15);
  
  // Weast North
  if (numSquaresToEdge[idx][2] >= 2 && numSquaresToEdge[idx][0] >= 1)
    l.push_back(idx - 10);
  
  // Weast South
  if (numSquaresToEdge[idx][2] >= 2 && numSquaresToEdge[idx][1] >= 1)
    l.push_back(idx + 6);

  for (int i : l) {
    if (i >= 0 && i <= 64) {
      if (!is_color(b->board[i], get_color(piece))) {
        add_move(idx, i);
      }
    }
  } 
}


// Generate legal next moves.
void generate_moves() {
  
  // Clear previous moves.
  moves.clear();

  for (int idx = 0 ; idx < 64 ; idx++) {

    char piece = b->board[idx];

    if (is_color(piece, b->turn)) {
      if (is_sliding_piece(piece)) {
        generate_sliding_moves(idx, piece);
      }
      if (is_pawn(piece)) {
        generate_pawn_moves(idx, piece);
      }
      if (is_knight(piece)) {
        generate_knight_moves(idx, piece);
      }
      if (is_king(piece)) {
        generate_king_moves(idx, piece);
      }
    }

  } // end for().

}
