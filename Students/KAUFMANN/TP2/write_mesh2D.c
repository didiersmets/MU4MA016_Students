#include <stdio.h>

void write_mesh2D(struct Mesh2D* m, const char* filename);

    FILE *fp = fopen(filename, "w");

    fprintf(fp, "MeshVersionFormatted 2\n");
    fprintf(fp, "Dimension 2\n");

    fprintf(fp, "Vertices %d\n", m->nv);

    for (int i=0;i<m->nv;i++) {
        fprintf(fp, "%lf %lf\n", m->vert->x, m->vert->y);
    }

    fprintf(fp, "Triangles %d\n", m->nt);

    for (int i=0;i<m->nv;i++) {
        fprintf(fp, "%d %d %d\n", m->tri->a, m->tri->b);
    }
