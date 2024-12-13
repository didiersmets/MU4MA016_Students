
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Vertex3 {
  double x;
  double y;
  double z;
} ;

struct Triangle3 {
  int v1;
  int v2;
  int v3;
} ;

struct Mesh3D {
  int       nv ;                // number of vertices
  int       nt ;                // numbers of triangles
  struct Vertex3   *vert;        // addr of vertices
  struct Triangle3 *tri;         // addr of triangles
} ;

struct Mesh3D* initialize_Mesh3D(int vtx_capacity, int tri_capacity) {
  if (vtx_capacity<0 || tri_capacity<0) {
    return NULL;
  }

  struct Mesh3D *m = malloc(sizeof(struct Mesh3D));

  m->nv  = vtx_capacity;
  m->nt  = tri_capacity;
  
  m->vert = (struct Vertex3*)   malloc(vtx_capacity * sizeof(struct Vertex3));
  m->tri  = (struct Triangle3*) malloc(tri_capacity * sizeof(struct Triangle3));

  if (m->vert==NULL || m->tri==NULL) {
    free(m->vert);
    free(m->tri);
    return NULL;
  }

  return m;
}

void dispose_mesh3D(struct Mesh3D *m) {free(m->vert);
  free(m->tri);
  free(m);
}

double area_triangle(struct Mesh3D *m, int t) {

  // find the coordinates
  double x1 = m->vert[m->tri[t].v1].x;
  double y1 = m->vert[m->tri[t].v1].y;
  double z1 = m->vert[m->tri[t].v1].z;

  double x2 = m->vert[m->tri[t].v2].x;
  double y2 = m->vert[m->tri[t].v2].y;
  double z2 = m->vert[m->tri[t].v2].z;

  double x3 = m->vert[m->tri[t].v3].x;
  double y3 = m->vert[m->tri[t].v3].y;
  double z3 = m->vert[m->tri[t].v3].z;

  double a = x2 - x1;
  double b = y2 - y1;
  double c = z2 - z1;

  double d = x3 - x1;
  double e = y3 - y1;
  double f = z3 - z1;

  double A = pow(b * f - c * e, 2);
  double B = pow(a * f - c * d, 2);
  double C = pow(a * e - b * d, 2);

  return 0.5 * sqrt(A + B + C);
}

double area_mesh3D(struct Mesh3D *m) {
  double total_area = 0;
  for (int t=0; t< m->nt; t++){

    total_area  += area_triangle(m, t);
  }

  return total_area;
}

double volume_mesh3D(struct Mesh3D *m) {
  double total_volume = 0;

  for(int t=0; t<m->nt; t++){

    double x1 = m->vert[m->tri[t].v1].x;
    double y1 = m->vert[m->tri[t].v1].y;
    double z1 = m->vert[m->tri[t].v1].z;
    double x2 = m->vert[m->tri[t].v2].x;
    double y2 = m->vert[m->tri[t].v2].y;
    double z2 = m->vert[m->tri[t].v2].z;
    double x3 = m->vert[m->tri[t].v3].x;
    double y3 = m->vert[m->tri[t].v3].y;
    double z3 = m->vert[m->tri[t].v3].z;
    double a = x2-x1;
    double b = y2-y1;
    double c = z2-z1;
    double d = x3-x1;
    double e = y3-y1;
    double f = z3-z1;

    double dotproduct = (x1+x2+x3)*(b*f-e*c) + (y1+y2+y3)*(d*c-a*f) + (z1+z2+z3)*(a*e+b*d);
    double area = area_triangle(m, t);

    total_volume += area * dotproduct / 3;
  }

  return total_volume;
}






int main() {



  struct Mesh3D*m = initialize_Mesh3D(5, 2);
  m->vert[0].x = 0.0;  m->vert[0].y = 0.0; m->vert[0].z = 0.0;
  m->vert[1].x = 4.0;  m->vert[1].y = 0.0; m->vert[1].z = 0.0; 
  m->vert[2].x = 1.0;  m->vert[2].y = 2.0; m->vert[2].z = 0.0;
  m->tri[0].v1 = 0;
  m->tri[0].v2 = 1;
  m->tri[0].v3 = 2;

  m->vert[3].x = 6.0;  m->vert[3].y = 0.0; m->vert[3].z = 0.0;
  m->vert[4].x = 6.0;  m->vert[4].y = 3.0; m->vert[4].z = 0.0;
  m->tri[1].v1 = 1;
  m->tri[1].v2 = 4;
  m->tri[1].v3 = 3;


  double area = area_mesh3D(m);
  printf("%f\n", area);

  /* printf("Hello there"); */

  return 0;
}
