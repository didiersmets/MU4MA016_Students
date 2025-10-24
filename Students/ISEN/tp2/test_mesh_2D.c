#include "mesh_2D.h"



int main(void){
    struct Mesh2D *test_m = malloc(sizeof(struct Mesh2D));

    //test read_mesh
    read_mesh2D(test_m, "mesh1_tp2.mesh");
    printf("%d %d", test_m->nt, test_m->nv);
    for (int i = 0; i < test_m->nt; i++){
        printf("Vertices %Lf %Lf\n", test_m->vert[i].x, test_m->vert[i].y);
    }
    for (int i = 0; i < test_m->nv; i++){
        printf("Triangles %d %d %d", test_m->tri[i].a, test_m->tri[i].b, test_m->tri[i].c);
    }

    //test mesh to gnu
    

    //test write_mesh

    free(test_m);
}


