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
  long   i2,j2,k2;
  double ** mul1;
  double ** mul2;
  double ** res;

  double * rmul1;
  double * rmul2;
  double * rres;

  

  mul1=malloc(sizeof(double**)*N);
  mul2=malloc(sizeof(double**)*N);
  res=malloc(sizeof(double**)*N);



  for (i = 0; i < N; ++i)
    {
      mul1[i]=(double*)malloc(sizeof(double)*N);
      mul2[i]=(double*)malloc(sizeof(double)*N);
      res[i]=(double*)malloc(sizeof(double)*N);
    }

  t=stoptime();


  // Idea from Drepper

#define SM (CLS / sizeof (double))
  for (i = 0; i < N; i += SM)
    for (j = 0; j < N; j += SM)
      for (k = 0; k < N; k += SM)
	for (  i2 = 0, rres = &res[i][j],    rmul1 = &mul1[i][k]; 
	       i2 < SM;
	       ++i2,   rres += N, rmul1 += N)
	  for (k2 = 0, rmul2 = &mul2[k][j];
	       k2 < SM; 
	       ++k2, rmul2 += N)
	    for (j2 = 0; j2 < SM; ++j2)
	      rres[j2] += rmul1[k2] * rmul2[j2];

  t=stoptime()-t;

  printf("calculation time : %f\n",t);
  //printf("gflops/s         : %f\n",((2.0*m*n*k)*1E-9)/t);
  printf("gflops/s         : %f\n",((2.0*N*N*N)*1E-9)/t);


  printf("res[i][j]:%f\n",res[i-1][j-1]);
}

