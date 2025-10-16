#include "../include/mesh2D.h"
#include "../include/mesh3D.h"


int main(){

    const char* filename1 = "../meshes/mesh1-tp2.mesh"; 
    const char* filename2 = "../meshes/mesh2-tp2.mesh";

    //2D Meshes ----------------------------------------------------------
    const char* filename1new = "../meshes/mesh1-tp2-new.mesh";
    const char* gnuplot1 = "../plots/mesh1.gnuplot";

    const char* filename2new = "../meshes/mesh2-tp2-new.mesh";
    const char* gnuplot2 = "../plots/mesh2.gnuplot";

    struct Mesh2D m1;
    struct Mesh2D m2;

    read_mesh2D(&m1, filename1);
    read_mesh2D(&m2, filename2);

    printf("Area of mesh 1 : %f\n", area_mesh2D(&m1));
    printf("Area of mesh 2 : %f\n", area_mesh2D(&m2));

    write_mesh2D(&m1, filename1new);
    write_mesh2D(&m2, filename2new);

    mesh2D_to_gnuplot(&m1, gnuplot1);
    mesh2D_to_gnuplot(&m2, gnuplot2);

    //3D Meshes ----------------------------------------------------------
    const char* filename3new = "../meshes/mesh3-tp2-new.mesh";
    const char* gnuplot3 = "../plots/mesh3.gnuplot";

    const char* filename4new = "../meshes/mesh4-tp2-new.mesh";
    const char* gnuplot4 = "../plots/mesh4.gnuplot";

    struct Mesh3D m3;
    struct Mesh3D m4;
    
    read_mesh3D(&m3, filename1);
    read_mesh3D(&m4, filename2);

    printf("Volume of mesh 1 : %f\n", volume_mesh3D(&m3));
    printf("Volume of mesh 2 : %f\n", volume_mesh3D(&m4));

    write_mesh3D(&m3, filename3new);
    write_mesh3D(&m4, filename4new);

    mesh3D_to_gnuplot(&m3, gnuplot3);
    mesh3D_to_gnuplot(&m4, gnuplot4);

    return 0;
}