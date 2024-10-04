#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

void Merge(int* T, int p, int q, int r){
	
	int size_C = r-p;
	int C[size_C];
	
	int p0 = p;
	int q0 = q;

	for(int k = 0; k<size_C; k++){
		if( ((p<q0)&&(q==r))  || (T[p]<=T[q]) ) {
			C[k] = T[p++];
		} else {
			C[k] = T[q++];
		}
	}

	
	for(int k = 0; k<size_C; k++){
		T[p0+k] = C[k];
	}
}


void MergeSort(int *T, int p, int r){
	if(p<r){
		int q = (p+r)/2;
		MergeSort(T,p,q);		
		MergeSort(T,q+1,r);		
		Merge(T,p,q,r);		
	}
}

int main(){
	
	FILE *file = fopen("data.txt", "w");
	
	for(int k=0; k<100; k++){
		
		int N = (int) pow(2.,(double)k);
		int T[N];

		for(int i=0; i<N; i++){
			T[i] = rand();
		}

		clock_t t = clock();
		MergeSort(T,0,N-1);
		t = clock() - t;
		double time = ((double)t)/CLOCKS_PER_SEC;

		fprintf(file, "%d %lf \n", N, time); 
	}

	return 0;
}
