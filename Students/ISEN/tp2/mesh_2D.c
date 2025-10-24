#include "mesh_2D.h"

//NOT FULLY TESTED YET
//missing: index {1,...,nt&nv} in mesh file, a few problems in the read_file, ...

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity){
    m->nt = 0;
    m->nv = 0;
    struct Vertex *ver = malloc(sizeof(struct Vertex) * vtx_capacity);
    struct Triangle *tr = malloc(sizeof(struct Triangle) * tri_capacity);
    m->vert = ver;
    m->tri = tr;
}


void dispose_mesh2D(struct Mesh2D *m){
    m->nt = 0;
    m->nv = 0;
    free(m->vert);
    free(m->tri);
}


double area_mesh2D(struct Mesh2D *m){
    double ar = 0;
    for (int i = 0; i < m->nt; i++){
        //the coordinates
        struct Vertex a = (m->vert)[(m->tri[i]).a];
        struct Vertex b = (m->vert)[(m->tri[i]).b];
        struct Vertex c = (m->vert)[(m->tri[i]).c];

        //the two edges
        struct Vertex d1;
        d1.x = b.x - a.x;
        d1.y = b.y - a.y;

        struct Vertex d2;
        d2.x = c.x - a.x;
        d2.y = c.y - a.y;

        //cross product
        ar += 1/2 * (d1.x * d2.y - d2.x * d2.y);
    }
    return ar;
}

//2  Mesh File --> struct Mesh
int read_mesh2D(struct Mesh2D* m, const char* filename){
    //read a 2D mesh from a .mesh file 
    FILE * mesh_file = fopen(filename, "r");

    char line [128]; //arbitrary number

    int found;
    //version
    int meshversion;
    printf("Hello");
    do{
        fgets(line, 128, mesh_file);
        found = sscanf(line, "MeshVersionFormatted %d", &meshversion);
        printf("Hello");
    }while(found != 1);

    if(meshversion != 1){
            return 0;
        }

    //dimension
    int dim;
    found = 0;
    do{
        fgets(line, 128, mesh_file);
        found = sscanf(line, "Dimension %d", &dim);
    }while(found != 1);

    if(dim < 2){  //if it's >= 2, you could just ingore the other coordinates?
        printf("Invalid dimension");  
        return 0;
        }

    // #vertices
    int num_vert;
    found = 0;
    do{
        fgets(line, 128, mesh_file);
        found = sscanf(line, "Vertices %d", &num_vert);
    }while(found != 1);

    m->nv = num_vert;

    m->vert = (struct Vertex*)malloc(sizeof(struct Vertex) * m->nv);


    // vertices 
    for (int i = 0; i < m->nv; i++){
        fgets(line, 128, mesh_file);
        sscanf(line, "%Lf %Lf", &m->vert[i].x, &m->vert[i].y);   //or Lf if you want double
    }

    // #triangles 
    int num_tri;
    found = 0;
    do{
        fgets(line, 128, mesh_file);
        sscanf(line, "Triangles %d", &num_tri);
    }while(found != 1);

    m->nt = num_tri;
    m->tri = (struct Triangle *)malloc(sizeof(struct Triangle) * m->nt);

    // triangles 
    for (int j = 0; j < m->nt; j++){
        fgets(line, 128, mesh_file);
        sscanf(line, "%d %d %d", &m->tri[j].a, &m->tri[j].b, &m->tri[j].c);
    }

    fclose(mesh_file);
}



//3  struct Mesh -> gnuplot 
int mesh_2D_to_gnuplot(struct Mesh2D* m, const char* filename){
    FILE *file_mesh;
    file_mesh = fopen(filename, "w"); 

    for (int i = 0; i < m->nt; i++){
        double a_x = m->vert[m->tri[i].a].x;
        double a_y = m->vert[m->tri[i].a].y;
        double b_x = m->vert[m->tri[i].b].x;
        double b_y = m->vert[m->tri[i].b].y;
        double c_x = m->vert[m->tri[i].c].x;
        double c_y = m->vert[m->tri[i].c].y;

        fprintf(file_mesh, "%Lf\t%Lf\n", a_x, a_y);
        fprintf(file_mesh, "%Lf\t%Lf\n", b_x, b_y);
        fprintf(file_mesh, "%Lf\t%Lf\n", c_x, c_y);
        fclose(file_mesh);
    }

    FILE *gnu_mesh = fopen("gnu_mesh.txt", "w");
    fprintf(gnu_mesh, "set title '2D Mesh'\n"
        "set xlabel 'x'\n"
        "set ylabel 'y'\n" 
        "plot 'file_mesh.txt'"      
        );
    fclose(gnu_mesh);
    system("gnuplot -p gnu_mesh.txt");
}



//4 struct Mesh -> Mesh File
int write_mesh2D(struct Mesh2D *m, const char* filename){
    FILE *into_mesh;
    into_mesh = fopen(filename, "w"); 

    fprintf(into_mesh, "MeshVersionFormatted 1\n");
    fprintf(into_mesh, "Dimension 2\n");
    fprintf(into_mesh, "Vertices %d\n", m->nv);
    for (int i = 0; i < m->nv; i++){
        fprintf(into_mesh, "%Lf %Lf\n", m->vert[i].x, m->vert[i].y);
    }
    fprintf(into_mesh, "Triangles %d\n", m->nt);
    for (int i = 0; i < m->nt; i++){
        fprintf(into_mesh, "%d\t%d\t%d\n", m->tri[i].a, m->tri[i].b, m->tri[i].c);
    }
    fclose(into_mesh);
}




