#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

/* Input: 
 * - array T* with len elements where the sub-arrays [0,...,size-1], [size,...,2*size-1], ..., [len/size,...,len-1] are sorted
 * - array C* with len elements
 *
 * Output:
 * - array T* with len elements
 * - array C* with len elements where the sub-arrays [0,...,2*size-1], [size,...,4*size-1], ..., [len/size,...,len-1] are sorted
 */
void merge(int *T, int* C, int len, int size){

	for(int i=0; i<len; i+=size){
		int p = i;
		int end = i+size <= len ? i+size : len; 
		int q = i+(size/2) <= end ? i+(size/2) : end;
		int q0 = q; 

		for(int k = i; k<end; k++){
			if( p<q0 && (q==end||T[p]<=T[q]) ) {
				C[k] = T[p++];
			} else {
				C[k] = T[q++];
			}
		}
	}
}


void MergeSort(int *T, int len){

	/* Save the memory address known to the user.
	 * We will always sort from the array located at T* to C*. 
	 */
	
	int *T0 = T;

	if(len>0){
		
		/* Allocate second array to ping-pong */
		int* C = (int*) malloc(len*sizeof(int)); 

		for(int size=2; size <= len*2; size*=2){
			merge(T,C,len,size);
				
			/* Swap pointers */
			int* temp = T;
			T = C;
			C = temp;
		}
		
		/* Copy the sorted data to T0 */
		for(int k=0; k<len; k++){
			T0[k] = T[k];
		}
	}
}

int main(){
		
	int N = 9;
		
	int* T = (int*) malloc(N*sizeof(int)); 

	for(int i=0; i<N; i++){
		T[i] = rand();
		}

	printf("initial array:\n");
	for(int k=0; k<N; k++){
		printf("%d\n", T[k]);
	}
	printf("\n");

	MergeSort(T,N);

	printf("sorted array:\n");
	for(int k=0; k<N; k++){
		printf("%d\n", T[k]);
	}
	printf("\n");

	return 0;
}
