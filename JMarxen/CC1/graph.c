#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

struct EdgeList *read_edge_list_from_file(const char *filename) {
	FILE *file = fopen(filename, "r");
	int nv;
	int ne;
	fscanf(file, "%d %d", &nv, &ne);
	struct EdgeList *list = malloc(sizeof(struct EdgeList));
	list->nverts = nv;
	list->nedges = ne;
	struct Edge *edges = malloc(ne * sizeof(struct Edge));
	int orig;
	int dest;
	float cost;
	for (int i = 0; i < ne; i++) {
		fscanf(file, "%d %d %f", &orig, &dest, &cost);
		edges[i].orig = orig;
		edges[i].dest = dest;
		edges[i].cost = cost;
	}
	list->edges = edges;
	return list;
}

struct Graph *build_graph_from_edge_list(const struct EdgeList *EL) {
	int nv = EL->nverts;
	int ne = EL->nedges;
	struct Graph *g = malloc(sizeof(struct Graph));
	g->nverts = nv;
	g->nedges = ne;
	int *counts = (int *)calloc(nv, sizeof(int));
	int v1;
	int v2;
	float cost;
	for (int e = 0; e < ne; e++) {
		v1 = EL->edges[e].orig;
		v2 = EL->edges[e].dest;
		counts[v1]++;
	}
	g->offsets = (int *)malloc(nv + 1 * sizeof(int));
	g->offsets[0] = 0;
	for (int i = 1; i < nv + 1; i++)
		g->offsets[i] = g->offsets[i - 1] + counts[i - 1];
	struct HEdge *hedges = malloc(ne * sizeof(struct HEdge));
	int index;
	for (int e = 0; e < ne; e++) {
		v1 = EL->edges[e].orig;
		v2 = EL->edges[e].dest;
		cost = EL->edges[e].cost;
		index = g->offsets[v1] + g->offsets[v1 + 1];
		hedges[index].dest = v2;
		hedges[index].cost = cost;
	}
	g->edges = hedges;
	return g;
}

