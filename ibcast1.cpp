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

   float buffer[5];
   
   //   int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, 
   //               MPI_Comm comm )
   //
   //   int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype,
   //               int root, MPI_Comm comm, MPI_Request *request)
     
   if(rank == 0)
   {
     for(int i = 0; i < 5; ++i)
       buffer[i] = 50*(float)i;
   }
   else
   {
     for(int i = 0; i < 5; ++i)
       buffer[i] = 0;

   }
   //MPI_Bcast(buffer, 5, MPI_FLOAT, 0, MPI_COMM_WORLD);
   MPI_Ibcast(buffer, 5, MPI_FLOAT, 0, MPI_COMM_WORLD, &request);
   // optional computation here.
   MPI_Wait(&request, MPI_STATUS_IGNORE);
     
   cout << rank << ": " << buffer[0] << ", " << buffer[2] << endl;
   
   MPI_Finalize();

   return 0;
}

