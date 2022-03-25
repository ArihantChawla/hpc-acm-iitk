#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

#define BUFFER_SIZE 20


int main(argc,argv)
int argc;
char *argv[];
{
    int MyRank, Numprocs, Destination, Source, iproc;
    MPI_Status status;
    int Message; 

    /*....MPI initialization.... */    
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs); 

    if (MyRank == 1) 
    {
        int sum = 1;
        int t = Numprocs / 2 - 1 ;
	while(t--){
	    MPI_Recv(&Message, BUFFER_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    	    sum = sum + Message;
//	    printf("%d",t);	
	}
	printf("Sum of odd ranks is %d\n", sum);
    }
    
    else if (MyRank % 2 == 1) 
    {
	MPI_Send(&MyRank, BUFFER_SIZE, MPI_INT, 1,MyRank, MPI_COMM_WORLD);
    }

    else if (MyRank == 0)
    {
	int sum = 0;
        int t = (Numprocs-1) / 2;
        while(t--){
            MPI_Recv(&Message, BUFFER_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            sum = sum + Message;
//          printf("%d",t);
        }
	printf("Sum of even ranks is %d\n", sum);
    }			

    else 
    {
//	sprintf(Message, "%d", MyRank);
        MPI_Send(&MyRank, BUFFER_SIZE, MPI_INT, 0,MyRank, MPI_COMM_WORLD);
    }


//    printf("I am %d\n", MyRank);    
    MPI_Finalize();
    return(1);	
}

