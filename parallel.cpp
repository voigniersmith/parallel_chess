// Parallel stuff here.

/*
  We will be using tag 0 for work messages, tag 1 for ACK messages and
  tag 2 for poll messages, tag 3 for terminate.
*/


// Producer ends consumers.
void terminate() {
  // Send p - 1 terminate messages.
}

// Producer execution.
void producer(int buf_size) {
  int buf;
//  MPI_Status status;
  
  // Create queue of moves.
  // Create queue of results

  // While work in queue.

    // Wait for poll or ACK  message.
//    MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    // Send work
//    MPI_Send(&buf, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);

    // If ACK Insert response into results
}


// Consumer execution.
void consumer() {
  // Send Poll for work

  // While work to do
  while (1) {
    // Wait for work
//    MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

    // Do work

    // Send results
//    MPI_Send(&rw, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
  }

}


