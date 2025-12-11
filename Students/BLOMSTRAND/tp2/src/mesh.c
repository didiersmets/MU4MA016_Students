#include "mesh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity)
{
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = NULL;
    m->tri = NULL;

    m->vert = malloc(sizeof(struct Vertex) * vtx_capacity);
    if (m->vert == NULL)
    {
        return 1;
    }

    m->tri = malloc(sizeof(struct Triangle) * tri_capacity);
    if (m->tri == NULL)
    {
        free(m->vert);
        m->vert = NULL;
        return 1;
    }
    return 0;
}

void dispose_mesh2D(struct Mesh2D *m)
{

    if (m->vert != NULL)
    {
        free(m->vert);
    }

    if (m->tri != NULL)
    {
        free(m->tri);
    }

    m->vert = NULL;
    m->tri = NULL;

    m->nv = 0;
    m->nt = 0;
}

double area_mesh2D(struct Mesh2D *m)
{
    double total_area = 0.0;
    for (int i = 0; i < m->nt; i++)
    {
        struct Triangle t = m->tri[i];

        struct Vertex A = m->vert[t.p1];
        struct Vertex B = m->vert[t.p2];
        struct Vertex C = m->vert[t.p3];

        double area = 0.5 * ((B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y));
        total_area += area;
    }
    return total_area;
}

int read_mesh2D(struct Mesh2D *m, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        return 1;
    }

    int nv = -1;
    int nt = -1;
    char word[256];

    // find nv and nt
    while (fscanf(f, "%255s", word) == 1)
    {
        if (strcmp(word, "Vertices") == 0)
        {
            if (fscanf(f, "%d", &nv) != 1)
            {
                fclose(f);
                return 1;
            }
        }
        else if (strcmp(word, "Triangles") == 0)
        {
            if (fscanf(f, "%d", &nt) != 1)
            {
                fclose(f);
                return 1;
            }
            break;
        }
    }

    if (nv <= 0 || nt <= 0)
    {
        fclose(f);
        return 1;
    }

    fclose(f);

    // allocate mesh
    if (initialize_mesh2D(m, nv, nt) != 0)
    {
        dispose_mesh2D(m);
        return 1;
    }

    f = fopen(filename, "r");
    if (f == NULL)
    {
        dispose_mesh2D(m);
        return 1;
    }

    while (fscanf(f, "%255s", word) == 1)
    {
        if (strcmp(word, "Vertices") == 0)
        {
            break;
        }
    }

    int dummy;
    if (fscanf(f, "%d", &dummy) != 1)
    {
        fclose(f);
        dispose_mesh2D(m);
        return 1;
    }

    for (int i = 0; i < m->nv; i++)
    {
        double x, y;
        int ref;
        if (fscanf(f, "%lf %lf %d", &x, &y, &ref) != 3)
        {
            fclose(f);
            dispose_mesh2D(m);
            return 1;
        }
        m->vert[i].x = x;
        m->vert[i].y = y;
    }

    // triangles
    while (fscanf(f, "%255s", word) == 1)
    {
        if (strcmp(word, "Triangles") == 0)
        {
            break;
        }
    }

    if (fscanf(f, "%d", &dummy) != 1)
    {
        fclose(f);
        dispose_mesh2D(m);
        return 1;
    }

    for (int i = 0; i < m->nt; i++)
    {
        int p1, p2, p3, ref;
        if (fscanf(f, "%d %d %d %d", &p1, &p2, &p3, &ref) != 4)
        {
            fclose(f);
            dispose_mesh2D(m);
            return 1;
        }
        m->tri[i].p1 = p1 - 1;
        m->tri[i].p2 = p2 - 1;
        m->tri[i].p3 = p3 - 1;
    }

    fclose(f);
    return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D *m, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        return 1;
    }

    for (int i = 0; i < m->nt; i++)
    {
        struct Triangle t = m->tri[i];

        struct Vertex A = m->vert[t.p1];
        struct Vertex B = m->vert[t.p2];
        struct Vertex C = m->vert[t.p3];

        fprintf(f, "%lf %lf\n", A.x, A.y);
        fprintf(f, "%lf %lf\n", B.x, B.y);
        fprintf(f, "%lf %lf\n", C.x, C.y);
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

int write_mesh2D(struct Mesh2D *m, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        return 1;
    }
    fprintf(f, "MeshVersionFormatted 1\n\n");
    fprintf(f, "Dimension 2\n\n");

    fprintf(f, "Vertices %d\n", m->nv);
    for (int i = 0; i < m->nv; i++)
    {
        struct Vertex v = m->vert[i];
        fprintf(f, "%lf %lf 0\n", v.x, v.y);
    }
    fprintf(f, "\n");

    fprintf(f, "Triangles %d\n", m->nt);
    for (int i = 0; i < m->nt; i++)
    {
        struct Triangle t = m->tri[i];
        int p1 = t.p1 + 1;
        int p2 = t.p2 + 1;
        int p3 = t.p3 + 1;
        fprintf(f, "%d %d %d 0\n", p1, p2, p3);
    }
    fprintf(f, "\nEnd\n");

    fclose(f);
    return 0;
}
