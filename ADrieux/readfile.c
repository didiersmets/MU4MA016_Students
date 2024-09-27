#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

	FILE *fichier = fopen(argv[1], "r");
	int caractereActuel = 0;
	if (fichier != NULL) {
		while (caractereActuel != EOF) {
			caractereActuel = fgetc(fichier);
			printf("%c", caractereActuel);
		}
		fclose(fichier);
	}
	return 0;
}

