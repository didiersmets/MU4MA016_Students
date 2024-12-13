
#include <stdio.h>
#include <stdlib.h>

struct Vertex {
  double x;
  double y;
} ;

struct Triangle {
  int v1;
  int v2;
  int v3;
} ;

struct Mesh2D {
  int       nv ;         // number of vertices
  int       nt ;         // numbers of triangles
  struct Vertex   *vert;        // addr of vertices
  struct Triangle *tri;         // addr of triangles
} ;

struct Mesh2D* initialize_Mesh2D(int vtx_capacity, int tri_capacity) {
  if (vtx_capacity<0 || tri_capacity<0) {
    return NULL;
  }

  struct Mesh2D *m = malloc(sizeof(struct Mesh2D));

  m->nv  = vtx_capacity;
  m->nt  = tri_capacity;
  
  m->vert = (struct Vertex*)   malloc(vtx_capacity * sizeof(struct Vertex));
  m->tri  = (struct Triangle*) malloc(tri_capacity * sizeof(struct Triangle));

  if (m->vert==NULL || m->tri==NULL) {
    free(m->vert);
    free(m->tri);
    return NULL;
  }

  return m;
}

void dispose_mesh2D(struct Mesh2D *m) {
  free(m->vert);
  free(m->tri);
  free(m);
}

double area_mesh2D(struct Mesh2D *m) {
  double total_area = 0;
  for (int t=0; t<m->nt; t++){  //calculate each area of m->tri[t]

    // find the coordinates
    double x1 = m->vert[m->tri[t].v1].x;
    double y1 = m->vert[m->tri[t].v1].y;

    double x2 = m->vert[m->tri[t].v2].x;
    double y2 = m->vert[m->tri[t].v2].y;

    double x3 = m->vert[m->tri[t].v3].x;
    double y3 = m->vert[m->tri[t].v3].y;


    double area = 0.5 * ( (x1-x3)*(y2-y1) - (x1-x2)*(y3-y1) );
    total_area += area;
  }
  return total_area;
}

int read_mesh2D(struct Mesh2D *m, const char *filename) {

  FILE* f = fopen(filename, "r");
  char line[300];

  while (!feof(f)) {
    fgets(line, 300, f);
    if (sscanf(line, "Vertices %d", &m->nv) == 1) {
      m->vert = (struct Vertex*) malloc(m->nv * sizeof(struct Vertex));
      for (int i = 0; i<m->nv; i++) {
	fgets(line, 300, f);
	sscanf(line, "%f %f", &m->vert[i].x, &m->vert[i].y);
      }
    }

    if (sscanf(line, "Triangles %d", &m->nt) == 1){
      m->tri = (struct Vertex*) malloc(sizeof(struct Triangle) * m->nt);
      for (int i=0; i<m->nt; i++){
	fgets(line, 300, f);
	sscanf(line, "%d %d %d", &m->tri[i].v1, &m->tri[i].v2, &m->tri[i].v3);
      }
    }

  }

  return 0;
}



////////////////////////////////////////////////

int main() {


  struct Mesh2D* m;

  m = initialize_Mesh2D(5, 3);
  m->vert[0].x = 0.0;  m->vert[0].y = 0.0;
  m->vert[1].x = 4.0;  m->vert[1].y = 0.0;
  m->vert[2].x = 1.0;  m->vert[2].y = 2.0;
  m->tri[0].v1 = 0;
  m->tri[0].v2 = 1;
  m->tri[0].v3 = 2;

  m->vert[3].x = 6.0;  m->vert[3].y = 0.0;
  m->vert[4].x = 6.0;  m->vert[4].y = 3.0;
  m->tri[1].v1 = 1;
  m->tri[1].v2 = 4;
  m->tri[1].v3 = 3;


  double area = area_mesh2D(m);
  printf("%f\n", area);


  return 0;
}
