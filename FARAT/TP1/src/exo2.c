#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include "sorting.c"

//file for gnuplot
#include "Merge_sort.dat"
#include "Insertion_sort.dat"
#include "Bubble_sort.dat"


int main(void)
{
	int val[7] = {10, 20, 50, 100,200,500,1000};

	FILE *bubble = fopen("Bubble_sort.dat", "w");
	//fprintf(bubble, "%s   %s\n","N","Time");

	FILE *insert = fopen("Insertion_sort.dat", "w");
	//fprintf(insert, "%s   %s\n","N","Time");

	FILE *merg = fopen("Merge_sort.dat", "w");
	//fprintf(merg, "%s   %s\n","N","Time");

	int i = 0;
	for (i = 0; i<7; i++){ 
		int N = val[i];
		int *T = malloc(N*sizeof(int));
		int k=0;

		for (k=0;k<N;k++){
			int r = rand();
			r = r %271;
			T[k] = r;
		}

		

		int *tab_bubble = malloc(N*sizeof(int));
		k=0;
		for (k=0;k<N;k++){
			tab_bubble[k] = T[k];
		}

		clock_t time = clock();
		Bubble_sort(tab_bubble,N);
		time = clock() - time;
		double time_in_sec = ((double) time)/ CLOCKS_PER_SEC;
		fprintf(bubble, "%d\t%f\n",N,time_in_sec);

		free(tab_bubble);


		

		int *tab_insert = malloc(N*sizeof(int));
		k=0;
		for (k=0;k<N;k++){
			tab_insert[k] = T[k];
		}

		time = clock();
		Insertion_sort(tab_insert, N);
		time = clock()-time;
		time_in_sec = ((double) time)/ CLOCKS_PER_SEC;
		fprintf(insert, "%d\t%f\n",N,time_in_sec);

		free(tab_insert);


		
		int *tab_merge = malloc(N*sizeof(int));
		k=0;
		for (k=0;k<N;k++){
			tab_merge[k] = T[k];
		}

		time = clock();
		Merge_sort(tab_merge, N);
		time = clock() - time;
		time_in_sec = ((double) time)/ CLOCKS_PER_SEC;
		fprintf(merg, "%d\t%f\n",N,time_in_sec);

		free(tab_merge);
		free(T);


	}
	
	fclose(bubble);
	fclose(insert);
	fclose(merg);
	return 0;
}