#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>


#include "GraphPoly.c"


int main() {
    struct Graph* graph = initgraph(15, 15);

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 3);
    addEdge(graph, 3, 10);
    addEdge(graph, 3, 9);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 7);
    addEdge(graph, 2, 8);
    addEdge(graph, 2, 5);
    addEdge(graph, 8, 7);
    addEdge(graph, 5, 7);
    addEdge(graph, 5, 6);
    addEdge(graph, 5, 8);

    printf("Testing BFS starting from vertex 0:\n");
    BFS(graph, 0);

    printf("Testing BFS starting from vertex 8:\n");
    BFS(graph, 8);

    freeGraph(graph);

    return 0;
}


