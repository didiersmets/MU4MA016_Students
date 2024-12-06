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
	graph->edge_capacity = ne_capacity * nv_capacity;
	graph->counts = (int*)malloc(nv_capacity * sizeof(int));
	graph->offsets = (int*)malloc(nv_capacity * sizeof(int));
	graph->edges = (int*)malloc(ne_capacity * nv_capacity * sizeof(int));
	
	for(int i=0;i<nv_capacity;i++){
		 graph->counts[i] = 0;
		 graph->offsets[i] = 0;
	}

	return graph;
}

void insertG(int** arr, int* size, int value, int position) {

    for (int i = *size; i > position; i--) {
        (*arr)[i] = (*arr)[i - 1];
    }

    (*arr)[position] = value;
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

	insertG(&(graph->edges), &(graph->edge_capacity), dest, graph->offsets[src]+graph->counts[src]);
	graph->ne++;
	graph->counts[src]++;
	for(int i = src + 1; i < graph->nv; i++){
		graph->offsets[i]++;
	}
	insertG(&(graph->edges), &(graph->edge_capacity), src, graph->offsets[dest]+graph->counts[dest]);
        graph->counts[dest]++;
        for(int i = dest + 1; i < graph->nv; i++){
                graph->offsets[i]++;
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

static void enlarge_queue(struct Queue* q) {
    int new_capacity = q->capacity * 2;
    int* new_array = (int*)malloc(new_capacity * sizeof(int));
    assert(new_array != NULL); // Ensure memory allocation succeeded

    // Copy elements to new array
    for (int i = 0; i < q->length; i++) {
        new_array[i] = q->array[(q->front + i) % q->capacity];
    }

    free(q->array);
    q->array = new_array;
    q->capacity = new_capacity;
    q->front = 0;
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

struct Stack{
        int top; // index of the first element in the stack
        int length; // number of items presently in the stack
        int capacity; // capacity of the stack (in nbr of items)
        int* array; // array
};

struct Stack *init_stack(int capacity){
        struct Stack *s = malloc(sizeof(struct Stack));
        if (s != NULL){
                s -> top = -1;
                s -> length = 0;
                s -> capacity = capacity;
                s -> array = (int*)malloc(capacity * sizeof(int));
        }
        return (s);
}

bool isFullStack(struct Stack* stack){
    	return stack->top == stack->capacity - 1;
}

bool isEmptyStack(struct Stack* stack){
    	return stack->top == -1;
}

void enlarge_stack(struct Stack* stack) {
    	int new_capacity = stack->capacity * 2;  
    	int* new_array = (int*)malloc(new_capacity * sizeof(int));
    	if (new_array != NULL) {
        	for (int i = 0; i <= stack->top; i++) {
            	new_array[i] = stack->array[i];
        	}
        free(stack->array);
        stack->array = new_array;
        stack->capacity = new_capacity;
    	}
}

void dispose_stack(struct Stack* stack){
	if(stack != NULL){
		free(stack->array);
		free(stack);
	}
}

void push(struct Stack* stack, int item){
    	if (isFullStack(stack))
        	return;
    	stack->array[++stack->top] = item;
}

int pop(struct Stack* stack){
    	if (isEmptyStack(stack))
        	return -10;
    	return stack->array[stack->top--];
}

void DFS_Rec(struct Graph* graph, bool visited[], int srs){
	visited[srs] = true;
	printf("%d, ", srs);
	
	if(graph->counts[srs] != 0){
		for(int k = graph->offsets[srs]; k < graph->offsets[srs] + graph->counts[srs]; k++){
			int explore = graph->edges[k];
			if (!visited[explore]){
				DFS_Rec(graph, visited, explore);
			}
		}
	}else{
		return;
	}
}

void DFS(struct Graph* graph, int srs){
	bool* visited = (bool*)malloc(graph->nv * sizeof(bool));
	
	for(int i = 0; i < graph->nv; i++) {
		visited[i] = false;
	}

	DFS_Rec(graph, visited, srs);
		
        printf("\n");

        free(visited);
}

