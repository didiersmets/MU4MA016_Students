#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vertex
{
    double x;
    double y;
};

struct Triangle
{
    int v1;     //index of first vertex
    int v2;     //index of second vertex
    int v3;     //index of third vertex
};

struct Mesh2D
{
    size_t nv;              //number of vertices
    struct Vertex* vert;    //actual vertices
    size_t nt;              //number of triangles
    struct Triangle* tri;   //actual triangles
};

int initialize_mesh2D(struct Mesh2D* m, int vxt_capacity, int tri_capacity){
    m->nv = 0;
    m->nt = 0;
    m->vert = (struct Vertex*) malloc(vxt_capacity*sizeof(struct Vertex));
    m->vert = (struct Triangle*) malloc(tri_capacity*sizeof(struct Triangle));
    return EXIT_SUCCESS;
}

void dispose_mesh2D(struct Mesh2D* m){
    m->nv = 0;
    m->nt = 0;
    free(m->vert);
    free(m->tri);
}

double area_mesh2D(struct Mesh2D* m){
    double area = 0;
    for(int i = 0; i < m->nt; i++){
        
        //Vertices of triangle of index i
        struct Vertex v1 = (m->vert)[(m->tri[i]).v1];
        struct Vertex v2 = (m->vert)[(m->tri[i]).v2];
        struct Vertex v3 = (m->vert)[(m->tri[i]).v3];
        
        //First and second edge
        struct Vertex e1 = {v2.x - v1.x, v2.y - v1.y};
        struct Vertex e2 = {v3.x - v2.x, v3.y - v2.y};

        //Add the area of thr triangle i
        area += (e1.x*e2.y - e2.x*e1.y)/2;
    }

    return area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename){
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
        check = sscanf(line, "Dimension %d", &dim);
    }while(check != 1);

    //Checking dimension
    if(dim != 2){
        printf("Wrong dimension ! Expected : 2, Given : %d \n", dim);
    }
    
    //Loading number of vertices
    do{
        fgets(line, len_line, file);
        check = sscanf(line, "Vertices %d", &(m->nv));
    }while(check != 1);

    //Loading vertices
    for(int i = 0; i < m->nv; i++){
        do{
            fgets(line, len_line, file);
            check = sscanf(line, " %ld %ld", (m->vert)[i].x, (m->vert[i]).y);
        }while(check != 2);
    }

    //Loading number of triangles
    do{
        fgets(line, len_line, file);
        check = sscanf(line, "Triangle %d", &(m->nt));
    }while(check != 1);

    //Loading triangles
    for(int i = 0; i < m->nt; i++){
        do{
            fgets(line, len_line, file);
            check = sscanf(line, " %d %d %d", (m->tri)[i].v1, (m->tri[i]).v2, (m->tri[i]).v3);
        }while(check != 3);
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){
    FILE* file = fopen(filename, "a+");

}

int write_mesh2D(struct Mesh2D* m, const char* filename){
    FILE* file = fopen(filename, "r+");

    fprintf(file, " MeshVersionFormatted 2\n");
    fprintf(file, " Dimension 2\n");
    fprintf(file, " Vertices %d\n", (m->nv));

    //Print vertices
    for(int i = 0; i < m->nv; i++){
        fprintf(file, "%.16f %.16f %.16f\t1\n", (m->vert[i]).x, (m->vert[i]).y, 0);
    }

    fprintf(file, " Trianfles %d\n", (m->nt));

    //Print triangles
    for(int i = 0; i < m->nt; i++){
        fprintf(file, "%d %d %d 1\n", (m->tri[i]).v1, (m->tri[i]).v2, (m->tri[i]).v3);
    }

    fprintf("End");
    fclose(file);
    return EXIT_SUCCESS;
}