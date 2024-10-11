#include <stdio.h>

void bubble(int *B, int size_A)
{
	int temp = 0;
	for (int j = 0; j<size_A; j++){
		int i = 0;
		while (i < size_A-j){
			if (B[i] > B[i+1]){
				temp = B[i];
				B[i] = B[i+1];
				B[i+1] = temp;
			}else{
				i++;
			}
		}
	}
}

