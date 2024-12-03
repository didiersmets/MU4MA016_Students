#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "graph.h"

struct EdgeList* initEdgeList(int nv, int ne){
	struct EdgeList* edgelist = (struct EdgeList*)malloc(sizeof(struct EdgeList));
	edgelist->nverts = nv;
	edgelist->nedges = ne;
	edgelist->edges = (struct Edge*)malloc(ne * sizeof(struct Edge));
	return edgelist;
}

struct Graph* initgraph(int nv_capacity, int ne_capacity){
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->nverts = nv_capacity;
	graph->nedges = ne_capacity;
	graph->counts = (int*)malloc(nv_capacity * sizeof(int));
	graph->offsets = (int*)malloc((nv_capacity+1) * sizeof(int));
	graph->edges = (struct HEdge*)malloc(ne_capacity * sizeof(int));

	for(int i=0;i<nv_capacity;i++){
		 graph->counts[i] = 0;
		 graph->offsets[i] = 0;
	}

	return graph;
}


/* Implement me here. Worth 5 points */
struct EdgeList* read_edge_list_from_file(const char *filename){
	FILE *fp = fopen(filename, "r");

	if (fp == NULL){
		printf("Error: could not open file %s \n", filename);
		return NULL;
	}

	char line[256];

	fgets(line, sizeof(line), fp);
	int nv = 0;
	int ne = 0;
	char *tri = strtok(line, "\n");
        sscanf(tri, "%d %d", &nv, &ne);

	struct EdgeList* edgelst = initEdgeList(nv,ne);
	while (fgets(line, sizeof(line), fp)){
		char *trimmed = strtok(line, "\n");
		sscanf(trimmed, "%d %d %e", &edgelst->edges->orig, &edgelst->edges->dest,&edgelst->edges->cost);
	}
	return edgelst;
}


/* Implement me here. Worth 5 points */
struct Graph *build_graph_from_edge_list(const struct EdgeList* EL){
	struct Graph* graph = initgraph(EL->nverts, EL->nedges);
	
	for(int i = 0; i<EL->nedges; i++){
		struct Edge* edge = &EL->edges[i];
		struct HEdge hedge;
		hedge.dest = edge->dest;
		hedge.cost = edge->cost;
		graph->edges[edge->orig + graph->offsets[edge->orig]] = hedge;
		for(int i = edge->orig + 1; i < graph->nedges; i++){
                	graph->offsets[i]++;
        	}
	}

	return graph;
}






