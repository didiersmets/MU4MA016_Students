#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Pour mesurer le temps

#include "../include/mesh_utils.h"
#include "../include/adjacency.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier.mesh>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    printf("Chargement du maillage: %s\n", filename);

    Mesh* mesh = mesh_read(filename);
    if (!mesh) {
        return 1;
    }
    printf("-> Maillage chargé: %d sommets, %d triangles.\n\n", mesh->n_vertices, mesh->n_triangles);

    clock_t start, end;
    double cpu_time_used;
    int* adj_table = NULL;

    // --- Méthode 1: Naïve O(n^2) ---
    // On ne l'exécute que pour les "petits" maillages pour ne pas attendre trop longtemps
    if (mesh->n_triangles < 10000) {
        printf("--- Test de la Méthode 1 (Naïve O(n^2)) ---\n");
        start = clock();
        adj_table = build_adjacency_table1(mesh);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Temps d'exécution: %f secondes\n", cpu_time_used);
        free(adj_table); // On libère la mémoire après chaque test
    } else {
        printf("--- Méthode 1 (Naïve O(n^2)) sautée (maillage trop grand) ---\n");
    }
    printf("\n");

    // --- Méthode 2: Table de hachage générique ---
    printf("--- Test de la Méthode 2 (Table de hachage générique) ---\n");
    start = clock();
    adj_table = build_adjacency_table2(mesh);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution: %f secondes\n", cpu_time_used);
    free(adj_table);
    printf("\n");

    // --- Méthode 3: Table de hachage ad-hoc ---
    printf("--- Test de la Méthode 3 (Table de hachage ad-hoc) ---\n");
    start = clock();
    adj_table = build_adjacency_table3(mesh);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Temps d'exécution: %f secondes\n", cpu_time_used);
    free(adj_table);
    printf("\n");

    // Libération du maillage
    mesh_dispose(mesh);
    printf("Mémoire du maillage libérée. Programme terminé.\n");

    return 0;
}
