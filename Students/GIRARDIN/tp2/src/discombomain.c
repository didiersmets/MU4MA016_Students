#include "../include/mesh3D.h"

int main(){

    //Discombocube
    const char* cubidoo = "../meshes/discombocube.mesh";
    const char* gnucubidoo = "../plots/cubidoo.gnuplot";

    struct Mesh3D cube;
    read_mesh3D(&cube, cubidoo);
    mesh3D_to_gnuplot(&cube, gnucubidoo);

    //Discombosphere
    const char* sphereidoo = "../meshes/sphere.mesh";
    const char* gnusphereidoo = "../plots/sphere.gnuplot";

    struct Mesh3D sphere;
    read_mesh3D(&sphere, sphereidoo);
    mesh3D_to_gnuplot(&sphere, gnusphereidoo);

    return 0;
}