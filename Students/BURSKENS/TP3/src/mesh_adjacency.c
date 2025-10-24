#include <mesh_adjacency.h>

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
    adj = (int*)malloc(sizeof(int)*3*m->ntri);
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
    return &adj;
}

struct HashTable *build_edge_table1(const struct Mesh *m){
    sizeof(struct Edge) //size of key in bytes
    sizeof(int) //size of value in bytes

}
