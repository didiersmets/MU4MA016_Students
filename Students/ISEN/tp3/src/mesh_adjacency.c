#include "mesh_adjacency.h"
#include <stdlib.h>  //malloc, ...
#include <stdio.h>


int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    if(t.v1 ==  v1 && t.v2 == v2){
        return 0;
    }else if(t.v2 == v1 && t.v3 == v2){
        return 1;
    }else if(t.v3 == v1 && t.v1 == v2){
        return 2;
    }else{
        return -1;
    }
}


int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    //tri1 and tri2 are indices...
    //for clarity, we define
    struct Triangle t1 = m->triangles[tri1];
	struct Triangle t2 = m->triangles[tri2];

    //check if edge from second vertex of triangle 1 to first vertex
    //of triangle 1 is in triangle 2 (so opposite orientation)
    if (edge_pos_in_tri(t1.v2, t1.v1, t2) != -1){
        //if yes, return position of common edge in triangle 1
        return(edge_pos_in_tri(t1.v1, t1.v2, t1));
    }
    //do this for all edges in v1 in opposite orientation
    if (edge_pos_in_tri(t1.v3, t1.v2, t2) != -1){
        return(edge_pos_in_tri(t1.v2, t1.v3, t1));
    }
    if (edge_pos_in_tri(t1.v1, t1.v3, t2) != -1){
        return(edge_pos_in_tri(t1.v3, t1.v1, t1));
    }
    return -1;
}

int *build_adjacency_table1(const struct Mesh *m){
    //space allocation
    int * adj = (int*) malloc(3* m->ntri* sizeof(int));
    //-1 everywhere
    for (int i = 0; i < 3* m->ntri; i++){
        adj[i] = -1;
    }
    //loop over all triagnles, loop once more, check adjacency 
    for (int i = 0; i < m->ntri; i++){
        for (int j = 0; j < m->ntri; j++){
            //r = position of the edge of triangle i
            int r = tris_are_neighbors(i, j, m);    //not m->triangles[i], ... because tris are neighbors takes indices...
            if (r != -1){  //if r == -1 -> no adjacency
                adj[3*i + r] = j;  //j = index of the adjacent triangle
            }
        }
    //dispose necessary?
    }
    return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    //size_t capacity, size_t key_len, size_t val_len
    /* unsigned capacity; // Nbr of slots in the table
	unsigned key_len; // Size in bytes of each key
	unsigned val_len; // Size in bytes of each value */
    struct HashTable *ht = hash_table_init(3 * m->ntri, sizeof(struct Edge), sizeof(int));  //3 edges & 2 directions per edge
    
    for (int i = 0; i < m->ntri; i++){
        struct Edge e1 = {m->triangles[i].v1, m->triangles[i].v2};
        struct Edge e2 = {m->triangles[i].v2, m->triangles[i].v3};
        struct Edge e3 = {m->triangles[i].v3, m->triangles[i].v1};

        hash_table_insert(ht, &e1, &i);   //returns value --> index of the triangle which contains the edge
        hash_table_insert(ht, &e2, &i);   //void hash_table_insert(struct HashTable *ht, void *key, void *val) --> we need &
        hash_table_insert(ht, &e3, &i);
    }
    return ht;
}

int *build_adjacency_table2(const struct Mesh *m){
    printf("table 2");
    struct HashTable *ht = build_edge_table1(m);

    //adjacency table
    int * adj = (int*) malloc(3* m->ntri* sizeof(int));
    //-1 everywhere
    for (int i = 0; i < 3* m->ntri; i++){
        adj[i] = -1;
    }
    //loop over all tragnles and update adjacency
    for (int i = 0; i < m->ntri; i++){
        //create edges with opposite direction wrt triangle[i]
        struct Edge e1_opp = {m->triangles[i].v2, m->triangles[i].v1}; 
        struct Edge e2_opp = {m->triangles[i].v3, m->triangles[i].v2};
        struct Edge e3_opp = {m->triangles[i].v1, m->triangles[i].v3};

        //look if edge is in hash table
        int* pos0 = (int*) hash_table_find(ht, &e1_opp);  //hash_table_find returns *void, we have to cast
        int* pos1 = (int*) hash_table_find(ht, &e2_opp);
        int* pos2 = (int*) hash_table_find(ht, &e3_opp);

        //if yes, then put index of triangle (value) in adj table 
        if(pos0){
            adj[3 * i + 0] = *pos0;
        }
        if(pos1){
            adj[3 * i + 1] = *pos1;
        }
        if(pos2){
            adj[3 * i + 2] = *pos2;
        }
    }
    hash_table_fini(ht); //dispose ht
    return adj;
}


