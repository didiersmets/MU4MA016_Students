#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv){
	const float x_min = -6*M_PI; 
	const float x_max = 6*M_PI;
	int n = atoi(argv[1]);
	const float d_x = (x_max/x_min)/(n-1);
	float* x = (float*) malloc(n * sizeof(float));
	float* y = (float*) malloc(n * sizeof(float));
	for(int i=0; i<n; i++){
		float xi = x_min+i*d_x;
		float yi = sin(xi)/xi;
		printf("%f	%f \n", xi, yi);
	}
	return 0;
}
