//
// Class material for Parallel Programming
// Author: Anthony Skjellum, PhD
// (C) 2024 Anthony Skjellum. All rights reserved.
// Released under a 3-Clause BSD License
//

#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
   int rank, size;
   MPI_Request request[2];
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   float sendbuf[1], recvbuf[1], buffer[1];
   
   recvbuf[0] = -555;
   sendbuf[0] = (float)rank;

   //   int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count,
   //                      MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,
   //                      MPI_Request * request)


   MPI_Iallreduce(sendbuf, recvbuf, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD, &request[0]);
   MPI_Waitall(1, &request[0], MPI_STATUSES_IGNORE);

   cout << rank << ": " << recvbuf[0] << endl;

   MPI_Finalize();
   
   return 0;
}

