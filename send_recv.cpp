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
  
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   if(0 == rank)
     {
       int myvalue = 12345;
       MPI_Send(&myvalue, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
     }
   else if(1 == rank)
     {
       int myvalue = 0;
       MPI_Recv(&myvalue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       cout << "My received value is " << myvalue << endl;
     }

   MPI_Finalize();

   return 0;
}

