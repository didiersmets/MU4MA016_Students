#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Vertex
{
  double coor_x;
  double coor_y;
}

struct Triangle
{
  Vertex point_1;
  Vertex point_2;
  Vertex point_3;
}

struct Mesh2D
{
  int nv;//number of vertices
  Vertex* vert;
  int nt;//number of triangles
  Triangle* tri;
}

int init_mesh2D(struct Mesh2D* m,int vtx_capacity, int tri_capacity)
{
  struct Mesh2D mesh = malloc(sizeof(struct Mesh2D));
  if (m != NULL){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    
  }
  
}

void dispose_mesh2D(struct Mesh2D* m)
{
  
}
