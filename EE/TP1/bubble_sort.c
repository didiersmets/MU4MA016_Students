#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void bubble(int *B, int size_A)
{
	int temp = 0;
	for (int j = 0; j<size_A; j++){
		int i = 0;
		while (i < size_A-j){
			if (B[i] > B[i+1]){
				temp = B[i];
				B[i] = B[i+1];
				B[i+1] = temp;
			}else{
				i++;

			}
		}
	}
}

int main (int argc, char **argv){
	FILE *fptr = fopen("data.txt", "w");
	int N[] = {10,20,50,100,200,500,1000};                                  
        for (int j = 0; j < 7; j ++){                                           
		int *T = malloc(N[j] * sizeof(int));                            
                srand(time(NULL));                                              
                for (int i = 0; i < N[j]; i ++){                                
                        T[i] = rand() % 100 + 1;                                
                }                                                               
                clock_t begin = clock();                                       
                bubble(T, N[j]);                                            
                clock_t end = clock();                                          
                double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;     
                fprintf(fptr, " %d", N[j]);                                     
                fprintf(fptr, " %f", time_spent);                               
                fprintf(fptr," \n");                                            
                printf(" %f", time_spent);                                      
                free(T);                                                        
        }                                                                       
        printf(" \n");                                                          
        fclose(fptr);                                                           
	return 0;
}
