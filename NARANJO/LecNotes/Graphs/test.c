#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "GraphPoly.c"


int main() {
    struct Graph* graph = createTestGraph();

    printf("Testing BFS starting from vertex 0:\n");
    BFS(graph, 0);

    printf("Testing BFS starting from vertex 2:\n");
    BFS(graph, 2);

    // Free graph memory
    free(graph->counts);
    free(graph->offsets);
    free(graph->edges);
    free(graph);

    return 0;
}


