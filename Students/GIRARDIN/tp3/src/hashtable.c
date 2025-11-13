#include <stdlib.h>
#include <stdio.h>

#include "../include/mesh.h"
#include "../include/hash_tables.h"
#include "../include/hashtable.h"

int edge_pos_in_tri(int v1, int v2, struct Triangle t){

    if((v1 == t.v1) && (v2 == t.v2)){return 0;}     //Edge 0
    if((v1 == t.v2) && (v2 == t.v3)){return 1;}     //Edge 1
    if((v1 == t.v3) && (v2 == t.v1)){return 2;}     //Edge 2
    return NOTEXIST;                                //(Oriented) edge doesn't exist
}

//-------------------------------------------------------------------------
int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){

    struct Triangle t1 = (m->triangles)[tri1];
    struct Triangle t2 = (m->triangles)[tri2];

    int common_edge = NOTEXIST;

    //check if the edge of t2 (in opposite orientation) are in t1
    common_edge = edge_pos_in_tri(t2.v2,t2.v1,t1);
    if(common_edge != NOTEXIST){return common_edge;}

    common_edge = edge_pos_in_tri(t2.v3,t2.v2,t1);
    if(common_edge != NOTEXIST){return common_edge;}

    common_edge = edge_pos_in_tri(t2.v1,t2.v3,t1);
    if(common_edge != NOTEXIST){return common_edge;}

    return NOTEXIST;
}

//-------------------------------------------------------------------------
int *build_adjacency_table1(const struct Mesh *m){

    //Allocate space
    size_t len_adj = 3*(m->ntri);
    int *adj = malloc(len_adj*sizeof(int));

    //Initialise adj
    for(size_t i = 0; i < len_adj; i++){adj[i] = NOTEXIST;}

    //Update adj
    for(int i = 0; i < m->ntri; i++){
        for(int k  = 0; k < m->ntri; k++){
            if(i != k){
                int j = tris_are_neighbors(i,k,m);
                if(j >= 0){adj[3*i + j] = k;}        //if they are neighbors
            }
        }
    }
    return adj;
}

//-------------------------------------------------------------------------
struct HashTable *build_edge_table1(const struct Mesh *m){

    struct HashTable *table = hash_table_init(3*(m->ntri), sizeof(struct Edge), sizeof(int));

    for(int i = 0; i < m->ntri; i++){
        struct Triangle t = (m->triangles)[i];
        struct Edge e1 = {t.v1, t.v2};
        struct Edge e2 = {t.v2, t.v3};
        struct Edge e3 = {t.v3, t.v1};

        hash_table_insert(table, &e1, &i);
        hash_table_insert(table, &e2, &i);
        hash_table_insert(table, &e3, &i);
    }
    return table;
}

//-------------------------------------------------------------------------
int *build_adjacency_table2(const struct Mesh *m){
;
    //Allocate space
    size_t len_adj = 3*(m->ntri);
    int *adj = malloc(len_adj*sizeof(int));

    //Edge hash table
    struct HashTable *edgetab = build_edge_table1(m);

    for(int i = 0; i < m->ntri; i++){
        struct Triangle t = (m->triangles)[i];

        //Opposing edges
        struct Edge e1 = {t.v2, t.v1};
        struct Edge e2 = {t.v3, t.v2};
        struct Edge e3 = {t.v1, t.v3};

        /*Checking if the opposing edges exist in some triangle; 
        if yes, add the index at address k to adj*/ 

        int *k = (int *)hash_table_find(edgetab, &e1);
        if(k != NULL){adj[3*i] = *k;}        //Edge e1 is adjencent to the edge 0 of t
        else{adj[3*i] = NOTEXIST;}

        k = (int *)hash_table_find(edgetab, &e2);
        if(k != NULL){adj[3*i + 1] = *k;}    //Edge e2 is adjencent to the edge 1 of t
        else{adj[3*i + 1] = NOTEXIST;}

        k = (int *)hash_table_find(edgetab, &e3);
        if(k != NULL){adj[3*i + 2] = *k;}    //Edge e3 is adjencent to the edge 2 of t
        else{adj[3*i + 2] = NOTEXIST;}
    }
    hash_table_fini(edgetab);
    return adj;
}

