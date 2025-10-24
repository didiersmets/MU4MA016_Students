#include "../include/mesh_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Mesh* mesh_read(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier '%s'\n", filename);
        return NULL;
    }

    // Allocation de la structure Mesh principale
    Mesh* m = (Mesh*)malloc(sizeof(Mesh));
    if (!m) {
        fclose(file);
        return NULL;
    }
    m->n_vertices = 0;
    m->n_triangles = 0;
    m->vertices = NULL;
    m->triangles = NULL;

    char line[256];
    int v_count = 0, t_count = 0;

    // Premier passage pour compter les sommets et les triangles
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Vertices", 8) == 0) {
            if (fgets(line, sizeof(line), file)) sscanf(line, "%d", &v_count);
        } else if (strncmp(line, "Triangles", 9) == 0) {
            if (fgets(line, sizeof(line), file)) sscanf(line, "%d", &t_count);
        }
    }

    if (v_count == 0 || t_count == 0) {
        fprintf(stderr, "Erreur: Fichier de maillage invalide ou vide ('%s').\n", filename);
        fclose(file);
        free(m);
        return NULL;
    }

    // Allocation des tableaux
    m->n_vertices = v_count;
    m->n_triangles = t_count;
    m->vertices = (Vertex*)malloc(v_count * sizeof(Vertex));
    m->triangles = (Triangle*)malloc(t_count * sizeof(Triangle));

    if (!m->vertices || !m->triangles) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les données du maillage.\n");
        mesh_dispose(m);
        fclose(file);
        return NULL;
    }

    // Second passage pour lire les données
    rewind(file);
    int ref_dummy;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Vertices", 8) == 0) {
            fgets(line, sizeof(line), file); // Skip count line
            for (int i = 0; i < v_count; ++i) {
                if(fgets(line, sizeof(line), file))
                    sscanf(line, "%lf %lf %lf %d", &m->vertices[i].x, &m->vertices[i].y, &m->vertices[i].z, &ref_dummy);
            }
        } else if (strncmp(line, "Triangles", 9) == 0) {
            fgets(line, sizeof(line), file); // Skip count line
            for (int i = 0; i < t_count; ++i) {
                if(fgets(line, sizeof(line), file)) {
                    sscanf(line, "%d %d %d %d", &m->triangles[i].v[0], &m->triangles[i].v[1], &m->triangles[i].v[2], &ref_dummy);
                    // Conversion des indices 1-based en 0-based
                    m->triangles[i].v[0]--;
                    m->triangles[i].v[1]--;
                    m->triangles[i].v[2]--;
                }
            }
        }
    }

    fclose(file);
    return m;
}

void mesh_dispose(Mesh* m) {
    if (m) {
        if (m->vertices) free(m->vertices);
        if (m->triangles) free(m->triangles);
        free(m);
    }
}
