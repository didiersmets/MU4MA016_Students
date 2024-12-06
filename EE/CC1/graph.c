#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct EdgeList *read_edge_list_from_file(const char *filename)
{
	FILE* fp = fopen(filename, "r");
	struct EdgeList* el = (struct EdgeList*)malloc(sizeof(EdgeList));
	char ligne[100];
	fgets(ligne, 100, fp);
	sscanf(ligne, "%d %d", &el->nverts, &el->nedges);
	el->edges = (Edge*)malloc((el->nedges)*sizeof(int));
	for (int i = 0; i < el->nedges; i ++){
		fgets(ligne, 100,fp);
		sscanf(ligne,"%d %d %f",&el->edges[i].orig,&el->edges[i].dest,&el->edges[i].cost);
	}
	fclose(fp);
	return el;
}
/* Implement me here. Worth 5 points */

struct Graph *build_graph_from_edge_list(const EdgeList *EL)
{
	struct Graph* g= (struct Graph*)malloc(sizeof(Graph));
	g->nverts = EL->nverts;
	g->nedges = EL->nedges;
	g->offsets = (int*)malloc((1 + g->nverts) * sizeof(int));
	g->edges = (HEdge*)malloc(g->nedges * sizeof(HEdge));
	for (int i = 0; i < g->nedges; i ++){
		g->offsets[EL->edges[i].orig] ++;
	}
	int sum = 0;
	for (int i = 0; i <= g->nverts; i++){
		if ((g->offsets[i] == 0)&&(sum == 0)){
			g->offsets[i] = 0;
		}else{
			sum += g->offsets[i];
			g->offsets[i] = sum - 1;
		}
	}
	for (int i = 0; i <= g->nedges; i ++){
		int og = EL->edges[i].orig;
		g->edges[g->offsets[og]].dest = EL->edges[i].dest;
		g->edges[g->offsets[og]].cost = EL->edges[i].cost;
		g->offsets[og] --;
	}
	return g;
}
/* Implement me here. Worth 5 points */
