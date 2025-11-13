#include <stdio.h>
#include <stdlib.h>
#include <hashtable.h>

struct Edge {
    int v1;
    int v2;
};

struct HashTable * build_edge_table1 (const struct Mesh *m);