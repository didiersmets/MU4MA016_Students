#include <mesh_adjacency.h>
#include <hashtable.h>

int edge_pos_in_tri(int v1, int v2, struct Triangle t){
    if(t.v1 == v1 && t.v2 == v2){return 0;}
    if(t.v2 == v1 && t.v3 == v2){return 1;}
    if(t.v3 == v1 && t.v1 == v2){return 2;}
    return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m){
    int temp = edge_pos_in_tri(m->triangles[tri2].v2, m->triangles[tri2].v1, m->triangles[tri1]);
    if( temp != -1){return temp;}
    temp = edge_pos_in_tri(m->triangles[tri2].v3, m->triangles[tri2].v2, m->triangles[tri1]);
    if( temp != -1){return temp;}
    temp = edge_pos_in_tri(m->triangles[tri2].v1, m->triangles[tri2].v3, m->triangles[tri1]);
    return temp;
}

int *build_adjacency_table1(const struct Mesh *m){
    int* adj = (int*)malloc(sizeof(int)*3*m->ntri);
    for(int i = 0; i < 3*m->ntri; i++){
        adj[i] = -1;
    }
    for(int i = 0; i < m->ntri; i++){
        for(int k = 0; k < m->ntri; k++){
            int j = tris_are_neighbors(m->triangles[i],m->triangles[k], m);
            if(j != -1){
                adj[3*i + j] = k;
            }
        }
    }
    return adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    struct HashTable *edg = hash_table_init(3*m->ntri,sizeof(struct Edge),sizeof(int));
    for(int k = 0; k < m->ntri; k++){
        struct Edge e0 = {m->triangles[k].v1, m->triangles[k].v2};
        struct Edge e1 = {m->triangles[k].v2, m->triangles[k].v3};
        struct Edge e2 = {m->triangles[k].v3, m->triangles[k].v1};
        hash_table_insert(edg,e0,k);
        hash_table_insert(edg,e1,k);
        hash_table_insert(edg,e2,k);
        }
    return edg;
}

int *build_adjacency_table2(const struct Mesh *m){
    int* adj = (int*)malloc(sizeof(int)*3*m->ntri);
    struct HashTable *edge_table = build_edge_table1(m);
    for(int k = 0; k < m->ntri; k++){
        struct Edge rev_e0 = {m->triangles[k].v2, m->triangles[k].v1};
        void* address = hash_table_find(edge_table,&rev_e0);
        if(address){
            int* tri_index = address;
            adj[3*k+0] = tri_index;
        }
        else{
            adj[3*k+0] = -1;
        }
        struct Edge rev_e1 = {m->triangles[k].v3, m->triangles[k].v2};
        void* address = hash_table_find(edge_table,&rev_e1);
        if(address){
            int* tri_index = address;
            adj[3*k+1] = tri_index;
        }
        else{
            adj[3*k+1] = -1;
        }
        struct Edge rev_e2 = {m->triangles[k].v1, m->triangles[k].v3};
        void* address = hash_table_find(edge_table,&rev_e2);
        if(address){
            int* tri_index = address;
            adj[3*k+2] = tri_index;
        }
        else{
            adj[3*k+2] = -1;
        }
    }
    hash_table_fini(edge_table);
    return adj;
}

void edge_table_initialize(struct EdgeTable *et, int nvert, int ntri){
    et->head = malloc(nvert*sizeof(int));
    et->next = malloc(3*ntri*sizeof(int));
    for(int i = 0; i < nvert; i++){
        et->head[i] = -1;
    }
    for(int i = 0; i < 3*ntri; i++){
        et->next[i] = -1;
    }
}

void edge_table_dispose(struct EdgeTable *et){
    free(et->head);
    free(et->next);
}

void edge_table_insert(int v1, int edge_code, struct EdgeTable *et){
    if(et->head[v1] == -1){
        et->head[v1] = edge_code;
    }
    else{
        int temp = et->head[v1];
        et->head[v1] = edge_code;
        et->next[edge_code] = temp;
    }
}

int edge_table_find(int v1, int v2, const struct EdgeTable *et, const struct Mesh *m){
    int current_edge = et->head[v1];
    if(edge_pos_in_tri(v1, v2,m->triangles[current_tri]) != -1){
            return current_tri;
    }
    while(et->next[current_edge] != -1){
        current_edge = et->next[current_edge];
        int curent_tri = current_edge/3;
        if(edge_pos_in_tri(v1, v2,m->triangles[current_tri]) != -1){
            return curent_tri;
        }

    }
    return -1;
}

struct EdgeTable *build_edge_table3(const struct Mesh *m){
    struct EdgeTable* etable;
    edge_table_initialize(etable,m->nvert,m->ntri);
    for(int k = 0; k < m->ntri; k++){
        edge_table_insert(m->triangles[k].v1,3*k+0,etable);
        edge_table_insert(m->triangles[k].v2,3*k+1,etable);
        edge_table_insert(m->triangles[k].v3,3*k+2,etable);
        }
    return etable;
}

int *build_adjacency_table3(const struct Mesh *m){
    int* adj = (int*)malloc(sizeof(int)*3*m->ntri);
    struct EdgeTable* etable = build_edge_table3(m);
    for(int k = 0; k < m->ntri; k++){
        int tri_index = edge_table_find(m->triangles[k].v2,m->triangles[k].v1,etable,m);
        adj[3*k+0] = tri_index;
        int tri_index = edge_table_find(m->triangles[k].v3,m->triangles[k].v2,etable,m);
        adj[3*k+1] = tri_index;
        int tri_index = edge_table_find(m->triangles[k].v1,m->triangles[k].v3,etable,m);
        adj[3*k+2] = tri_index;
    }
    return adj;
}
