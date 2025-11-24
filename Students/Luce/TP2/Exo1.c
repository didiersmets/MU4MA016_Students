#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef struct Vertex{
    double x;
    double y;
}Vertex;

typedef struct Triangle{
    int index_pt1;
    int index_pt2;
    int index_pt3;
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

    if (!m->vert || !m->tri){
        return 0;
    }
    return 1;
}

void dispose_mesh2D(struct Mesh2D*m){
    if (!m) return;
    free(m->vert);
    free(m->tri);
    free(m);
}

double area_mesh2D(struct Mesh2D* m){ //je comprends que c'est la somme de l'air de chaque triangle de mesh2D

    double aire = 0;

    for(int i=0; i<(m->nt); i++){

        Vertex A = m->vert[(m->tri[i]).index_pt1]; //points A,B et C du trangle i
        Vertex B = m->vert[(m->tri[i]).index_pt2];
        Vertex C = m->vert[(m->tri[i]).index_pt3];

        Vertex AB; //vecteur AB
        AB.x = B.x - A.x;
        AB.y = B.y - A.y;

        Vertex AC;
        AC.x = C.x - A.x;
        AC.y = C.y - A.y;

        aire += 1/2*(AB.x*AC.y-AC.x*AB.y); //déterminant de la matrice composée des vecteurs colonnes AB et AC, qui divisé par 2 donne l'aire signé du trangle ABC
    }

    return aire;
}

int main(){
    return 0;
}