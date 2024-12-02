#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure to represent a graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;  // Array of adjacency lists
} Graph;

// Queue implementation for BFS
typedef struct Queue {
    int* items;
    int front;
    int rear;
    int capacity;
} Queue;

// Function to create a node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Create an array of adjacency lists
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Add edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src (since the graph is undirected)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Initialize the queue
Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->items = (int*)malloc(capacity * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
    return q;
}

// Check if the queue is empty
bool isEmpty(Queue* q) {
    return q->front == -1;
}

// Enqueue an element
void enqueue(Queue* q, int value) {
    if (q->rear == q->capacity - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

// Dequeue an element
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return value;
}

// BFS function
void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));

    // Initialize visited array to false
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    // Create a queue for BFS
    Queue* queue = createQueue(graph->numVertices);

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = true;
    enqueue(queue, startVertex);

    printf("BFS Order: ");
    while (!isEmpty(queue)) {
        // Dequeue a vertex and process it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Traverse all adjacent vertices
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");

    // Free allocated memory
    free(visited);
    free(queue->items);
    free(queue);
}

// Main function to test BFS
int main() {
    int vertices = 4;
    Graph* graph = createGraph(vertices);

    // Adding edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);

    int startVertex = 0;
    BFS(graph, startVertex);

    // Free allocated memory for graph
    for (int i = 0; i < vertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph);

    return 0;
}



