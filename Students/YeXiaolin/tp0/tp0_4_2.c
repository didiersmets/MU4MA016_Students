#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	if (n <= 0) return EXIT_FAILURE;


    
    double xmax = 6 * M_PI;
    double xmin = -6 * M_PI;
	double delta = (xmax -xmin) / (n - 1);

    FILE *f;
    f = fopen("data.txt", "w");
	

	for (int j = 0; j < n; j++) {
		double x = xmin + j * delta;
		double y =  sin(x) / x;
		
		fprintf(f, "%lf\t%lf\n", x, y);
	}

	fclose(f);
	return EXIT_SUCCESS;
}
