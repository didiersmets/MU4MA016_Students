#include <stdio.h>
#include <stdlib.h>

// From correction

int main(int argc, char **argv) {
	if (argc < 2) { // so that we get an error if we just run the executable "./read_file"
		printf("Syntax : ./read_file filename\n");
		return EXIT_FAILURE;
	}

	FILE *f = fopen(argv[1], "r"); // to open the file put as the first argument "./read_file ../test-tp0.txt"
	if (!f) return EXIT_FAILURE;

#define CHUNK 256
	char line[CHUNK];
	/* Note : lines in the file can be longer than CHUNK, they will
	 * simply be loaded and printed in parts, the new_line character
	 * only appearing once.
	 * Could you modify it so that long lines are wrapped at e.g. 80 chars ?
	 */
	while (fgets(line, CHUNK, f)) {
		printf("%s", line);
	}
	int success = feof(f);
	fclose(f);
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

// Compile with e.g. : gcc tp0_ex4_1.c -o read_file
 