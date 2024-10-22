#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include <string.h>

void merge(int T[],int p, int q, int r)
{
    
  int N = r - p + 1;
  int *S = malloc(N * sizeof(int));
  
  int n1 = p;
  int n2 = q + 1;
  
  
  for(int i = 0; i < N; i++){
    
    if(T[n1] <=T[n2]){
      S[i]=T[n1];
      n1++;
    }else{
      S[i]=T[n2];
      n2++;
    }
    
  }
  
  memcpy(T+p,S,N); 
  
  free(S);
}

void merge_sort(int T[],int p ,int r)
{
  if (p < r ){
    int q =(p + r )/2;
    merge_sort(T,p,q);
    merge_sort(T,q+1,r);
    merge(T,p,q,r);
  }
}

int main()
{
  FILE *f;
  f = fopen("data_merge.txt","w+");
  
  int L_N[]={10,20,50,100,200,500,1000};
  
  for (size_t i=0;i< sizeof(L_N)/sizeof(int);++i){
    int * l_sort=malloc(L_N[i] * sizeof(int));
    
    for(int j=0; j < L_N[i]; ++j){
      l_sort[j] = rand();
    }
    
    double time1= clock();
    
    
    merge_sort(l_sort,L_N[i]/2,L_N[i]);
    double time2= clock();
    double timedif = (time2-time1)/CLOCKS_PER_SEC;
    
    //printf("the execution time of an array of %d random is %f \n",L_N[i],timedif);
    
    fprintf(f,"%d %f \n",L_N[i],timedif);
    
    free(l_sort);
  }
  
}
