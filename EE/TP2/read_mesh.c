#include "Tri_mesh2D.h"
#include <stdlib.h>
#include <stdio.h>

int read_mesh2D(struct Mesh2D *m, const char *file)
{
	FILE *fptr = open(file, "r");
	if (fp = NULL){
		printf("impossible de lire le fichier\n");
		return -1;
	}
	int vtx_capacity = 0;
	int tri_capacity = 0;
	char ligne[100];
	while(!feof(fp)){
		fgets(ligne, 100, fp);
	initialise_mesh2D(m, vtx_capacity, tri_capacity);
