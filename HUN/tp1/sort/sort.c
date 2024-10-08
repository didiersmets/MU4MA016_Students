
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void BubbleSort(int *A, int N) {
  int counter = 0;
  int swap;
  while (counter < N-1) {
    if (A[counter]>A[counter+1]){ // shall swap
      swap = A[counter];
      A[counter] = A[counter+1];
      A[counter+1] = swap;
      counter = 0;
    } else {counter ++ ;}
  }
}

void InsertionSort(int *A, size_t N) {
  int swap;
  int j;

  for (int i=0; i<N-1; i++){
    j=i;
    while ( j>=0 &&  A[j+1]<A[j] ) {
      swap = A[j];
      A[j] = A[j+1];
      A[j+1] = swap;
      j--;
    }
  }
}


void Merge(int *T, size_t p, size_t q, size_t r) {
  size_t i=p;
  size_t j=q+1; //j<=r

  int ai = T[i];
  int aj = T[j];

  while (ai < aj) {
    i ++;
  }





  
}



int main() {

  int A[10] = {11, 54, 23, 6, 7, 89, 4, 2, 8, 45};
  int B[10] = {11, 54, 23, 6, 7, 89, 4, 2, 8, 45};
  for (int i=0; i<10; i++){printf("%d ", A[i]);} printf("\n");
  
  BubbleSort(A, 10);
  for (int i=0; i<10; i++){printf("%d ", A[i]);} printf("\n");

  InsertionSort(B, 10);
  for (int i=0; i<10; i++){printf("%d ", B[i]);}




  
  return 0;
}
