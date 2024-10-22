#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

void bubble_sort(int adress[], int n)//adress if the array and the number of elements
{
  for (int i=0;i < n-1 ;++i){
    bool move = false;
    for (int j =0;j < n-1;++j){
      if (adress[j] > adress[j+1]){
	int copy = adress[j];
	adress[j] = adress[j+1];
	adress[j+1] = copy;
	move = true;
      }
    }
    if (move == false){
      break;
    }
  }
}


int main()
{
  
  int L_N[]={10,20,50,100,200,500,1000};
  
  FILE * f;
  f=fopen("data_bubble","w+");
  
  for (size_t i=0;i< sizeof(L_N)/sizeof(int);++i){
    int * l_sort=malloc(L_N[i] * sizeof(int));
    
    for(int j=0; j < L_N[i]; ++j){
      l_sort[j] = rand();
    }
    
    double time1= clock();
    bubble_sort(l_sort,L_N[i]);
    double time2= clock();
    double timedif = (time2-time1)/CLOCKS_PER_SEC;
    
    //printf("the execution time of an array of %d random is %f \n",L_N[i],timedif);
    fprintf(f,"%d %f \n",L_N[i],timedif);
    free(l_sort);
  }
  
}
