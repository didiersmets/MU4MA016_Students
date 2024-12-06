#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct EdgeList *read_edge_list_from_file(const char *filename)
{
	FILE* f = fopen(filename,"r");
	if (f==NULL){
		printf("file do not exist");
		return NULL;
	}
	struct EdgeList *EL;	

	char line[512];
	while (!feof(f)){
		fgets(line,512,f);
		if (sscanf(line,"%d %d",&EL->nverts,&EL->nedges)==2){
			EL->edges = malloc(EL->nedges * sizeof(struct Edge));
			for(int i=0; i<(EL->nedges);i++){
				fgets(line,512,f);
				int* orig = &EL->edges[i].orig;
				int* dest = &EL->edges[i].dest;
				float* cost = &EL->edges[i].cost;
				sscanf(line,"%d %d %f",orig,dest,cost);
			}
		}

	}

	fclose(f);
	return EL;
};
/* Implement me here. Worth 5 points */

struct Graph *build_graph_from_edge_list(const EdgeList *EL)
{
	if(EL == NULL){
		printf("Data do not exist");
		return NULL;
	}
	struct Graph *G;
	G->nverts = EL->nverts;
	G->nedges = EL->nedges;
	G->offsets = malloc((G->nverts +1)*sizeof(int));
	G->offsets[0]=0;
	G->edges = malloc((G->nedges)*sizeof(struct HEdge));

	for(int i=0;i<G->nedges;i++){
		int edgecount = 0;
		int* orig = &EL->edges[i].orig;
		int* dest = &EL->edges[i].dest;
		float* cost = &EL->edges[i].cost;
		G->offsets[orig+1]=i+1;
		G->edges[i].dest = dest;
		G->edges[i].cost = cost;
	}	
	
	return G;
};
/* Implement me here. Worth 5 points */
