#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>

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
	struct HEdge* data;
};

DijkstraHeap* createHeap(int capacity)
{
    struct DijkstraHeap* heap = (struct DijkstraHeap*)malloc(sizeof(DijkstraHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (struct HEdge**)malloc(capacity * sizeof(HEdge*));
    return heap;
}



/* You should implement these two ONLY if you have already implemented
 * Dijkstra_solve. */
static void heap_push(struct DijkstraHeap *heap, struct HEdge edge);


static struct HEdge heap_pop(struct DijkstraHeap *heap)


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


struct DijkstraSol *Dijkstra_solve(struct Graph *G, int source);
/* Implement me here. Worth 5 points */
{
	struct DijkstraHeap* heap = createHeap(graph->nedges);
	struct DijkstraSol* dj = (DijkstraSol*)malloc(sizeof(DijkstraSol));
    	dj->pred = (int*)malloc(graph->nverts * sizeof(int));
   	dj->cost = (int*)malloc(graph->nverts * sizeof(int));
	
	for(int i = 0; i<graph->nverts; i++){
		dj->pred[i] = -1;
	}

	dj-pred[source] = source;
	dj-cost[source] = 0;
	struct HEdge edge;
	edge->cost = 0;
	edge->dest = source;
	
	heap_push(heap, edge);
	while(!IsEmpty(heap)){
		e = heap_pop(heap);
	// NOT DONE... SAD FACE :(
	}
    	
}
/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol);
/* Implement me here. Worth 2 points */
