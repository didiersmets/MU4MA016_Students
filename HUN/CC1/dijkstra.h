#pragma once

/* For any 0 <= dest < nverts :
 * - pred[dest] should eventually contain the predecessor of vertex
 *   dest along a shortest path from source to dest.
 * - cost[dest] will eventually contain the total cost of a shortest path from
 *   source to dest.
 * It is useful to initialize predecessors to -1 to indicate 'no predecessor
 * candidate yet'.
 */
struct DijkstraSol {
	int *pred; /* size = nverts */
	int *cost; /* size = nverts *
};

struct DijkstraSol *Dijkstra_solve(const struct Graph *G, int source);
void print_minimal_path(int source, int dest, struct DijkstraSol *sol);
