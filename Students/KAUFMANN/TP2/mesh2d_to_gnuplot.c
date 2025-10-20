#include <stdio.h>

int mesh2D_to_gnuplot(struct Mesh2D *m, const char *filename) {
    FILE *fp = fopen(filename, "w");

    for (int i = 0; i < m->nt; i++) {
        struct Triangle *t = m->tri + i;

        fprintf(fp, "%f %f\n", m->vert[t->a].x, m->vert[t->a].y);
        fprintf(fp, "%f %f\n", m->vert[t->b].x, m->vert[t->b].y);
        fprintf(fp, "%f %f\n", m->vert[t->c].x, m->vert[t->c].y);

        fprintf(fp, "%f %f\n", m->vert[t->a].x, m->vert[t->a].y);

        fprintf(fp, "\n");
    }

    fclose(fp);
    return 0;
}
