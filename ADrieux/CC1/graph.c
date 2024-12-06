#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define TAILLE_MAX 100
struct EdgeList *read_edge_list_from_file(const char *filename)
{
	FILE *fichier = fopen("filename", "r");
	char line[TAILLE_MAX];
	struct EdgeList *EL = (struct EdgeList *)malloc(sizeof(struct EdgeList));
	EL->nverts = 0;
	EL->nedges = 0;
	if (fichier != NULL)
	{
		while(fgets(line, TAILLE_MAX, fichier) != NULL)
		{
			if (sscanf(line, "%d %d", &EL->nverts, &EL->nedges) == 2)
			{
				EL->edges = (struct Edge *)malloc(EL->nedges*sizeof(struct Edge));
				for (int i = 0; i<EL->nedges; i++)
				{
					fgets(line, TAILLE_MAX, fichier);
					sscanf(line, "%d %d %f", &EL->edges[i].orig, &EL->edges[i].dest, &EL->edges[i].cost);
				}
			}
		}
	}
	fclose(fichier);
	return(EL);
}

struct Graph *build_graph_from_edge_list(const EdgeList *EL)
{
	struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
	g->nverts = EL->nverts;
	g->nedges = EL->nedges;
	g->offsets = (int *)malloc((g->nverts + 1)*sizeof(int));
	g->edges = (struct HEdge *)malloc(g->nedges*sizeof(struct HEdge));
	g->offsets[0] = 0;
	for (int i = 1; i<g->nverts + 1; i++)
	{
		for (int j = 0; j<g->nedges; j++)
		{
			if (EL->edges[j].orig == i-1)
			{
				g->offsets[i] = 1 + g->offsets[i];
			}
		}
	}
	for (int j = 0; j<g->nedges; j++)
	{
		g->edges[j].dest = EL->edges[j].dest;
		g->edges[j].cost = EL->edges[j].cost;
	}
	return g;
}


