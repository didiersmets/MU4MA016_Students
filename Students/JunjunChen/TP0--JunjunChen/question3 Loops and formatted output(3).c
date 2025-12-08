#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


// question 3 Loops and formatted output（github）
void update_line(int *L, int i) {
	/* Note : L[0] and L[i] are already holding the correct value 1 */
	for (int j = i - 1; j > 0; j--) {
		L[j] = L[j] + L[j - 1];
	}
}

void print_line(int *L, int i) {
	for (int j = 0; j <= i; j++) {
		printf("%5d ", L[j]);
	}
	printf("\n");
}

void pascal(int n) {
	if (n <= 0) return;

	/* Reserve memory for an array L of n integers. It will contain
	 * succesively each line of the matrix A, overwriting the previous
	 * one with the new one.
	 */
	int *L = malloc(n * sizeof(int));
	assert(L);

	/* We pre-fill L with ones (only an optimization) */
	for (int j = 0; j < n; j++) L[j] = 1;

	for (int i = 0; i < n; i++) {
		update_line(L, i);
		print_line(L, i);
	}

	free(L);
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Syntax : ./pascal n\n");
		return EXIT_FAILURE;
	}

	int n = atoi(argv[1]);
	if (n < 0 || n > 20) {
		printf("Inappropriate value of n (wouldn't fit on screen)\n");
		return EXIT_FAILURE;
	}

	pascal(n);
	return EXIT_SUCCESS;
}

// Compile with e.g. : gcc tp0_ex3.c -o pascal