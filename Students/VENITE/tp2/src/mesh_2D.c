#include "mesh_2d.h"
#include <stdlib.h>
#include <string.h>

int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity) {
    m->nv = 0;
    m->nt = 0;
    m->vert = (Vertex2D*)malloc(vtx_capacity * sizeof(Vertex2D));
    if (m->vert == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer la mémoire pour les sommets 2D.\n");
        return -1;
    }
    m->nv = vtx_capacity;

    m->tri = (Triangle*)malloc(tri_capacity * sizeof(Triangle));
    if (m->tri == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer la mémoire pour les triangles 2D.\n");
        free(m->vert);
        m->vert = NULL;
        m->nv = 0;
        return -1;
    }
    m->nt = tri_capacity;
    return 0;
}

void dispose_mesh2D(Mesh2D* m) {
    if (m != NULL) {
        if (m->vert != NULL) free(m->vert);
        if (m->tri != NULL) free(m->tri);
        m->vert = NULL;
        m->tri = NULL;
        m->nv = 0;
        m->nt = 0;
    }
}

double area_mesh2D(const Mesh2D* m) {
    double total_area = 0.0;
    for (int i = 0; i < m->nt; ++i) {
        Vertex2D p1 = m->vert[m->tri[i].v1];
        Vertex2D p2 = m->vert[m->tri[i].v2];
        Vertex2D p3 = m->vert[m->tri[i].v3];
        total_area += 0.5 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    }
    return total_area;
}

int read_mesh2D(Mesh2D* m, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier '%s'\n", filename);
        return -1;
    }

    char line[256];
    int vtx_count = 0, tri_count = 0, dimension = 0;

    while (fgets(line, sizeof(line), file)) {
         if (sscanf(line, "Dimension %d", &dimension) == 1) {
            if (dimension != 2) {
                fprintf(stderr, "Erreur: Le fichier '%s' n'est pas un maillage 2D.\n", filename);
                fclose(file);
                return -1;
            }
        } else if (strncmp(line, "Vertices", 8) == 0) {
            if (fgets(line, sizeof(line), file)) sscanf(line, "%d", &vtx_count);
        } else if (strncmp(line, "Triangles", 9) == 0) {
            if (fgets(line, sizeof(line), file)) sscanf(line, "%d", &tri_count);
        }
    }

    if (vtx_count == 0 || tri_count == 0) {
        fprintf(stderr, "Erreur: Fichier de maillage invalide ('%s').\n", filename);
        fclose(file);
        return -1;
    }

    if (initialize_mesh2D(m, vtx_count, tri_count) != 0) {
        fclose(file);
        return -1;
    }
    rewind(file);

    int ref;
    double z_dummy;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Vertices", 8) == 0) {
            fgets(line, sizeof(line), file); // Skip count line
            for (int i = 0; i < vtx_count; ++i) {
                if(fgets(line, sizeof(line), file))
                    sscanf(line, "%lf %lf %lf %d", &m->vert[i].x, &m->vert[i].y, &z_dummy, &ref);
            }
        } else if (strncmp(line, "Triangles", 9) == 0) {
            fgets(line, sizeof(line), file); // Skip count line
            for (int i = 0; i < tri_count; ++i) {
                if(fgets(line, sizeof(line), file)) {
                    sscanf(line, "%d %d %d %d", &m->tri[i].v1, &m->tri[i].v2, &m->tri[i].v3, &ref);
                    m->tri[i].v1--; m->tri[i].v2--; m->tri[i].v3--;
                }
            }
        }
    }

    fclose(file);
    return 0;
}

int write_mesh2D(const Mesh2D* m, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erreur: Impossible de créer le fichier '%s'\n", filename);
        return -1;
    }

    fprintf(file, "MeshVersionFormatted 2\n\n");
    fprintf(file, "Dimension 2\n\n");
    fprintf(file, "Vertices\n%d\n", m->nv);
    for (int i = 0; i < m->nv; ++i) {
        fprintf(file, "%f %f 0\n", m->vert[i].x, m->vert[i].y);
    }
    fprintf(file, "\nTriangles\n%d\n", m->nt);
    for (int i = 0; i < m->nt; ++i) {
        fprintf(file, "%d %d %d 0\n", m->tri[i].v1 + 1, m->tri[i].v2 + 1, m->tri[i].v3 + 1);
    }
    fprintf(file, "\nEnd\n");
    fclose(file);
    return 0;
}

int mesh2D_to_gnuplot(const Mesh2D* m, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erreur: Impossible de créer le fichier gnuplot '%s'\n", filename);
        return -1;
    }
    for (int i = 0; i < m->nt; ++i) {
        Vertex2D p1 = m->vert[m->tri[i].v1];
        Vertex2D p2 = m->vert[m->tri[i].v2];
        Vertex2D p3 = m->vert[m->tri[i].v3];
        fprintf(file, "%f %f\n", p1.x, p1.y);
        fprintf(file, "%f %f\n", p2.x, p2.y);
        fprintf(file, "%f %f\n", p3.x, p3.y);
        fprintf(file, "%f %f\n", p1.x, p1.y);
        fprintf(file, "\n\n");
    }
    fclose(file);
    return 0;
}
