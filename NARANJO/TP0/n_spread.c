#include <stdio.h>
#include <math.h>

void printnspread(int n) {
	FILE *ptr;
	ptr=fopen("resutls1.txt", "w+");

	float x_min = -6*M_PI;
	float x_max = 6*M_PI;
	float delta_x = (x_max - x_min)/(n-1);
	for (int j = 0; j < n; j++) {
		float x_j = x_min + j*delta_x;
		float y_j = sin(x_j)/x_j;
		fprintf(ptr, "%f  %f \n", x_j, y_j);
	}
	fclose(ptr);
}


int main(){
	int n;

	printf("Enter a number n: ");
	scanf("%d", &n);

	printnspread(n);

	return 0;	
}