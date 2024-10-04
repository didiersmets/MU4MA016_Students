#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	FILE *file_pointer;
	const float x_min = -6*M_PI; 
	const float x_max = 6*M_PI;
	int n = atoi(argv[1]);
	const float d_x = (x_max/x_min)/(n-1);
	file_pointer = fopen("output.txt", "w");
	for(int i=0; i<n; i++){
		float xi = x_min+i*d_x;
		float yi = sin(xi)/xi;
		printf("%f	%f \n", xi, yi);
		fprintf(file_pointer, "%f      %f \n", xi, yi);
	}
	fclose(file_pointer);
	return 0;
}


