#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct EdgeList *read_edge_list_from_file(const char *filename){
	struct EdgeList *el = (struct EdgeList*) malloc(sizeof(struct EdgeList)); 
	FILE *f = fopen(filename, "r");
	int LINE =100;
	char line[LINE];
	fgets(line, LINE, f);
	sscanf(line, "%d" "%d", &el->nverts, &el->nedges);
	el->edges = (struct Edge*) malloc(el->nedges * sizeof(struct Edge));
	for (int i = 0; i < el->nedges; ++i) {
		fgets(line, LINE, f);
		sscanf(line, "%d %d %f", &el->edges[i].orig, &el->edges[i].dest, &el->edges[i].cost);
	}
	fclose(f);
	return el;
}

struct Graph *build_graph_from_edge_list(const struct EdgeList *EL){
	struct Graph* g = (struct Graph*) malloc(sizeof(struct Graph));
	g->nverts = EL->nverts;
	g->nedges = EL->nedges;
	g->edges = (struct HEdge*) malloc(g->nedges * sizeof(struct HEdge));
	g->offsets = (int*) malloc((g->nverts+1) * sizeof(int));
	g->offsets[0] = 0;
	int counter = 0;
	for(int vertex=0; vertex<g->nverts; vertex++){
		for(int edge=0; edge<g->nedges; edge++){
			if(EL->edges[edge].orig == vertex){
				g->edges[counter].dest = EL->edges[edge].dest;
				g->edges[counter].cost = EL->edges[edge].cost;
				counter += 1;
			}
		}
		g->offsets[vertex+1] = counter;
	}
	return g;
}
