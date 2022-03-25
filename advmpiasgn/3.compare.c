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
 
  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  chunk = N/size;
  int hmm[N];	
  // data initialization
  if (!rank) {
    for (i=0; i<N; i++)
      arr[i] = i+1;
    for(i=1;i<size;i++)
        MPI_Send(arr,N,MPI_INT,i,i,MPI_COMM_WORLD); 
  }	  
  else
     MPI_Recv(arr,N,MPI_INT,0,MPI_ANY_TAG, MPI_COMM_WORLD,&status);

 
  //perform local sum
  for (int j=rank*chunk;j<(rank+1)*chunk;j++)
    localsum = localsum + arr[j]; 
    if(rank)
	{
//printf("%d",rank);
	MPI_Send(&localsum,1,MPI_INT,0,rank,MPI_COMM_WORLD);	
	//printf("%d",rank);
}
  // rank 0 computes the sums
  if (rank == 0) {
   sum = localsum;
   //printf("%d",localsum);
   int temp;
   for (i=1; i<size; i++){ 
//     printf("%d",i);
       MPI_Recv(&temp,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD, &status);
  //   printf("%d",i);
     sum = sum + temp;}	
   printf("%d\n", sum);
  }

  MPI_Finalize();
  return 0;

}

