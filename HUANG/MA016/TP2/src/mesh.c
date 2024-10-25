#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Vertex
{
  double x;
  double y;
}

struct Triangle
{
  int a;
  int b;
  int c;
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
  if (m != NULL){
    m->nv = 0;
    m->nt = 0;
    m->vert = malloc(vtx_capacity *sizeof(struct Vertex));
    m->tri = malloc(tri_capacity * sizeof(struct Triangle));
  }
  return 0
}

void dispose_mesh2D(struct Mesh2D* m)
{
  if (m!= NULL){
    free(m->vert);
    free(m->tri);
  }
}

double area_mesh2D(struct Mesh2D* m)
{
  if(m->tri == NULL){
    return 0
  }
  
  double area=0;

  for(int j=0,j<m->nt,j++){
    struct Vertex *c1=m->tri[j]->a;
    struct Vertex *c2=m->tri[j]->b;
    struct Vertex *c3=m->tri[j]->b;
    double surface =0.5* ((c2->x - c1-> x)*(c3->y - c1->y)-(c2->y - c1-> y)*(c3->x - c1-> x));
    area += surface; 
  }
  return area;
}

int read_mesh2D(struct Mesh2D* m,const char* filename)
{
	FILE* f;
	f= fopen("filename","r");
	if(f==NULL){
		return 1
	}
	
	fclose(f);

}


