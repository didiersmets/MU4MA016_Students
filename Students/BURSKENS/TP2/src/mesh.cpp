



int initialize mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
    m->ntri = tri_capacity;
    m->nvert = vtx_capacity;
    m->vertices = malloc(2*sizeof(double)*vtx_capacity);
    m->triangles = malloc(3*sizeof(int)*tri_capacity);
    return 0;
}

void dispose mesh2D(struct Mesh2D* m) {
    free(m->triangles);
    free(m->vertices);
}

struct Vector vect(struct Vertex v, struct Vertex w) {
    struct Vector vw;
    vw->x_length = v->x_coordinate - w->x_coordinate;
    vw->y_length = v->y_coordinate - w->y_coordinate;
    return vw;
}

double area mesh2D(struct Mesh2D* m) {
    double area = 0;
    int trinum = m->ntri;
    for(int i = 0; i < trinum; i++) {
        double ab[2] = vect(m->vertices[m->triangles[i]->a],m->vertices[m->triangles[i]->b]);
        double ac[2] = vect(m->vertices[m->triangles[i]->a],m->vertices[m->triangles[i]->c]);
        double tri_area = (ab[1]*ac[1] + ab[2]*ac[2])/2;
        area += tri_area;
    }
    return area;
}

int read mesh2D(struct Mesh2D* m, const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    fscanf("", );
    fclose(fp);
    return 0;
}
