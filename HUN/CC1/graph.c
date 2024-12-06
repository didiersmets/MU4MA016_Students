#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct EdgeList *read_edge_list_from_file(const char *filename) {
  struct EdgeList *List = malloc(sizeof(struct EdgeList));
  FILE *f = fopen(filename, "r");
  char line[300];

  while (!feof(f)) {
    fgets(line, 300, f);
    if (sscanf(line, "%d %d", &List->nverts, &List->nedges) == 1) {
      List->edges = (struct * Edge) malloc(sizeof(struct Edge) * List->nedges);
      for (int i = 0; i < List->nedges; i++) {
        fgets(line, 300, f);
        sscanf(line, "%d %d %f",
	       List->edges[i].orig,
	       List->edges[i].dest,
               List->edges[i].cost);
      }
    }
    fclose(f);
  }

  return List;
}
/* Implement me here. Worth 5 points */

struct Graph *build_graph_from_edge_list(const EdgeList *EL) {
  struct Gragh* G ;
  int nverts = EL->nverts;
  int nedges = EL->nedges;
  G->nvert  = nverts;
  G->nedges = nedges;
  G->offsets = malloc(sizeof(int) * (nverts + 1));
  G->edges = malloc(sizeof(struct HEdge) * nedges);

  G->offsets[0] = 0;
  int *count = malloc(sizeof(nverts));

  for (int i=0; i<nedges; i++){
    count[EL->edges[i].orig] ++;
  }
  for (int i=1; i<nverts; i++){
    G->offsets[i] = G->offsets[i-1] + count[i];
  }

  for (int i=0; i<nedges + 1; i++){
    /* G->edges[i] =  */
  }
  return G;
}
/* Implement me here. Worth 5 points */
