#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

struct Graph {
	int nv;
	int ne;
	int* counts;
	int* offsets;
	int* edges;
	int edge_capacity;
}Graph;


struct Graph* initgraph(int nv_capacity, int ne_capacity){
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->nv = nv_capacity;
	graph->ne = 0;
	graph->edge_capacity = ne_capacity;
	graph->counts = (int*)malloc(nv_capacity * sizeof(int));
	graph->offsets = (int*)malloc(nv_capacity * sizeof(int));
	graph->edges = (int*)malloc(ne_capacity * sizeof(int));
	
	for(int i=0;i<nv_capacity;i++){
		 graph->counts[i] = 0;
		 graph->offsets[i] = 0;
	}

	return graph;
}

void addEdge(struct Graph* graph, int src, int dest){
	if (src >= graph->nv || dest >= graph->nv){
		printf("Error: Vertex out of range. \n");
		return;
	}

	if(graph->ne >= graph->edge_capacity){
		graph->edge_capacity *= 2;
		graph->edges = (int*)realloc(graph->edges, (graph->edge_capacity) * sizeof(int));
	}

	
	graph->edges[graph->ne] = dest;
	graph->ne++;
	graph->counts[src]++;
}

void finalizeGraph(struct Graph* graph) {
    graph->offsets[0] = 0;
    for (int i = 1; i < graph->nv; i++) {
        graph->offsets[i] = graph->offsets[i - 1] + graph->counts[i - 1];
    }
}

void freeGraph(struct Graph* graph) {
	free(graph->counts);
	free(graph->offsets);
	free(graph->edges);
	free(graph);
}

struct Queue{
	int front; // index of the first element in the queue
  	int length; // number of items presently in the queue
  	int capacity; // capacity of the queue (in nbr of items)
  	int* array; // array
};

bool isFull(struct Queue* q){
    	assert (q != NULL);
    	return (q->length==q->capacity);
}

bool isEmpty(struct Queue* q){
    	assert (q != NULL);
	return (q->length == 0);
}

static void enlarge_queue(struct Queue* q){
    	q -> capacity *= 2;
}

struct Queue *init_queue(int capacity){
	struct Queue *q = malloc(sizeof(struct Queue));
  	if (q != NULL){
    		q -> front = 0;
    		q -> length = 0;
    		q -> capacity = capacity;
    		q -> array = (int*)malloc(capacity * sizeof(int));
  	}
  	return (q);
}

void enqueue(struct Queue* q,int* item){
    	if(isFull(q)){
        	enlarge_queue(q);
    	}
    	q->array[(q->front + q->length) % q->capacity] = *item;
    	q->length += 1;
}

int dequeue(struct Queue* q){
    	if(isEmpty(q)){
        	printf("this queue is empty\n");
    	}
    	int dest;
    	memcpy(&dest,&q->array[q->front],sizeof(int));
    	q->front = (q->front + 1 )%q->capacity;
    	q->length -= 1;
    	return dest;
}

void dispose_queue(struct Queue* q){
    	if(q == NULL){
        	return;
    	}
    	free(q -> array);
    	free(q);
}

void BFS(struct Graph* graph, int srs){
	bool* visited = (bool*)malloc(graph->nv * sizeof(bool));

	for (int i = 0; i < graph->nv; i++) {
        	visited[i] = false;
    	}

	struct Queue* q = init_queue(graph->nv);
	visited[srs] = true;
	enqueue(q, &srs);

	printf("BFS Order: \n");
	while(!isEmpty(q)){
		int curr = dequeue(q);
		printf("%d, ", curr);
		for(int k = graph->offsets[curr]; k < graph->offsets[curr] + graph->counts[curr]; k++){
			int explore = graph->edges[k];
			if(!visited[explore]){
				visited[explore] = true;
				enqueue(q, &explore);
			}
		}
	}
	printf("\n");

	free(visited);
	dispose_queue(q);
}


