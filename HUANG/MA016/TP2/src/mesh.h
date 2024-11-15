//mesh_h
#ifndef MESH_H

#define MESH_H

struct Vertex
{
  double x;
  double y;
};

struct Triangle
{
  int a;
  int b;
  int c;
};

struct Mesh2D
{
  int nv;//number of vertices
  struct Vertex* vert;
  int nt;//number of triangles
  struct Triangle* tri;
};

int init_mesh2D(struct Mesh2D* m,int vtx_capacity, int tri_capacity);
void dispose_mesh2D(struct Mesh2D* m);
double area_mesh2D(struct Mesh2D* m);
int read_mesh2D(struct Mesh2D* m,const char* filename);
int mesh2D_to_gnuplot(struct Mesh2D *m,const char* filename);
int write_mesh2D(struct Mesh2D* m,const char*filename);

#endif //Mesh_H
