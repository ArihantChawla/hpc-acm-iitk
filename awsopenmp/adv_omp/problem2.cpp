// Compile: g++ -fopenmp problem2.cpp -o problem2
// Run: ./problem2

#include <cassert>
#include <iomanip>
#include <iostream>
#include <omp.h>

#define N 40
#define THRESHOLD 20

using namespace std;

long ser_fib(int n) {
  if (n == 0 || n == 1) {
    return (n);
  }
  return ser_fib(n - 1) + ser_fib(n - 2);
}

int fib[N];
fib[0] = 0;
fib[1] = 1;
for (int i = 2,i<N,i++)
	fib[i] = -1;

long omp_fib(int n) {
  if (fib[n] != -1)
	return fib[n];
  if (fib[n-1] != -1)
	if (fib[n-2] != -1)
	{
		fib[n] = fib[n-1] + fib[n-2];
		return fib[n];
	}
	else 
	{
		int temp;
		#pragma omp single
	pragma omp task 
			temp = omp_fib(n-2)
		fib[n] = fib[n-1] + temp;
		return fib[n];
	}
  else {
        if (fib[n-2] != -1)
        {
	       int temp;
                #pragma omp single
                #pragma omp task
                        temp = omp_fib(n-1)
                fib[n] = temp + fib[n-2];
                return fib[n];
        }
        else
        {
                int temp1 temp2;
                #pragma omp single
                #pragma omp task
                        temp2 = omp_fib(n-2)
		#pragma omp task 
			temp1 = omp_fib(n-1)
                fib[n] = temp1 + temp2;
                return fib[n];
	}
  }		
}

int main(int argc, char** argv) {
  std::cout << std::fixed;
  std::cout << std::setprecision(5);

  double start, end;

  start = omp_get_wtime();
  long s_fib = ser_fib(N);
  end = omp_get_wtime();
  cout << "Serial time: " << (end - start) << " seconds\n";

  start = omp_get_wtime();
  long v1_fib = omp_fib(N);
  end = omp_get_wtime();
  assert(s_fib == v1_fib);
  cout << "OMP Version time: " << (end - start) << " seconds\n";

  return EXIT_SUCCESS;
}
