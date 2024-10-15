#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "merge.h"

//sorted one in S, try to copy it in t, swap will be easier

void Merge(int* T , int p, int q, int r, int* S){
	size_t n = r-p+1;
	size_t t1 = p;
	size_t t2 = q+1;

	printf("Merge");
	for(size_t k=0; k<n;k++){
		if( (t1<q+1) && (t2==r+1 || T[t1]<= T[t2])){
			S[k] = T[t1];
			t1++;
		}
		else{
			S[k] = T[t2];
			t2++;
		}
		printf(" %d, ",S[k]);
		
	}	
	printf("\n");
}

void MergeSort(int* from, int p, int r,int* to){
	if (p<r){
		int q = (p+r)/2;
		printf("p = %d, q = %d r = %d\n",p,q,r);
		printf("1 ");
		MergeSort(to, p,q,from);
		printf("\n 2 ");
		MergeSort(to,q+1,r,from);
		printf("\n final ");
		printf("2:  p = %d, q = %d r = %d\n",p,q,r);
		Merge(from,p,q,r,to);

	}
}
void Merge_sort(int* T, int n){
	int * S = malloc(n*sizeof(int));
	memcpy(S,T,n*sizeof(int));
	MergeSort(T,0,n-1,S);
	for(int i= 0; i< n-1; i++){
		printf(" %d, ",T[i]);
	}
	printf("\n");

	free(S);
}

