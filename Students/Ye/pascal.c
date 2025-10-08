
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
void update_line(int *L,int i);
void print_line(int *L, int i);

void update_line(int *L, int i){
	for(int j = i-1;j>0;j--){
		L[j] = L[j] + L[j-1];
	}
}

void print_line(int* L, int i){
	for(int j = i-1;j>0;j--){
		printf("%5d",L[j]);
	}
	printf("\n");
}

void pascal(int n){
	if(n<=0)return;
	int*L = malloc(n*sizeof(int));
	assert(L);
	for (int j=0;j<n;j++) L[j] =1;
	for(int i = 0; i<n;i++){
		update_line(L,i);
		print_line(L,i);
	}
	free(L);
}
int main(int argc, char**argv){
	if(argc < 2){
		printf("Syntaxx : .pascal n\n");
		return EXIT_FAILURE;
	}
	int n = atoi(argv[1]);
	if (n<0){
		printf("n must be a positive number.\n");
		return EXIT_FAILURE;
	}
	pascal(n);
	return EXIT_SUCCESS;

}
