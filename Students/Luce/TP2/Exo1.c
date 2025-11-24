#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef struct Vertex{
    double x;
    double y;
}Vertex;

typedef struct Triangle{
    int index;
    Vertex pt1;
    Vertex pt2;
    Vertex pt3;
}Triangle;

typedef struct Mesh2D{
    int nv; //number of vertices in the mesh
    Vertex *vert;

    int nt; //Number of triangles in the msh
    Triangle *tri;
}Mesh2D;

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m = malloc(sizeof(Mesh2D));
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(sizeof(Vertex)*m->nv);
    m->tri = malloc(sizeof(Triangle)*m->nt);

    /*srand(time(NULL));
    for(int i=0; i<(m->nv); i++){
        m->vert[i].x = (double) (rand()%(m->nv+1)); //comme il n'est pas spécifié quels points on doit mettre dans le tableau
        m->vert[i].y = (double) (rand()%(m->nv+1));
    }*/




    return 1;

}


int main(){
    return 0;
}