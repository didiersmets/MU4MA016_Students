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
static void heapify(struct DijkstraHeap *heap, int i)
{
	int min = i;
	int left = 2*i+1;
	int right = 2*i+2;
	if (left<heap->size){
		if(heap->data[left].cost < heap->data[min].cost){
			min = left;
		}
	}
	if (right<heap->size){
		if(heap->data[right].cost < heap->data[min].cost){
			min = rigth;
		}
	}

	if (min!=i){
		struct HEdge temp =heap->data[i];
	       	heap->data[i] = heap->data[min];
		heap->data[min] = temp;	
		heapify(heap,min)
	}
}


static void heap_push(struct DijkstraHeap *heap, struct HEdge edge)
{
	if (heap->size == heap->capacity){
		printf("Heap overflow\n");
		return;
	}
        int i = heap->size;
	heap->data[i]= edge;
	heap->size++;
	
	while(i!=0){
		int parent =(i-1)/2;
		if (heap->data[parent].cost > heap->data[i].cost){
			struct HEdge temp = heap->data[parent];
			heap->data[parent] = heap->data[i];
			heap->data[i] = temp;
			i = parent;
		}else{
			break;
		}
	}
};
static struct HEdge heap_pop(struct DijkstraHeap *heap)
{
	if heap->size <=0{
		return NULL;
	}
	struct HEdge e  =heap->data[0];
	heap->size--;
	heap->data[0] = heap->data[heap->size];
	heapify(heap,0);
	return e;
};
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
	struct DijkstraSol *Dsol;
	Dsol->pred = malloc(G->nverts * sizeof(int));
	Dsol->cost = malloc(G->nverts * sizeof(float));
	for (int i=0;i<G->nverts;i++ ){
		Dsol->pred[i]=-1;
		Dsol->cost[i]=-1;
	}

	struct DijkstraHeap *Dheap;
	
	Dsol->pred[source] = source;
	Dsol->cost[source] = 0;
	struct HEdge H;
	H->dest = source;
	H->cost = 0;
	heap_push(Dheap,H);

	int count = 0;
	while(Dheap->size != 0){
		struct HEdge e1 = heap_pop(Dheap);
		if(e1->dest > Dsol->pred){
			for(int k = G->offsets[count];k<G->offsets[counts+1];k++){
				struct HEdge e2 = G->edges[k];
				if( || ) {
					e2->cost += e1->cost;
					heap_push(Dheap,e2);
				}
			}
			count++;
		}

	}

	return Dsol;	
};
/* Implement me here. Worth 5 points */

/* Follow predecessors back from dest until source and (pretty) print them */
void print_minimal_path(int source, int dest, struct DijkstraSol *sol);
/* Implement me here. Worth 2 points */
