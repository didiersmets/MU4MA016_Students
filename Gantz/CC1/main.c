#include <stdlib.h>

#include "dijkstra.h"
#include "graph.h"

int main(){
	struct EdgeList *EL = read_edge_list_from_file("data/gr1.dta");
	struct Graph *G = build_graph_from_edge_list(EL);
	struct DijkstraSol *sol = Dijkstra_solve(G,0);
	print_minimal_path(0,1,sol);
	free(sol);
	free(G);
	free(EL);
}
