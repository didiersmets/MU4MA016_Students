#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>


// question 4 Reading and writing into a file using C (2) 读写文件 (github)
int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	if (n <= 0) return EXIT_FAILURE;

	FILE *f = fopen("data.txt", "w");
	if (!f) return EXIT_FAILURE;

	double delta = 12 * M_PI / (n - 1);
	double xmin = -6 * M_PI;

	for (int j = 0; j < n; j++) {
		double x = xmin + j * delta;
		double y = x == 0 ? 1 : sin(x) / x;
		/* We could/should check that fprintf returns 2 */
		fprintf(f, "%lf\t%lf\n", x, y);
	}

	fclose(f);
	return EXIT_FAILURE;
}

// Compile e.g. with : gcc tp0_ex4_2.c -o fill_gnuplot_data -lm
// The -lm indicates to link the executable to the libm.so math shared library,
// necessary to access the sin function.