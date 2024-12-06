#include "dijkstra.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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
	struct HEdge *data;
};

void swap(struct DijkstraHeap *heap, int pos1, int pos2) {
	struct HEdge temp = heap->data[pos1];
	heap->data[pos1] = heap->data[pos2];
	heap->data[pos2] = temp;
}

/* You should implement these two ONLY if you have already implemented
 * Dijkstra_solve. */
static void heap_push(struct DijkstraHeap *heap, struct HEdge edge) {
	if (heap->size >= heap->capacity) {
		heap->capacity *= 2;  // increase capacity if exceeding limit
		heap->data =
		    realloc(heap->data, heap->capacity * sizeof(struct HEdge));
	}
	int pos = heap->size++;
	heap->data[pos] = (struct HEdge){.dest = edge.dest, .cost = edge.cost};
	// Sift up
	int curr_pos = pos;
	int parent_pos = (pos - 1) / 2;
	while ((parent_pos < 0) &&
	       (heap->data[curr_pos].cost) < (heap->data[parent_pos].cost)) {
		swap(heap, curr_pos, parent_pos);
		curr_pos = parent_pos;
		parent_pos = (curr_pos - 1) / 2;
	}
}
static struct HEdge heap_pop(struct DijkstraHeap *heap) {
	if (heap->size == 0)
		return (struct HEdge){.dest = -1, .cost = 0};  // empty heap
	struct HEdge root = heap->data[0];
	heap->data[0] =
	    heap->data[--(heap->size)];	 // replace root by last node
	// Sift it down
	int pos = 0;
	int left_child_pos = 2 * pos + 1;
	int right_child_pos = left_child_pos + 1;
	while (left_child_pos < heap->size) {
		int l_s_r = (heap->data[left_child_pos].cost) <
			    (heap->data[right_child_pos].cost);
		int l_s_i =
		    (heap->data[left_child_pos].cost) < (heap->data[pos].cost);
		int r_s_i =
		    (heap->data[right_child_pos].cost) < (heap->data[pos].cost);
		if (l_s_r && l_s_i) {
			swap(heap, left_child_pos, pos);
			pos = left_child_pos;
		} else if (!l_s_r && r_s_i) {
			swap(heap, right_child_pos, pos);
			pos = right_child_pos;
		} else {
			break;
		}
		left_child_pos = 2 * pos + 1;
		right_child_pos = left_child_pos + 1;
	}
	return root;
}

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
	struct DijkstraSol *S = malloc(sizeof(struct DijkstraSol));
	S->pred = (int *)malloc(G->nverts * sizeof(int *));
	S->cost = (float *)malloc(G->nverts * sizeof(float *));
	for (int c = 0; c < G->nverts; c++) {
		S->pred[c] = -1;
		S->cost[c] = 10e9;
	}
	struct DijkstraHeap *H = malloc(sizeof(struct DijkstraHeap));
	H->size = 0;
	H->capacity = G->nverts;
	H->data = G->edges;
	S->pred[source] = source;
	S->cost[source] = 0;
	struct HEdge source_edge = {source, 0};
	heap_push(H, source_edge);
	while (H->size > 0) {
		struct HEdge e = heap_pop(H);
		if (e.cost < S->cost[e.dest])
			continue;
		else {
			for (int e_idx = G->offsets[e.dest];
			     e_idx <
			     G->offsets[e.dest] + G->offsets[(e.dest) + 1];
			     e_idx++) {
				struct HEdge e_2 = G->edges[e_idx];
				float new_cost = e_2.cost + e.cost;
				if ((new_cost < S->cost[e_2.dest]) ||
				    (S->pred[e_2.dest] == -1)) {
					e_2.cost = new_cost;
					heap_push(H, e_2);
					S->cost[e_2.dest] = e_2.cost;
					S->pred[e_2.dest] = e.dest;
				}
			}
		}
	}
	return S;
}

/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol) {
	int e = dest;
	printf("Minimal Path:");
	printf("%d ", e);
	while (sol->pred[e] != -1) {
		printf("-> %d ", sol->pred[e]);
		e = sol->pred[e];
	}
}

