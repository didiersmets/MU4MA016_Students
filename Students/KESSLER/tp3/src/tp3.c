#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "mesh_io.h"
#include "mesh_adjacency.h"

// Return current time in microseconds
long long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

// Compare two adjacency tables
int verify_table(int *table, int *reference, int ntri) {
    for (int i = 0; i < ntri * 3; i++) {
        if (table[i] != reference[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n",
                   i, reference[i], table[i]);
            return 0;
        }
    }
    return 1;
}

// Check if a string ends with a given suffix
int endswith(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <mesh_file.obj>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct Mesh mesh;

    if (read_mesh_from_wavefront_file(&mesh, filename) != 0) {
        printf("Error reading mesh from file %s\n", filename);
        return 1;
    }

    // Use algorithm 2 as the reference result
    int *reference_table = build_adjacency_table2(&mesh);

    // Run algorithm 1
    if (!endswith(filename, "bugatti.obj")) {
        printf("Running algorithm 1...\n");
        long long start = get_time();
        int *table1 = build_adjacency_table1(&mesh);
        long long end = get_time();

        printf("Algorithm 1 took %.6f seconds\n", (end - start) / 1e6);
        int ok1 = verify_table(table1, reference_table, mesh.ntri);
        printf("Algorithm 1 %s\n", ok1 ? "PASSED" : "FAILED");

        free(table1);
    } else {
        printf("Skipping algorithm 1 for bugatti.obj\n");
    }

    // Run algorithm 2
    printf("Running algorithm 2...\n");
    long long start = get_time();
    int *table2 = build_adjacency_table2(&mesh);
    long long end = get_time();

    printf("Algorithm 2 took %.6f seconds\n", (end - start) / 1e6);
    int ok2 = verify_table(table2, reference_table, mesh.ntri);
    printf("Algorithm 2 %s\n", ok2 ? "PASSED" : "FAILED");

    // Run algorithm 3
    printf("Running algorithm 3...\n");
    start = get_time();
    int *table3 = build_adjacency_table3(&mesh);
    end = get_time();

    printf("Algorithm 3 took %.6f seconds\n", (end - start) / 1e6);
    int ok3 = verify_table(table3, reference_table, mesh.ntri);
    printf("Algorithm 3 %s\n", ok3 ? "PASSED" : "FAILED");

    free(table3);

    free(reference_table);
    dispose_mesh(&mesh);

    return 0;
}
