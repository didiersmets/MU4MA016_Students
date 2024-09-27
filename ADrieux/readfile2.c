#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 100

int main(int argc, char** argv) {
	FILE *fichier = fopen(argv[1], "r");
	char chaine[TAILLE_MAX] = "";
	if (fichier != NULL) {
		while(fgets(chaine, TAILLE_MAX, fichier) != NULL) {
			printf("%s", chaine);
		}
		fclose(fichier);
	}
	return 0;
}

