#include <stddef.h> // for size_t
#include <mesh.hpp>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    char* filename1 = argv[1];
    char* filename2 = argv[2];
    struct Mesh2D *m;
    read_mesh2D(m, filename1);
    double area = area_mesh2D(m);
    printf("Area: %f",area);
    write_mesh2D(m, filename2);
    dispose_mesh2D(m);
    return 0;
}
