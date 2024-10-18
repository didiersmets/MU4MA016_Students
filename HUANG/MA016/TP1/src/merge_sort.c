#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <string.h>

void merge(int T[],int p, int q, int r)
{
  int n1 = q - p ;
  int n2 = r - q - 1 ;
  int * tmp1 = malloc(n1 * sizeof(int));
  int * tmp2 = malloc(n2 * sizeof(int));

  void * src1 = ;
  memcpy(tmp1,);

  for(int i =p; i < q,i++){
    T[i]=tmp1[i-p]
  }
  for (int j = q +1; j < r,j++){
    T[j]=tmp2[j-q-1]
  }
  
  free(tmp1);
  free(tmp2);
}

void merge_sort(int T[],int p ,int r)
{
  if (p < r ){
    int q =(p + r )/2;
    merge_sort(T,p,q);
    merge_sort(T,q+1,r);
    merge(T,p,q,r)
  }
}

int main()
{
  
  int L_N[]={10,20,50,100,200,500,1000};
  
  for (size_t i=0;i< sizeof(L_N)/sizeof(int);++i){
    int * l_sort=malloc(L_N[i] * sizeof(int));
    
    for(int j=0; j < L_N[i]; ++j){
      l_sort[j] = rand();
    }
    
    double time1= clock();
    merge(l_sort,L_N[i]);
    double time2= clock();
    double timedif = (time2-time1)/CLOCKS_PER_SEC;
    
    printf("the execution time of an array of %d random is %f \n",L_N[i],timedif);
    free(l_sort)
  }
  
}
