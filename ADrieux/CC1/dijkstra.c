#include <stddef.h>

#include "dijkstra.h"
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

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
struct DijkstraSol *Dijkstra_solve(struct Graph *G, int source)
{
	struct DijkstraSol *DjS = (struct DijkstraSol *)malloc(sizeof(struct DijkstraSol));
	struct DijkstraHeap *heap = (struct DijkstraHeap *)malloc(10*sizeof(struct DijkstraHeap));
	heap->size = 0;
	heap->capacity = 10;
	Djs->pred = (int *)malloc(G->nverts*sizeof(int));
	for (int i = 0; i<G->nverts; i ++)
	{
		Djs->pred[i] = -1;
	}
	Djs->cost = (int *)malloc(G->nverts*sizeof(int));
	Djs->cost[source] = 0;
	Djs->pred[source] = NULL;


/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol);
/* Implement me here. Worth 2 points */
