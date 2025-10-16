 #include <stdio.h>
 #include <stdlib.h>
 
struct Mesh2D m;

 int read_mesh2D(struct Mesh2D* m, const char* filename) {
    FILE *fp = fopen(filename, "r");
    char line[128];
    fgets(line, 128, fp);
    fgets(line, 128, fp);

    int nb_vertices;
    fscanf(fp, "%*s %d", &nb_vertices);
    for (int i=0;i<nb_vertices;i++) {
        struct Vertex *v = m->vert + i;
        fscanf(fp, "%lf %lf", &v->x, &v->y)
    }
    int nb_triangles;
    fscanf(fp, "%*s %d", &nb_triangles);
    for (int i=0;i<nb_triangles;i++) {
        struct Triangle *t = m->tri + i;
        fscanf(fp, "%d %d %d", &t->a, &t->b, &t->c);
    }
return 0;
 }