//third and optimal strategy
struct EdgeTable {
    int *head;
    int *next;
};

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
    et->head = malloc(nvert * sizeof(int));
    et->next = malloc(3 * ntri *sizeof(int));
    for (int i = 0; i < nvert; i++){   //all heads to -1 --> no entry yet
        et->head[i] = -1;
    }
    for (int i = 0; i < 3 * ntri; i++){
        et->next[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et){
    free(et->head);
    free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){
    //edge_code = 3*i+j
    if(et->head[v1] == -1){   //if free space, put index of where we can find the vertex in the mesh (edge_code)
        et->head[v1] = edge_code;
    }else{ //"chain the appearances of v1"
        int tmp = et->head[v1];
        et->head[v1] = edge_code;
        et->next[edge_code] = tmp;
    }
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
    int edgeCode = et->head[v1];   //first possible triangle 
    int i = edgeCode / 3;
    int j_v1 = edgeCode % 3;
    int j_v2 = (j_v1 + 1) % 3; //theoretical position of v2 (position of v1 + 1)

    //check if vertex at that theoretical position corresponds to v2
    if((j_v2 == 0 && m->triangles[i].v1 == v2) || (j_v2 == 1 && m->triangles[i].v2 == v2) || (j_v2 == 2 && m->triangles[i].v3 == v2)){
        return i; //index of triangle 
    }
    
    while(et->next[edgeCode] != -1){   //loop through other possible triangles
        edgeCode = et->next[edgeCode];
        int i = edgeCode / 3;
        int j_v1 = edgeCode % 3;
        int j_v2 = (j_v1 + 1) % 3;
        //check if vertex at that theoretical position corresponds to v2
        if((j_v2 == 0 && m->triangles[i].v1 == v2) || (j_v2 == 1 && m->triangles[i].v2 == v2) || (j_v2 == 2 && m->triangles[i].v3 == v2)){
            return i;
        }
    }
    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){
    struct EdgeTable *et = malloc(sizeof(struct EdgeTable));
    int nvert = m->nvert;
    int ntri = m->ntri;
    edge_table_initialize(et, nvert, ntri); 
    for (int i = 0; i < m->ntri; i++){    //loop through all triangles
        //loop trough all vertices of triangle
        edge_table_insert(m->triangles[i].v1, 3*i+0, et); //v1 = m->triangles[i].j ; edge_code = 3*i+j 
        edge_table_insert(m->triangles[i].v2, 3*i+1, et);
        edge_table_insert(m->triangles[i].v3, 3*i+2, et);
    }
    return et;
}


int *build_adjacency_table3(const struct Mesh *m){
    printf("table 3");
    //adjacency table
    int * adj = (int*) malloc(3* m->ntri* sizeof(int));
    //-1 everywhere
    for (int i = 0; i < 3* m->ntri; i++){
        adj[i] = -1;
    }

    struct EdgeTable *et = build_edge_table3(m);
    
    for (int i = 0; i < m->ntri; i++){
        int e1_opp = edge_table_find(m->triangles[i].v2, m->triangles[i].v1, et, m);
        int e2_opp = edge_table_find(m->triangles[i].v3, m->triangles[i].v2, et, m);
        int e3_opp = edge_table_find(m->triangles[i].v1, m->triangles[i].v3, et, m);

        if(e1_opp != -1){
            adj[3 * i + 0] = e1_opp;  //put index of adjacent triangle at right position of triangle
        }
        if(e2_opp != -1){
            adj[3 * i + 1] = e2_opp;
        }
        if(e3_opp != -1){
            adj[3 * i + 2] = e3_opp;
        }
    }
    edge_table_dispose(et);
    return adj;
} 
