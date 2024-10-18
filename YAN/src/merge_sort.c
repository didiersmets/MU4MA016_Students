#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "merge.h"

//sorted one in S, try to copy it in t, swap will be easier

void Merge(int* from , int p, int q, int r, int* to){
	size_t n = r-p+1;
	size_t t1 = p;
	size_t t2 = q+1;
	printf("verify\n");

	for(int i= q+1; i< r+1; i++){
		printf(" %d, ",to[i]);
	}
	printf("\n");
	for(int i= p; i< q+1; i++){   
		printf(" %d, ",from[i]);
	}
	printf("\n");
	printf("Merge");
	for(size_t k=0; k<n;k++){
		if( (t1<q+1) && (t2==r+1 || from[t1]<= from[t2])){
			to[k] = from[t1];
			t1++;
		}
		else{
			to[k] = from[t2];
			t2++;
		}
		printf(" %d, ",to[k]);
		
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
void Merge_sort(int*T , int n){
	int * S = malloc(n*sizeof(int));
	memcpy(S,T,n*sizeof(int));
	MergeSort(S,0,n-1,T);
	for(int i= 0; i< n; i++){
		printf(" %d, ",T[i]);
	}
	printf("\n");
	for(int i= 0; i< n; i++){   
		printf(" %d, ",S[i]);
	}
	free(S);
	printf("\n");
	
}