//-------------------------------------------------------------------------
void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
    //Allocating memory
    et->head = malloc(nvert*sizeof(int));
    et->next = malloc(3*ntri*sizeof(int));

    //Initialising all entries of head to -1
    for(int i = 0; i < nvert; i++){
        (et->head)[i] = NOTEXIST;
    }

    //Initialising all entries of next to -1
    for(int i = 0; i < 3*ntri; i++){
        (et->next)[i] = NOTEXIST;
    }
}

//-------------------------------------------------------------------------
void edge_table_dispose(struct EdgeTable *et){
    free(et->head);
    free(et->next);
    free(et);
}

//-------------------------------------------------------------------------
void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){

    if((et->head)[v1] == NOTEXIST){     //empty slot
        (et->head)[v1] = edge_code;
      
    }else{                              //not empty; chaining
        int tmp = (et->head)[v1];
        (et->head)[v1] = edge_code;
        (et->next)[edge_code] = tmp;
    }
}

//-------------------------------------------------------------------------
int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){

    if(!et){return NOTEXIST;}

    int edge_code = (et->head)[v1];
 
    while(edge_code != NOTEXIST){       //while slot is not empty

        int j = edge_code % 3;          //Index of edge associated to edge_code
        int i = (edge_code - j)/3;      //index of triangle associated to edge_code

        if((j == 0) && (v2 == (m->triangles)[i].v2)){   //v1->v2 is first edge of triangle i
            return edge_code;
        }
        if((j == 1) && (v2 == (m->triangles)[i].v3)){   //v1->v2 is second edge of triangle i
            return edge_code;
        }
        if((j == 2) &&(v2 == (m->triangles)[i].v1)){    //v1->v2 is third edge of triangle i
            return edge_code;
        }

        edge_code = (et->next)[edge_code];      //continue along the chain
    }

    return NOTEXIST;
}

//-------------------------------------------------------------------------
struct EdgeTable *build_edge_table3(const struct Mesh *m){

    struct EdgeTable *edgetable = malloc(sizeof(struct EdgeTable));
    edge_table_initialize(edgetable, m->nvert, m->ntri);

    for(int i = 0; i < m->ntri; i++){
        struct Triangle t = (m->triangles)[i];

        edge_table_insert(t.v1, 3*i, edgetable);
        edge_table_insert(t.v2, 3*i + 1, edgetable);
        edge_table_insert(t.v3, 3*i + 2, edgetable);
    }

    return edgetable;
}

//-------------------------------------------------------------------------
int *build_adjacency_table3(const struct Mesh *m){

    //Allocate space
    size_t len_adj = 3*(m->ntri);
    int *adj = malloc(len_adj*sizeof(int));

    //Edge table
    struct EdgeTable *edgetab = build_edge_table3(m);

    for(int i = 0; i < m->ntri; i++){
        struct Triangle t = (m->triangles)[i];

        if(i%2500 == 0){
            printf("### i = %d / %d\n", i, m->ntri);
        }

        /*Checking if the opposing edges exist in some triangle; 
        if yes, add the index k to adj*/ 
        int e = edge_table_find(t.v2, t.v1, edgetab, m);
        int k = (e - (e%3))/3;
        if(e != NOTEXIST){adj[3*i] = k;}        //Edge e1 is adjencent to the edge 0 of t
        else{adj[3*i] = NOTEXIST;}

        e = edge_table_find(t.v3, t.v2, edgetab, m);
        k = (e - (e%3))/3;
        if(e != NOTEXIST){adj[3*i + 1] = k;}    //Edge e2 is adjencent to the edge 1 of t
        else{adj[3*i + 1] = NOTEXIST;}

        e = edge_table_find(t.v1, t.v3, edgetab, m);
        k = (e - (e%3))/3;
        if(e != NOTEXIST){adj[3*i + 2] = k;}    //Edge e3 is adjencent to the edge 2 of t
        else{adj[3*i + 2] = NOTEXIST;}
    }

    edge_table_dispose(edgetab);
    return adj;
}