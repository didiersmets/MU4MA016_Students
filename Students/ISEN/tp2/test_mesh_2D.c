#include "mesh_2D.h"



int main(void){
    
    struct Mesh2D *test_m = malloc(sizeof(struct Mesh2D));

    //test read_mesh
    read_mesh2D(test_m, "mesh2-tp2.mesh");
    printf("Number of vertices: %d , number of triangles:  %d\n", test_m->nv, test_m->nt);

    /*for (int i = 0; i < test_m->nv; i++){
        printf("Vertex %d : %Lf %Lf\n", i, test_m->vert[i].x, test_m->vert[i].y);
    }
    for (int i = 0; i < test_m->nt; i++){
        printf("Triangle %d : %d %d %d\n", i, test_m->tri[i].a, test_m->tri[i].b, test_m->tri[i].c);
    } */

    //test mesh to gnu
    mesh_2D_to_gnuplot(test_m, "filename.txt");

    //test write_mesh
    write_mesh2D(test_m, "into_mesh1.txt");

    free(test_m);

}


