#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char const *argv[])
{
	FILE *text = fopen(argv[1],"w");
	int n = atol(argv[2]);

	double x_max = 6*M_PI;
	double x_min = -x_max;
	double D = (x_max - x_min)/(n-1);
	printf("%f\n", D);
	printf("%f\n", sin(x_min));


	int j = 0;
	for (j=0; j<n; j++){

		double x = x_min + j*D;
		double y = sin(x)/x;
		fprintf(text, "%f   %f \n",x,y);
	}

	fclose(text);

	return 0;
}