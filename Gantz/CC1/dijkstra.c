#include <stddef.h>
#include <stdio.h>
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
	struct HEdge *data;
};



struct DijkstraHeap* create_heap(int initial_capacity) {
    // Allocate memory for the heap structure
    struct DijkstraHeap* heap = (struct DijkstraHeap*) malloc(sizeof(struct DijkstraHeap));
    // Allocate memory for the dynamic array
    heap->data = (struct HEdge*)malloc(initial_capacity * sizeof(struct HEdge));
	heap->size = 0;
    heap->capacity = initial_capacity;
    return heap;
}

void free_heap(struct DijkstraHeap* heap) {
    // Free the dynamic array and heap structure
    free(heap->data);
    free(heap);
}

static int parent(int index) {
    return (index - 1) / 2;
}

static int left_child(int index) {
    return 2 * index + 1;
}

static int right_child(int index) {
    return 2 * index + 2;
}

static void swap(struct HEdge* a, struct HEdge* b) {
    struct HEdge temp = *a;
    *a = *b;
    *b = temp;
}

static void resize_heap(struct DijkstraHeap* heap) {
	// Double the capacity of the heap
	int new_capacity = heap->capacity * 2;
	struct HEdge* new_data = (struct HEdge*)realloc(heap->data, new_capacity * sizeof(struct HEdge));
	heap->data = new_data;
	heap->capacity = new_capacity;
}

static void sift_up(struct DijkstraHeap* heap, int index) {
    while (index > 0 && heap->data[parent(index)].cost > heap->data[index].cost) {
        swap(&heap->data[parent(index)], &heap->data[index]);
        index = parent(index);
    }
}

static void heap_push(struct DijkstraHeap *heap, struct HEdge edge) {
    // Resize if the heap is full
    if (heap->size == heap->capacity) {
        resize_heap(heap);
    }

    // Add the new node at the end of the heap
    heap->data[heap->size] = edge;
    heap->size++;

    // Restore heap property by sifting up
    sift_up(heap, heap->size - 1);
}

static void sift_down(struct DijkstraHeap* heap, int index) {
    int smallest = index;
    int left = left_child(index);
    int right = right_child(index);

    if (left < heap->size && heap->data[left].cost < heap->data[smallest].cost) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right].cost < heap->data[smallest].cost) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        sift_down(heap, smallest);
    }
}

struct HEdge heap_pop(struct DijkstraHeap* heap) {
    if (heap->size == 0) {
        fprintf(stderr, "Heap is empty\n");
        exit(EXIT_FAILURE);
    }

    // Store the minimum node
    struct HEdge min_node = heap->data[0];

    // Replace the root with the last element
    heap->data[0] = heap->data[--heap->size];

    // Restore heap property by sifting down
    sift_down(heap, 0);

    return min_node;
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
struct DijkstraSol *Dijkstra_solve(const struct Graph *G, int source){
		struct DijkstraSol *sol = (struct DijkstraSol*) malloc(sizeof(struct DijkstraSol));
		sol->pred = (int*) malloc(G->nverts * sizeof(int));
		sol->cost = (int*) malloc(G->nverts * sizeof(int));
		
		// Error probably here: maybe add attribute discovered ?
		for(int i=0; i<G->nverts; i++){
			sol->pred[i] = -1;
			sol->cost[i] = 10e4;
		}

		struct DijkstraHeap *heap = create_heap(10); //randomly choosen

		sol->pred[source] = source;
		sol->cost[source] = 0;
		
		struct HEdge* initial = (struct HEdge*) malloc(sizeof(struct HEdge));
		initial->dest = source;
		initial->cost = 0;
		
		while(heap->size > 0){
			struct HEdge e = heap_pop(heap);
			if(sol->cost[e.dest] <= e.cost){
				continue;
			} else {
				for(int eprime_idx=G->offsets[e.dest]; eprime_idx<G->offsets[e.dest+1]; eprime_idx++){

					struct HEdge eprime;
					eprime.dest = G->edges[eprime_idx].dest;
					eprime.cost = G->edges[eprime_idx].cost + e.cost;

					if(eprime.cost < sol->cost[eprime.dest] ||  sol->pred[eprime.dest]  == -1){
						heap_push(heap, eprime);
						sol->cost[eprime.dest] = eprime.cost;
						sol->pred[eprime.dest] = e.dest;
					}
				}
			}
		}
		free_heap(heap);
		return sol;
}

/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol){
	printf("Shortest path from vertex %d to vertex %d in reverse order ", source, dest);
	int v = dest;
	printf("%d <- ", dest);
	while(sol->pred[v]!=source){
		v = sol->pred[v];
		printf("%d <- ", v);
	}
	printf("%d\n", source);
}
