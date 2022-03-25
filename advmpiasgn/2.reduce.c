#include <stdio.h>
#include "mpi.h"
#define N 1073741824 

int main (int argc, char *argv[])
{

  int rank, size, color, sum=0, localsum=0, i, chunk;
  int arr[N], recv_arr[N], partialsum[N];
  MPI_Status status;
  int newrank, newsize;
  MPI_Comm newcomm;
  int globalsum;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  chunk = N/size;
  int hmm[chunk];
  // data initialization
  if (!rank)
  for (i=0; i<N; i++)
     arr[i] = i+1;
     if (i<chunk)
        hmm[i] = 0;

  // data distribution
  MPI_Scatter (arr,chunk,MPI_INT,hmm,chunk,MPI_INT,0,MPI_COMM_WORLD);

  //perform local sum
  for (int j=0;j<chunk;j++)
    localsum = localsum + hmm[j];


  // Reduce at rank 0  
  
  MPI_Reduce(&localsum, &globalsum, 1, MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);

  MPI_Finalize();
  if (!rank)
	  printf("%d\n",globalsum);  
  return 0;

}

