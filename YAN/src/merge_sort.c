#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

void Merge(int* T , int p, int q, int r){
	size_t n = r-p+1;
	size_t t1 = p;
	size_t t2 = q+1;
	int* C = malloc(n*sizeof(int));


	for(size_t k=0; k<n;k++){
		if( (t1<q+1) && (t2==r+1 || T[t1]<= T[t2])){
			C[k] = T[t1];
			t1++;
		}
		else{
			C[k] = T[t2];
			t2++;
		}
		printf("%d \n",C[k]);
	}
	free(C);	
}

void MergeSort(int* T, int p, int r){
	if (p<r){
		int q = (p+r)/2;
		MergeSort(T, p,q);
		MergeSort(T,q+1,r);
		Merge(T,p,q,r);

	}
}

