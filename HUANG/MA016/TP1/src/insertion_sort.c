#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

void insertion(int A[], int n)//adress if the array and the number of elements
{
  for (int i=1;i < n;++i){
    int tmp = A[i];
    int j = i;
    while(j>0 && tmp < A[j-1]){
      A[j]=A[j-1];
      j--;
    }
    A[j]=tmp;
  }
  
}


int main()
{
  
  int L_N[]={10,20,50,100,200,500,1000};
  
  FILE *f;
  f= fopen("data_insertion","w+");
  
  for (size_t i=0;i< sizeof(L_N)/sizeof(int);++i){
    int * l_sort = malloc(L_N[i] * sizeof(int));
    
    for(int j=0; j < L_N[i]; ++j){
      l_sort[j] = rand();
    }
    
    double time1= clock();
    insertion(l_sort,L_N[i]);
    double time2= clock();
    double timedif = (time2-time1)/CLOCKS_PER_SEC;
    
    //for(int i=0 ;i<10;i++){
    //	printf("%d \n",l_sort[i]);
    //}
    
    //printf("the execution time of an array of %d randoms is %f \n",L_N[i],timedif);
    
    fprintf(f,"%d %f \n",L_N[i],timedif);
    free(l_sort);
  }
  
}
