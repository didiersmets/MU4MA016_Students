#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>


void MergeSort(int *T, int p, int r){

	int* T0 = T;
	int size_T = (r-p)+1;

	if(size_T>0){
		
		int* C = (int*) malloc(size_T*sizeof(int)); // second array to merge into

		for(int size=2; size <= size_T; size*=2){
			
			for(int i=0; i<size_T; i+=size){

				printf("i: %d\n", i);
				
				// Merge sub-arrays
				
				int p = i;
				int q = i+size/2;
				int q0 = q;
				int end = i+size <= r ? i+size : r+1; 

				for(int k = i; k<end; k++){
					if( ((p<q0)&&(q==end))  || (T[p]<=T[q]) ) {
						C[k] = T[p++];
					} else {
						C[k] = T[q++];
					}
				}

			}
		
			// swap pointers
			int* temp = T;
			T = C;
			C = temp;


			printf("sorted array (%d)\n", size);
			for(int k=p; k<=r; k++){
				printf("%d\n", T[k]);
			}
			printf("\n");
		
		}



		for(int k=p; k<=r; k++){
			T0[k] = T[k];
		}
	}
}

int main(){
	
	// FILE *file = fopen("data.txt", "w");
	
	for(int k=3; k<4; k++){
		
		int N = (int) pow(2.,(double)k);
		
		int* T = (int*) malloc(N*sizeof(int)); 

		for(int i=0; i<N; i++){
			T[i] = rand();
		}

		printf("initial array:\n");
		for(int k=0; k<N; k++){
			printf("%d\n", T[k]);
		}
		printf("\n");

		MergeSort(T,0,N-1);

		printf("sorted array:\n");
		for(int k=0; k<N; k++){
			printf("%d\n", T[k]);
		}
		printf("\n");
		
		/*
		clock_t t = clock();
		MergeSort(T,0,N-1);
		t = clock() - t;
		double time = ((double)t)/CLOCKS_PER_SEC;

		fprintf(file, "%d %lf \n", N, time);
		*/
	}

	return 0;
}
