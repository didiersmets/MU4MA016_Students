#include <stddef.h>
#include <stdlib.h>

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
struct DijkstraSol *Dijkstra_solve(struct Graph *G, int source) {
  int nverts = G->nverts;

  struct DijkstraHeap *H = malloc(sizeof(struct *DijkstraHeap));
  struct DijkstraSol  *Sol = malloc(sizeof(struct * DijkstraSol));
  Sol->pred = (int *)malloc(sizeof(int) * nverts);
  Sol->cost = (int *)malloc(sizeof(int) * nverts);

  Sol->pred[source] = source;
  Sol->cost[source] = 0;

  HEdge e;

  e.dest = source; e.cost = 0;
  heap_push(H, e);

  while (H->size > 0) {
    e = heap_pop(H);

    for (int i = G->offsets[e.dest]; i<G->offsets[e.dest+1]; i++){
      heap_push(H, G->edges[i]);                                     //G->edges[i] is the outgoing halfedge from dest
      if (Sol->cost[source] + e.cost < Sol->cost[?]) {
	Sol->pred[source+1] = e.dest;
	Sol->cost[source+1] = Sol->cost[source] + e.cost;
      }
    }
    source ++; 
  }
  return H;
}
/* Implement me here. Worth 5 points */

/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol) {
}
/* Implement me here. Worth 2 points */
