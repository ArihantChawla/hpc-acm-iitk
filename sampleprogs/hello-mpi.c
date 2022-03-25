// Compile: mpiicc hello-mpi.c
// Execute: mpiexec.hydra -n 2 ./a.out

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(argc,argv)
int argc;
char *argv[];
{
    int  MyRank,Numprocs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
    printf("MPI Rank=%d \n",MyRank);
    system("hostname");
    MPI_Finalize();
}


