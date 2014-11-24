#include <stdio.h>
#include <sys/time.h>
#define N 1000


double stoptime(void)
{
  struct timeval t;
  gettimeofday(&t,NULL);
  return (double) t.tv_sec + t.tv_usec/1000000.0;
}


int main()
{
  double t;
  long   i,j,k;
  double ** mul1;
  double ** mul2;
  double ** res1;

  mul1=malloc(sizeof(double**)*N);
  mul2=malloc(sizeof(double**)*N);
  res1=malloc(sizeof(double**)*N);



  for (i = 0; i < N; ++i)
    {
      mul1[i]=(double*)malloc(sizeof(double)*N);
      mul2[i]=(double*)malloc(sizeof(double)*N);
      res1[i]=(double*)malloc(sizeof(double)*N);
    }

  t=stoptime();

  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      for (k = 0; k < N; ++k)
        res1[i][j] += mul1[i][k] * mul2[k][j];

  t=stoptime()-t;

  printf("calculation time : %f\n",t);
  //printf("gflops/s         : %f\n",((2.0*m*n*k)*1E-9)/t);
  printf("gflops/s         : %f\n",((2.0*N*N*N)*1E-9)/t);


  printf("res1[i][j]:%f\n",res1[i-1][j-1]);
}

