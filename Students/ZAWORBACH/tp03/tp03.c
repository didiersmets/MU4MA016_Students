#include <stdio.h>
#include "../tp02/include/mesh2d.h"
#include "../tp02/include/triangle.h"


int edge_pos_in_tri(int v1 , int v2 , const struct Triangle *t)
{
    // if v1->v2 is edge a->b return 1
    if ((t->v1 == v1 && t->v2 == v2) || (t->v1 == v2 && t->v2 == v1)) {
        return 1;
    }
    if ((t->v2 == v1 && t->v3 == v2) || (t->v2 == v2 && t->v3 == v1)) {
        return 2;
    }
    if ((t->v3 == v1 && t->v1 == v2) || (t->v3 == v2 && t->v1 == v1)) {
        return 3;   
    }
    return -1;
}

int tris_are_neighbors(const int tri1, const int tri2, const struct mesh2d *m)
{
    const struct Triangle *t1 = &m->tri[tri1];
    const struct Triangle *t2 = &m->tri[tri2];

    int position = 0;
    if ((position = edge_pos_in_tri(t1->v1, t1->v2, t2)) != -1) {
        return position;
    }
    if ((position = edge_pos_in_tri(t1->v2, t1->v3, t2)) != -1) {
        return position;
    }
    if ((position = edge_pos_in_tri(t1->v3, t1->v1, t2)) != -1) {
        return position;    
    }

    return -1;
}

int *build_adjacency_table1(const struct mesh2d *m)
{
    int adj[3*m->nt];
    for (int i=0; i<m->nt; i++){
        adj[3*i] = -1;
        adj[3*i+1] = -1;
        adj[3*i+2] = -1;
    }

    for (int i=0; i<m->nt; i++){
        for (int j=i+1; j<m->nt; j++){
            int pos = tris_are_neighbors(i, j, m);
            if (pos != -1){
                adj[3*i + pos - 1] = j;
                int pos2 = tris_are_neighbors(j, i, m);
                adj[3*j + pos2 - 1] = i;
            }
        }   
    }
    return adj;
}

