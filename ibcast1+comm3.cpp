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
   MPI_Comm mycomm = MPI_COMM_NULL;
   MPI_Comm newcomm = MPI_COMM_NULL;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   // MPI_Comm_dup(MPI_COMM_WORLD, &mycomm);
   // MPI_Comm_split();
   //
   // int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);

   //   int color = (rank & 1), key = rank;
   int color = (rank < 3) ? 0 : 1, key = rank;

   cout << "color = " << color << ", key = " << key << endl;
   
   MPI_Comm_split(MPI_COMM_WORLD, color, key,  &newcomm);

   int newcomm_rank, newcomm_size;
   MPI_Comm_rank(newcomm, &newcomm_rank);
   MPI_Comm_size(newcomm, &newcomm_size);

   cout << "in newcomm: " << newcomm_size << "rank:" << newcomm_rank << "key = " << key << ", " << newcomm_size << endl;
     
   float buffer[5];
   
   //   int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root, 
   //               MPI_Comm comm )
   //
   //   int MPI_Ibcast(void *buffer, int count, MPI_Datatype datatype,
   //               int root, MPI_Comm comm, MPI_Request *request)
     
   if(newcomm_rank == 0)
   {
     for(int i = 0; i < 5; ++i)
       buffer[i] = (color) ? 333 : 444;
   }
   else
   {
     for(int i = 0; i < 5; ++i)
       buffer[i] = 0;

   }
   //MPI_Bcast(buffer, 5, MPI_FLOAT, 0, mycomm);
   MPI_Ibcast(buffer, 5, MPI_FLOAT, 0, newcomm, &request);
   // optional computation here.
   MPI_Wait(&request, MPI_STATUS_IGNORE);
     
   cout << "rank in COMM_WORLD: " << rank << ", local rank in newcomm:" << newcomm_rank << ": " << buffer[0] << ", " << buffer[2] << endl;

   MPI_Comm_free(&newcomm);
   MPI_Finalize();

   return 0;
}

