#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>


struct Vertex{
    double x;
    double y;
    double z;
};

struct Triangle{
    struct Vertex * vertecies[3];
};

void initiate_trianlge(struct Triangle tri, struct Vertex A, struct Vertex B, struct Vertex C){
    tri.vertecies[0]=&A;
    tri.vertecies[1]=&B;
    tri.vertecies[2]=&C;
}

struct Mesh3D{
    int nv; // number of total vertices
    struct Vertex* vert; // array of all vertices in mesh
    int nt; // number of triangles in mesh
    struct Triangle *tri;

};


int initialize_Mesh3D(struct Mesh3D* m, int vtx_capacity, int tri_capacity){
    m=(struct Mesh3D *)malloc(sizeof(struct Mesh3D));

    m->nv=0;
    m->vert=(struct Vertex *)malloc(sizeof(struct Vertex)*vtx_capacity);
    m->nt=0;
    m->tri=(struct Triangle *)malloc(sizeof(struct Triangle)*tri_capacity);

    if (m==NULL){return -1;}
    return 0;
}

void dispose_Mesh3D(struct Mesh3D* m){
    free(m->vert);
    free(m->tri);
    free(m);
}

double area_triangle2D(struct Triangle tri){
    double area= 1/2* (tri.vertecies[0]->x*(tri.vertecies[1]->y-tri.vertecies[2]->y)+
                        tri.vertecies[1]->x*(tri.vertecies[2]->y-tri.vertecies[0]->y)+
                        tri.vertecies[2]->x*(tri.vertecies[0]->y-tri.vertecies[1]->y));
    return fabs(area);
}

double area_triangle3D(struct Triangle tri){
    double xx=  (tri.vertecies[1]->y-tri.vertecies[0]->y)*(tri.vertecies[2]->z-tri.vertecies[0]->z)-
            (tri.vertecies[1]->z-tri.vertecies[0]->z)*(tri.vertecies[2]->y-tri.vertecies[0]->y);
    double yy=  (tri.vertecies[1]->z-tri.vertecies[0]->z)*(tri.vertecies[2]->x-tri.vertecies[0]->x)-
            (tri.vertecies[1]->x-tri.vertecies[0]->x)*(tri.vertecies[2]->z-tri.vertecies[0]->z);
    double zz=  (tri.vertecies[1]->x-tri.vertecies[0]->x)*(tri.vertecies[2]->y-tri.vertecies[0]->y)-
            (tri.vertecies[1]->y-tri.vertecies[0]->y)*(tri.vertecies[2]->x-tri.vertecies[0]->x);

    double area=1/2*sqrt(pow(xx,2) + pow(yy,2) + pow(zz,2));
    return area;
}

double area_Mesh3D(struct Mesh3D* m){
    int area=0;
    for (int i =0; i< m->nt; i++){
        area+=area_triangle3D(m->tri[i]);
    }
    return area;
}

double *barycenter_triangle(struct Triangle *tri){
    double x= 1/3*(tri->vertecies[0]->x+tri->vertecies[0]->y+tri->vertecies[0]->z);
    double y=1/3*(tri->vertecies[1]->x+tri->vertecies[1]->y+tri->vertecies[1]->z);
    double z=1/3*(tri->vertecies[2]->x+tri->vertecies[2]->y+tri->vertecies[2]->z);
    double vector[]={x,y,z};
    return vector;
}

double *normalized_norm(struct Vertex *A, struct Vertex *B, struct Vertex *C){
    double x= (B->y-A->y)*(C->z-A->z)-(C->y-A->y)*(B->z-A->z);
    double y= (B->x-A->x)*(C->z-A->z)-(C->x-A->x)*(B->z-A->z);
    double z= (B->x-A->x)*(C->y-A->y)-(C->x-A->x)*(B->y-A->y);
    double norm= sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    double vector[]={x/norm,y/norm,z/norm};
    return vector;
}

double volume_Mesh3D(struct Mesh3D* m){
    int volume=0;
    double scalar_prod;
    for (int i =0; i< m->nt; i++){
        scalar_prod=0;
        for (int j=0; j<3; j++){
            scalar_prod+=normalized_norm(&(m->tri[i].vertecies[0]), &(m->tri[i].vertecies[1]), &(m->tri[i].vertecies[2]))[j]* barycenter_triangle(&(m->tri[i]))[j];
        }
        volume+=area_triangle3D(m->tri[i])*scalar_prod;
    }
    return volume;
}



int main(int argc, char** argv ){

    struct Vertex A ;
    A.x=0;
    A.y=0;
    A.z=0;
    struct Vertex B ;
    B.x=1;
    B.y=0;
    B.z=0;
    struct Vertex C ;
    C.x=1;
    C.y=1;
    C.z=0;
    struct Vertex D ;
    D.x=1;
    D.y=0;
    D.z=1;
    printf("Triangle File\n");


    return 0;
}