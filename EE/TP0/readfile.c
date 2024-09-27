#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 100

int main(int argc, char **argv)
{
	FILE* fp;
	fp= fopen(argv[1], "r");
	if (fp == NULL){
		printf("impossible d'ouvrir le fichier\n");
	}
	else{
		char ligne[TAILLE_MAX]="";
		while(!feof(fp)){
			fgets(ligne, 100, fp);
			printf ("%s", ligne);
		}
	}
	return 0;
}

