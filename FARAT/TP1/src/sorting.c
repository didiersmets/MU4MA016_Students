#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include "/home/chloe/016/MU4MA016_Students/FARAT/TP1/include/sorting.h"



void Bubble_sort(int *t,int l){
	//int k = (int) (sizeof(t)/sizeof(t[0]));
	//assert (l == k);

	int i = 0;
	for (i=0; i<(l-1); i++){

		int j=0;
		for (j=0; j<(l-i); j++){

			if (t[j]>t[j+1]){

				int cp = t[j];
				t[j] = t[j+1];
				t[j+1] = cp;   
			}
		} 
	}
}



void Insertion_sort(int *t,int l){

	int k = 1;
	for (k=1; k<l; k++){

		for(int j=k;j>0;j--){

			if (t[j]<t[j-1]){   //essaye avec un for   
				int cp = t[j-1];
				t[j] = t[j-1];
				t[j-1] = cp;   
			} 
		}
	}
}


static void merge(int *T, int p, int q, int r){
	assert ((p<=q)&&(q<r));//p ≤ q <r
	                     //T[p],T[p + 1],...T[q]  and T[q+1], T[q+2],...T[r] are sorted 
	int i1 =p;
	int i2 = q+1;
	int *T_bis = malloc(sizeof(int)*(r-p+1));

	for (int i =0; i<r-p+1; i++) {
		if (i1 <= q && (i2>r || T[i1] <= T[i2])){
			T_bis[i] = i1++;
		}
		else{
			T_bis[i] = i2++;
		}
	}

	int k = 0;
	for (k=0;k<r-p+1;k++){
		T[p+k] = T[T_bis[k]];
	}

	free(T_bis);
}


static void Merge_bis(int *T, int p, int r){
	if (p<r){
		int q = floor((p+r)/2);   //renvois la partie entière
		Merge_bis(T, p, q);
		Merge_bis(T, q+1, r);
		merge(T, p, q, r);
	}
}



void Merge_sort(int *t,int l){
	Merge_bis(t, 0, l-1);
}
