// Parallel stuff here.

/*
  We will be using tag 0 for work messages, tag 1 for ACK messages and
  tag 2 for poll messages, tag 3 for terminate.
*/


struct work_msg {
  int d;
  struct board b;
  struct move m;
};

struct res_msg {
  int e;
  struct move m;
};

// Producer ends consumers.
void terminate() {
  MPI_Status status;

  // Send p - 1 terminate messages.
  for (int i = 1; i < npes; i++) {
    MPI_Recv(NULL, 0, MPI_BYTE, i, 2, MPI_COMM_WORLD, &status);
    MPI_Send(NULL, 0, MPI_BYTE, i, 3, MPI_COMM_WORLD);
  }
}

// Producer execution.
struct move producer() {
  struct res_msg r;
  struct work_msg w;
  struct move m;
  MPI_Status status;
  
  // Create queue of moves.
  std::vector<struct move> cur_moves = moves; 

  // Create queue of results
  std::vector<std::pair<int, struct move> > results;

  b->turn = b->turn == 'z' ? 'Z' : 'z';
  
  // While work in queue.
  while (results.size() != moves.size()) {
    // Wait for poll or ACK  message.
    MPI_Recv(&r, sizeof(struct res_msg), MPI_BYTE, MPI_ANY_SOURCE,
      MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    
    if (status.MPI_TAG == 1) { // If ACK insert response into results.
      results.push_back(std::make_pair(r.e, r.m));
    
    } else if (status.MPI_TAG == 2 && cur_moves.size() != 0) { // If polled and work to do.
      m = cur_moves.back();
      cur_moves.pop_back();

      // Make Message.
      char c = make_move(m.start, m.target);
      w.d = global_depth - 1;
      w.b = *b;
      w.m = m;
      unmake_move(m.start, m.target, c);

      // Send work
      MPI_Send(&w, sizeof(struct work_msg), MPI_BYTE, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
    
    } else if (cur_moves.size() == 0) { // Polled but no work to do.
      // Send nothing.
      MPI_Send(&w, 0, MPI_BYTE, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
    }
  }
  
  b->turn = b->turn == 'z' ? 'Z' : 'z';

  // Sort moves by eval.
  std::sort(results.begin(), results.end(), compare);

  return results.at(0).second;
}


// Consumer execution.
void consumer() {
  struct res_msg r;
  struct work_msg w;
  struct move m;
  MPI_Status status;

  // While work to do
  while (1) {
    // Send poll
    MPI_Send(&w, 0, MPI_BYTE, 0, 2, MPI_COMM_WORLD);

    // Wait for work
    MPI_Recv(&w, sizeof(w), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &status);

    if (status.MPI_TAG == 3) {
      break;
    }

    printf("Rank %d: %c turn, move %d->%d\n", myrank, w.b.turn, w.m.start, w.m.target);
    fflush(stdout);
    // Do work
    b->turn = w.b.turn;
    b->board = w.b.board;
    b->layout = w.b.layout;

    print_board();
    fflush(stdout);

    r.e = search(w.d, w.d);
    printf("After search %d\n", myrank);
    fflush(stdout);
    r.m = w.m;

    // Send results
    MPI_Send(&r, sizeof(r), MPI_BYTE, 0, 1, MPI_COMM_WORLD);
  }

}


