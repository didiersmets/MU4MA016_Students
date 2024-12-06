#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct EdgeList *read_edge_list_from_file(const char *filename){
	FILE* f = fopen(filename, 'r');
	char line[400];
	struct EdgeList* EL = malloc(sizeof(struct EdgeList));
	int nv = 0;
	int nt = 0;
	while (!feof(f)){
		fgets(line,400,f);
		if( sscanf(line, "%d %d",&nv, &ne)==1){
			EL->nverts = nv;
			EL->nedges = ne;
			EL->edges = malloc(ne*sizeof(struct Edge));
			for(int i=0,i<nv, i++){
				fgets(line,400,f);
				sscanf(line, "%d %d %f", &EL->edges[i].orig,&EL->edges[i].dest,ÉL->deges[i].cost);
			}
		}
	}
	fclose(f);
	return EL;
}


/* Implement me here. Worth 5 points */

struct Graph *build_graph_from_edge_list(const struct EdgeList *EL){
	struct Graph* G = malloc(sizeof(struct Graph));
	G->nverts = EL->nverts;
	G->nedges = EL->nedges;
	G->offsets = malloc((EL->nverts+1)*sizeof(int));
	g->edges = calloc(EL->nedges*sizeof(struct HEdge));
	int* count = malloc((EL->nverts+1)*sizeof(int));
	for(int i = 0, i<El->nedges, i++){
		G->offsets[EL->edges[i].orig+1]+=1;
	}
	for(int i = 1, i<=G->nverts, i++){
		G->offsets[EL->edges[i].orig]+=G->offsets[EL->edges[i-1].orig];
	}
	count = memcpy(count, G->offsets, (EL->nverts+1)*sizeof(int));
	for(int k = 0, k<EL->nedges, k++){
		G->edges[count[El->edges[k].orig]].dest = EL->edges[k].dest;
		G->edges[count[El->edges[k].orig]].cost = EL->edges[k].cost;
		count[El->edges[k].orig]+=1;
	}
	return G;
}
	


		
	

		
	

/* Implement me here. Worth 5 points */
