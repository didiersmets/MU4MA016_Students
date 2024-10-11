#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

void insertion(int* adress[], int n)//adress if the array and the number of elements
{
  
}


int main()
{
  
  int L_N[]={10,20,50,100,200,500,1000};
  
  for (size_t i=0,i< sizeof(L_N)/sizeof(struct L_N),++i){
    int* l_sort[L_N[i]];
    
    for(int j=0, j < L_N[i], ++j){
      l_sort[j] = rand();
    }
    
    double time1= clock();
    insertion(l_sort,L_N[i]);
    double time2= clock();
    double timedif = (time2-time1)/CLOCKS_PER_SEC;
    
    printf("the execution time of an array of %d random is %f",L_N[i],timedif);
    
  }
  
}
