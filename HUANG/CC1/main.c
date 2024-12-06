#include "graph.c"
#include "dijkstra.c"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

int main()
{
	const char *F = "data/gr1.dta";
	
	struct EdgeList *EL= read_edge_list_from_file(F);
	struct Graph *G = build_graph_from_edge_list(EL);
	return 0;
}

