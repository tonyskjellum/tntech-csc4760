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

   //std::cout << rank << " of " << size << "sends hello world to you!" << std::endl;
   cout << rank << " of " << size << "sends hello world to you!" << endl;
   
   MPI_Finalize();

   return 0;
}

