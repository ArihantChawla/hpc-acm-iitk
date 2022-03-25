/*****************************************************************************
About: Serial program to multiply two matrices A and B and store into C matrix
Objective : Use OpenMP to make the program parallel with correct output.
            Time the serial program, and parallel program with different no. of threads.
*****************************************************************************/

#include<stdio.h>
#include<string.h>
#include "mpi.h"


#define BUFFER_SIZE 20



#define N 3000

int main(argc,argv)
int argc;
char *argv[];
{

      int x,y,z;
      double  a[N][N],b[N][N],c[N][N];

      printf("\n    Simple Matrix Multiplication: N=%d\n\n",N);

     for(x=0;x<N;x=x+1)
       for(y=0;y<N;y=y+1)
        {
          a[x][y]=((y+2)*1.0)/(5.0+x*1.0);
          b[x][y]=((x+y)*1.0)/((y+1)*1.0);
          c[x][y]=0.0;
//	  printf("%lf %lf %lf", a[x][y] ,b[x][y], c[x][y]);	
        }


    int  MyRank,Numprocs, Destination, Source, iproc;
    int  Destination_tag, Source_tag; 
    int  root = 0;
    int  IntMessage;
    double  DoubleMessage; 

    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
    MPI_Comm_size(MPI_COMM_WORLD,&Numprocs); 

    if (MyRank == root) 
    {
	for(x=0;x<N;x=x+1) {
            for(y=0;y<N;y=y+1) {
		double temp = 0.0;
		for(iproc = 1 ; iproc < Numprocs ; iproc++) {	     
		    Destination = iproc;
		    Destination_tag = x*N + y;
		    MPI_Send(&Destination_tag, BUFFER_SIZE, MPI_INT, Destination, Destination_tag, MPI_COMM_WORLD);	
	            MPI_Recv(&DoubleMessage, BUFFER_SIZE, MPI_DOUBLE, MPI_ANY_SOURCE, Destination_tag, MPI_COMM_WORLD, &status);
		    temp += DoubleMessage;	
		}
		c[x][y] = temp;
	    }
	}
    printf("%lf\n",c[N-1][N-1]);
    }
    else 
    {
	MPI_Recv(&IntMessage, BUFFER_SIZE, MPI_INT, root, MPI_ANY_TAG, MPI_COMM_WORLD,&status);
	int tempx, tempy;
	double tbs= 0.0;
	tempx = IntMessage / N;
	tempy = IntMessage % N;
	for (int i=(MyRank-1);i<N;i=(i+Numprocs-1)) {
	    tbs += a[tempx][i]*b[i][tempy];
	}
	MPI_Send(&tbs, BUFFER_SIZE, MPI_DOUBLE, root, IntMessage, MPI_COMM_WORLD);	
    }
    MPI_Finalize();
    return 0;
}
