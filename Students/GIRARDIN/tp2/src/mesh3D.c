#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/mesh3D.h"

int initialize_mesh3D(struct Mesh3D* m, int vxt_capacity, int tri_capacity){
    m->nv = 0;
    m->nt = 0;
    m->vert = (struct Vertex3D*) malloc(vxt_capacity*sizeof(struct Vertex3D));
    m->tri = (struct Triangle3D*) malloc(tri_capacity*sizeof(struct Triangle3D));
    return EXIT_SUCCESS;
}

//-------------------------------------------------------------------------
void dispose_mesh3D(struct Mesh3D* m){
    m->nv = 0;
    m->nt = 0;
    free(m->vert);
    free(m->tri);
}

//-------------------------------------------------------------------------
double volume_mesh3D(struct Mesh3D* m){
    double volume = 0;
    for(int i = 0; i < m->nt; i++){
        
        //Vertices of triangle of index i
        struct Vertex3D v1 = (m->vert)[(m->tri[i]).v1];
        struct Vertex3D v2 = (m->vert)[(m->tri[i]).v2];
        struct Vertex3D v3 = (m->vert)[(m->tri[i]).v3];
        
        //Barycentre b
        struct Vertex3D b = {(v1.x + v2.x + v3.x)/3, (v1.y + v2.y + v3.y)/3, (v1.z +  v2.y + v3.y)/3};

        //First two edges
        struct Vertex3D e1 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
        struct Vertex3D e2 = {v3.x - v2.x, v3.y - v2.y, v3.z - v2.z};

        //Normal vector n (PRODUIT SCALAIRE EDGES)

        struct Vertex3D n = {e1.y*e2.z - e2.y*e1.z, e1.z*e2.x - e2.z*e1.x, e1.x*e2.y - e2.x*e1.y};

        //Add the volume of the triangle i
        volume += n.x*b.x + n.y*b.y + n.z*b.z;
    }
    return volume;
}

//-------------------------------------------------------------------------
int read_mesh3D(struct Mesh3D* m, const char* filename){

  //Loading file
    FILE* file = fopen(filename, "r+");
    if (!file)
    {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    int check = 0;  //Checks correct loading of information from file
    size_t len_line = 128;
    char line[len_line];

  //Loading dimension
    int dim;
    do{
        fgets(line, len_line, file);
        check = sscanf(line, " Dimension %1d", &dim);
    }while(check != 1);
    
  //Checking dimension
    if(dim < 3){
        printf("Wrong dimension ! Expected : 3 (or greater) Given : %d \n", dim);
    }

    int vxt_capacity;
    int tri_capacity;

  //Loading number of vertices
    do{
        fgets(line, len_line, file);
        check = sscanf(line, " Vertices %d", &vxt_capacity);
    }while(check != 1);

  //Loading number of triangles
    do{
        fgets(line, len_line, file);
        check = sscanf(line, " Triangles %d", &tri_capacity);
    }while(check != 1);

    rewind(file);   //to get back to the start and load vertices (which have been skipped before)

  //Initialise the mesh m
    initialize_mesh3D(m,vxt_capacity,tri_capacity);
    m->nv = vxt_capacity;
    m->nt = tri_capacity;

  //Loading vertices
    for(int i = 0; i < m->nv; i++){
        do{
            fgets(line, len_line, file);
            check = sscanf(line, " %Lf %Lf %Lf", &(m->vert)[i].x, &(m->vert)[i].y, &(m->vert)[i].z);
        }while(check != 3);
    }

  //Loading triangles
    for(int i = 0; i < m->nt; i++){
        do{
            fgets(line, len_line, file);
            check = sscanf(line, " %d %d %d", &(m->tri)[i].v1, &(m->tri)[i].v2, &(m->tri)[i].v3);
        }while(check != 3);

        //indexing of the vertices start at 0 (and not 1) in the array vert
        (m->tri)[i].v1 -= 1;
        (m->tri)[i].v2 -= 1;
        (m->tri)[i].v3 -= 1; 
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}

//-------------------------------------------------------------------------
int mesh3D_to_gnuplot(struct Mesh3D* m, const char* filename){

  //Open file
    FILE* file = fopen(filename, "w+");
    if (!file)
    {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

  //Print triangles
    for(int i = 0; i < m->nt; i++){

        //indexing of the vertices start at 1 (not 0 like in the array)
        struct Vertex3D v1 = (m->vert)[(m->tri[i]).v1];
        struct Vertex3D v2 = (m->vert)[(m->tri[i]).v2];
        struct Vertex3D v3 = (m->vert)[(m->tri[i]).v3];

        fprintf(file, "%Lf\t%Lf\t%Lf\n", v1.x, v1.y, v1.z);
        fprintf(file, "%Lf\t%Lf\t%Lf\n", v2.x, v2.y, v2.z);
        fprintf(file, "%Lf\t%Lf\t%Lf\n\n", v3.x, v3.y, v3.z);
    }

    fclose(file);
    return EXIT_SUCCESS;
}

//-------------------------------------------------------------------------
int write_mesh3D(struct Mesh3D* m, const char* filename){

  //Open file
    FILE* file = fopen(filename, "w+");
    if (!file)
    {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    
    fprintf(file, " MeshVersionFormatted 2\n");
    fprintf(file, " Dimension 3\n");
    fprintf(file, " Vertices %ld\n", (m->nv));

  //Print vertices
    for(int i = 0; i < m->nv; i++){
        fprintf(file, " %20Lf      %20Lf      %20Lf      1\n", (m->vert[i]).x, (m->vert[i]).y, (m->vert[i]).z);
    }

    fprintf(file, " Triangles %ld\n", (m->nt));

  //Print triangles
    for(int i = 0; i < m->nt; i++){

        //indexing of the vertices start at 1 (not 0 like in the array)
        int v1 = (m->tri[i]).v1 + 1;
        int v2 = (m->tri[i]).v2 + 1;
        int v3 = (m->tri[i]).v3 + 1;

        fprintf(file, " %d %d %d 1\n", v1, v2, v3);
    }

    fprintf(file, " End");
    fclose(file);

    return EXIT_SUCCESS;
}