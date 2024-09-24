#include <stdio.h>
#include <stdlib.h>

int compute_A(int i,int j){
	if(j>0 && j<i){
		return compute_A(i-1,j-1)+compute_A(i-1,j);
	}
	else{
		return 1;
	}
}

int main(int argc, char **argv){
	for (int i = 0; i<atoi(argv[1]); i++)
	{
		for (int j = 0; j<atoi(argv[1]); j++)
		{
			if(j<=i){
				int curr_A = compute_A(i,j);
				printf("%i ", curr_A ); 
			}
		}
		printf("\n");
	}
	return 0;
}
