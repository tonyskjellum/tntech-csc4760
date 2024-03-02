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

   
   if(0 == rank)
     {
       int mysendvalue = 12345, myrecvvalue = 0;
       MPI_Isend(&mysendvalue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request[0]);
       MPI_Irecv(&myrecvvalue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request[1]);
       MPI_Waitall(2, request, MPI_STATUSES_IGNORE);
       cout << rank << ": My received value is " << myrecvvalue << endl;
     }
   else if(1 == rank)
     {
       int mysendvalue = 54321, myrecvvalue = 0;
       MPI_Isend(&mysendvalue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request[0]);
       MPI_Irecv(&myrecvvalue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request[1]);
       MPI_Waitall(2, request, MPI_STATUSES_IGNORE);
       cout << rank << ": My received value is " << myrecvvalue << endl;

     }

   MPI_Finalize();

   return 0;
}

