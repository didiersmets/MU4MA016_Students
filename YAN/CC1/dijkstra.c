#include <stddef.h>

#include "dijkstra.h"
#include "graph.h"

/* A heap containing half edges. The .cost field
 * will contain the accumulated cost from source up to dest,
 * not just the cost of that particular edge.
 * The comparison function for the heap property should
 * be the comparison between the costs, with the min on top.
 */
struct DijkstraHeap {
	size_t size;
	size_t capacity;
	HEdge *data;
};

/* You should implement these two ONLY if you have already implemented
 * Dijkstra_solve. */
static void heap_push(struct DijkstraHeap *heap, struct HEdge edge);
static struct HEdge heap_pop(struct DijkstraHeap *heap);
/* Implement them here. Worth 5 points in total */

/* 1) Initialize a DikstraSol and and DijkstraHeap.
 * 2) Set pred[source] = source, cost[source] = 0, and push the half edge
 *    {source, 0} into the heap.
 * 3) While the heap is non empty:
 *     - Pop a half edge e = {dest, cost} from the heap
 *     - If dest already have a better or equal solution in the DijkstraSol:
 *         do nothing and continue
 *       Else:
 *         for each half edge e' outgoing from dest in G, push the
 *         half edge {e'.dest, e'.cost + e.cost} into the heap, ONLY IF
 *         that strictly improves over an existing path towards e'.dest or if
 *         there are no path to e'.dest yet.
 *    Each time some half edge is pushed into heap, DijkstraSol should be
 *    updated accordingly.
 */
struct DijkstraSol *Dijkstra_solve(struct Graph *G, int source){
	struct DijkstraSol* dij = malloc(sizeof(struct DijkstraSol));
	dij->pred = malloc(G->nverts*sizeof(int));
	dij->cost = malloc(G->nverts*sizeof(int));
	for(int i = 0, i< G->nverts, i++){
		dij->pred[i]=-1;
	}
	struct DijkstraHeap* heap = mallox(sizeof(struct DijkstrHeap));
	heap->size = G->nverts;
	heap->capacity = G->nverts;
	heap->data = malloc(g->nverts*sizeof(struct HEdge));
	dij->pred[source]=source;
	dij->cost[source]=0;
	struct HEdge next;
	struct HEdge he;
	he.dest = source;
	he.cost = 0;
	heap_push(heap,he);
	while (heap->capacity != G->nverts){
		he = heap_pop(heap);
		if(dij->cost[he.dest]>he.cost){
			for(int i= G->offsets[dest], i<G->offssts[dest+1], i++){
				next->dest= G->edges[i].dest;
				next->cost = he.cost+G->edges[i].cost;
				if(dij->pred[next->dest]=-1 || dij->cost[next->dest]>next->cost){
					heap_push(heap, next);
					dij->pred[he.dest]=next->dest;
					dij->pred[he.cost]=next->cost;
				}
			}
		}
	}
	return dij;
}

	
/* Implement me here. Worth 5 points */

/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol);
/* Implement me here. Worth 2 points */
