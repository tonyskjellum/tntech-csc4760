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
   MPI_Request request;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   float sendbuf[1], recvbuf[1];
   
   //   int MPI_Ireduce(const void *sendbuf, void *recvbuf,
   //               int count, MPI_Datatype datatype, MPI_Op op, int
   //               root, MPI_Comm comm, MPI_Request *request)

   recvbuf[0] = -555;
   sendbuf[0] = (float)rank;

   //MPI_Ireduce(sendbuf, recvbuf, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD, &request);
   MPI_Ireduce(sendbuf, recvbuf, 1, MPI_FLOAT, MPI_MAX, 0, MPI_COMM_WORLD, &request);
   
   MPI_Wait(&request, MPI_STATUS_IGNORE);

   if(rank == 0)
   {
     //     cout << "The result is " << recvbuf[0] << " vs. " << (size-1)*size/2.0 << endl;
     cout << "The result is " << recvbuf[0] << " vs. " << (size-1) << endl;
   }

   
   MPI_Finalize();

   return 0;
}

