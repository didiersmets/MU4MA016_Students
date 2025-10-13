#include <stdlib.h>
#include <stdio.h>
#include <mesh.hpp>


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->ntri = tri_capacity;
    m->nvert = vtx_capacity;
    m->vertices = (Vertex*) malloc(2*sizeof(double)*vtx_capacity);
    m->triangles = (Triangle*) malloc(3*sizeof(int)*tri_capacity);
    return 0;
}

void dispose_mesh2D(struct Mesh2D* m) {
    free(m->triangles);
    free(m->vertices);
}

struct Vector vect(struct Vertex v, struct Vertex w) {
    struct Vector vw;
    vw.x_length = v.x_coordinate - w.x_coordinate;
    vw.y_length = v.y_coordinate - w.y_coordinate;
    return vw;
}

double area_mesh2D(struct Mesh2D* m) {
    double area = 0;
    int trinum = m->ntri;
    for(int i = 0; i < trinum; i++) {
        double ab[2] = vect(m->vertices[m->triangles[i].a],m->vertices[m->triangles[i].b]);
        double ac[2] = vect(m->vertices[m->triangles[i].a],m->vertices[m->triangles[i].c]);
        double tri_area = (ab[1]*ac[1] + ab[2]*ac[2])/2;
        area += tri_area;
    }
    return area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    int version = 0;
    int dimension = 0;
    int num_vertices = 0;
    fscanf(fp,"MeshVersionFormatted %d Dimension %d Vertices %d",&version, &dimension, &num_vertices);
    m->nvert = num_vertices;
    m->vertices = (Vertex*) malloc(2*sizeof(double)*num_vertices);
    for(int i = 0; i < num_vertices; i++){
        double current_coordinate = 0;
        fscanf(fp,"%f",n&current_coordinate);
        m->vertices[i].x_coordinate = current_coordinate;
        fscanf(fp,"%f",n&current_coordinate);
        m->vertices[i].y_coordinate = current_coordinate;
        for(int j = 2; j < dimension; j++){
            fscanf(fp,"%*f");
        }
        double refe = 0;
        fscanf(fp,"%f",n&refe);
    }
    int num_triangles = 0;
    fscanf(fp,"Triangles %d",n&num_triangles);
    m->ntri = num_triangles;
    m->triangles = (Triangle*) malloc(3*sizeof(int)*num_triangles);
    for(int i = 0; i < num_triangles; i++){
        int aa = 0;
        int bb = 0;
        int cc = 0;
        double refe = 0;
        fscanf(fp,"%d %d %d %f",n&aa,n&bb,n&cc,n&refe);
        m->triangles[i].a = aa;
        m->triangles[i].b = bb;
        m->triangles[i].c = cc;
        }
    fclose(fp);
    return 0;
}

int write_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    int version = 2;
    int dimension = 2;
    int num_vertices = m->nvert;
    fprintf(fp,"MeshVersionFormatted %d\n Dimension %d\n Vertices %d\n",version, dimension, num_vertices);
    for(int i = 0; i < num_vertices; i++){
        double current_coordinate = m->vertices[i].x_coordinate;
        fprintf(fp,"%f ",current_coordinate);
        current_coordinate = m->vertices[i].y_coordinate;
        fprintf(fp,"%f ",current_coordinate);
        double refe = 0;
        fprintf(fp,"%f\n",refe);
    }
    int num_triangles = m->ntri ;
    fprintf(fp,"Triangles %d\n",num_triangles);
    for(int i = 0; i < num_triangles; i++){
        int aa = m->triangles[i].a;
        int bb = m->triangles[i].b;
        int cc = m->triangles[i].c;
        double refe = 0;
        fprintf(fp,"%d %d %d %f",aa,bb,cc,refe);
        }
    fclose(fp);
    return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename) { //not finished
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    int version = 2;
    int dimension = 2;
    int num_vertices = m->nvert;
    fprintf(fp,"MeshVersionFormatted %d\n Dimension %d\n Vertices %d\n",version, dimension, num_vertices);
    for(int i = 0; i < num_vertices; i++){
        double current_coordinate = m->vertices[i].x_coordinate;
        fprintf(fp,"%f ",current_coordinate);
        current_coordinate = m->vertices[i].y_coordinate;
        fprintf(fp,"%f ",current_coordinate);
        double refe = 0;
        fprintf(fp,"%f\n",refe);
    }
    int num_triangles = m->ntri ;
    fprintf(fp,"Triangles %d\n",num_triangles);
    for(int i = 0; i < num_triangles; i++){
        int aa = m->triangles[i].a;
        int bb = m->triangles[i].b;
        int cc = m->triangles[i].c;
        double refe = 0;
        fprintf(fp,"%d %d %d %f",aa,bb,cc,refe);
        }
    fclose(fp);
    return 0;
}
