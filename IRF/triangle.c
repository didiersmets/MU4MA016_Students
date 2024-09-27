#include <stdio.h>
#include <stdlib.h>
int *trianglepascal(int n)
{
  int *T=malloc(n*n*sizeof(int));
  for (int i = 0; i < n; i++) {
    T[i*n+0] = 1;
    T[i*n+i] = 1;
    for (int j =0; j < n; j++) {
      if (j<i && 0<j){
	T[i*n + j] = T[(i-1)*n+(j-1)]+T[(i-1)*n+j];
      }
    }
  }
  return T;
}

int main(int argc, char** argv)
{
   int n = atoi(argv[1]);
   int *T = trianglepascal(n);
   for (int i = 0; i<n; i++){
     for (int j = 0; j<=i; j++){
       printf("%d", T[i*n+j]);
     }
     printf("\n");
   }
   return 0;
}
  
