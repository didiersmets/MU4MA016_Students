// gcc -o tp3 src/tp3.c src/mesh_io.c src/mesh_adjacency.c src/hash_tables.c src/mesh.c -Iinclude -std=c11

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "mesh_io.h"
#include "mesh_adjacency.h"



int* (*algorithms[])(const struct Mesh *m) = {
    build_adjacency_table1,
    build_adjacency_table2,
    build_adjacency_table3
};

long long get_time() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

int verify_table(int* table, int* actual, int ntri) {
    for (int i = 0; i < ntri * 3; i++) {
        if (table[i] != actual[i]) {
            printf("Mismatch at index %d: expected %d, got %d\n", i, actual[i], table[i]);
            //for bugatti.obj,
            // "36362 36361" occurs twice, causing Mismatch at index 206818: expected 73504, got 87800
            return 0;
        }
    }
    return 1;
}

int endswith(const char* str, const char* suffix) {
    if (!str || !suffix) {
        return 0;
    }
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr) {
        return 0;
    }
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, char* args[]) {
    if (argc != 2) {
        printf("Expected 1 argument (filename of the mesh in .obj format)\n");
        return 1;
    }

    char* arg = args[1];
    struct Mesh mesh;
    if (read_mesh_from_wavefront_file(&mesh, arg) != 0) {
        printf("Error reading mesh from file %s\n", arg);
        return 1;
    }

    
    int* actual_table = algorithms[1](&mesh);

    for (int i = 0; i < 3; i++) {
        if(i == 0 && endswith(arg, "bugatti.obj")) {
            continue; // skip the actual algorithm
        }
        printf("Running algorithm %d...\n", i + 1);
        long long start = get_time();
        int* table = algorithms[i](&mesh);
        long long end = get_time();
        printf("Algorithm %d took %f seconds\n", i + 1, (end - start) / 1e6);
        int correct = verify_table(table, actual_table, mesh.ntri);
        free(table);
    }

    dispose_mesh(&mesh);

    return 0;
}