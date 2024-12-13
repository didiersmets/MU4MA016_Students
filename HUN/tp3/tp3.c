
#include <stdio.h>
#include <stdlib.h>
#include "include/hash_tables.h"


struct Vertex {
  double x;
  double y;
} ;

struct Triangle {
  int v1;
  int v2;
  int v3;
} ;


struct Mesh {
  int       nv ;         // number of vertices
  int       nt ;         // numbers of triangles
  struct Vertex   *vert;        // addr of vertices
  struct Triangle *tri;         // addr of triangles
} ;


struct Edge {
  int v1;
  int v2;
};



int edge_pos_in_tri(int v1, int v2, struct Triangle t) {
  if (v1==t.v1 && v2==t.v2) {return 0;}
  if (v1==t.v2 && v2==t.v3) {return 1;}
  if (v1==t.v3 && v2==t.v1) {return 2;}
  return -1;
}

int tris_are_neighbors(int tri1, int tri2, const struct Mesh *m) {
  struct Triangle T1 = m->tri[tri1];
  struct Triangle T2 = m->tri[tri2];
  
  if ( 1 == edge_pos_in_tri(T2.v2, T2.v1, T1)) {return 1;}
  if ( 2 == edge_pos_in_tri(T2.v3, T2.v2, T1)) {return 2;}
  if ( 3 == edge_pos_in_tri(T2.v1, T2.v3, T1)) {return 3;}

  return -1;
}


int *build_adjacent_table1(const struct Mesh *m) {
  int ntri = m->nt;
  int *adj = (int *)malloc(3 * ntri * sizeof(int));
  for (int i=0; i<3*ntri; i++){adj[i] = -1;}

  for (int i=0; i<ntri; i++){
    for (int k=0; k<ntri; k++){
      if (k!=i){
	int j = tris_are_neighbors(i, k, m)  ;
	if (j!=-1) {adj[3*i + j] = k;}
      }
    }
  }
  return adj;
}


struct HashTable *build_edge_table(const struct Mesh *m) {
  int ntri =  m->nt;
  struct HashTable *ht = hash_table_init( 6*ntri, sizeof(struct Edge),  sizeof(int));
  for(int i=0; i<ntri; i++){
    int val;
    struct Edge e;

    e.v1 = m->tri[i].v1;
    e.v2 = m->tri[i].v2;
    val = 3*i ;
    hash_table_insert(ht, &e, &val);

    e.v1 = m->tri[i].v2;
    e.v2 = m->tri[i].v3;
    val = 3*i + 1;
    hash_table_insert(ht, &e, &val);

    e.v1 = m->tri[i].v3;
    e.v2 = m->tri[i].v1;
    val = 3*i + 2;
    hash_table_insert(ht, &e, &val);
  }

  return *ht;
}



int *build_adjacent_table2(const struct Mesh *m) {
  struct HashTable *ht = build_edge_table(m);
  int ntri = m->nt;
  int *adj = (int *)malloc(3 * ntri * sizeof(int));
  for (int i=0; i<3*ntri; i++){adj[i] = -1;}

  for (int i=0; i<ntri; i++){
    struct Edge e;
    e.v1 = m->tri[i].v2;
    e.v2 = m->tri[i].v1;
    int *pval = (int *)hash_table_find(ht, &e);    // return the index of tri that neighbors to i

    if (pval!=NULL){
      int j = tris_are_neighbors(i, *pval, m);
      adj[3*i + j] = *pval;
    }
  }

  hash_table_fini(ht);
  return adj;
}






int main() {
  return 0;
}

