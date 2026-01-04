#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mesh.h"
#include "mesh_io.h"
#include "mesh_adjacency.h"

/* --------- timing --------- */
static double now_seconds(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + 1e-9 * (double)ts.tv_nsec;
}

/* --------- helpers --------- */
static const char *basename_c(const char *path)
{
    const char *p = strrchr(path, '/');
    return p ? (p + 1) : path;
}

static int is_bugatti_obj(const char *path)
{
    return strcmp(basename_c(path), "bugatti.obj") == 0;
}

static int has_ext(const char *filename, const char *ext)
{
    size_t n = strlen(filename);
    size_t e = strlen(ext);
    if (n < e) return 0;
    return strcmp(filename + (n - e), ext) == 0;
}

/* Reads mesh based on extension: .obj or .mesh */
static int load_mesh(struct Mesh *m, const char *filename)
{
    initialize_mesh(m);

    if (has_ext(filename, ".obj")) {
        return read_mesh_from_wavefront_file(m, filename);
    }
    if (has_ext(filename, ".mesh")) {
        return read_mesh_from_medit_file(m, filename);
    }

    fprintf(stderr, "Unsupported file extension (expected .obj or .mesh): %s\n", filename);
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mesh.obj|mesh.mesh>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];

    struct Mesh m;
    int rc = load_mesh(&m, filename);
    if (rc != 0) {
        fprintf(stderr, "Error: could not read mesh file '%s'\n", filename);
        dispose_mesh(&m);
        return 1;
    }

    printf("Loaded mesh: nvert=%d, ntri=%d\n", m.nvert, m.ntri);

    /* ---- Method 1 (naive O(ntri^2)) ---- */
    if (!is_bugatti_obj(filename)) {
        double t0 = now_seconds();
        int *adj1 = build_adjacency_table1(&m);
        double t1 = now_seconds();

        if (!adj1) {
            fprintf(stderr, "Error: build_adjacency_table1 failed\n");
            dispose_mesh(&m);
            return 1;
        }

        printf("Method 1 (naive)      : %.6f s\n", (t1 - t0));
        free(adj1);
    } else {
        printf("Method 1 (naive)      : skipped for bugatti.obj\n");
    }

    /* ---- Method 2 (generic hash table) ---- */
    {
        double t0 = now_seconds();
        int *adj2 = build_adjacency_table2(&m);
        double t1 = now_seconds();

        if (!adj2) {
            fprintf(stderr, "Error: build_adjacency_table2 failed\n");
            dispose_mesh(&m);
            return 1;
        }

        printf("Method 2 (hash table) : %.6f s\n", (t1 - t0));
        free(adj2);
    }

    /* ---- Method 3 (ad-hoc edge table) ---- */
    {
        double t0 = now_seconds();
        int *adj3 = build_adjacency_table3(&m);
        double t1 = now_seconds();

        if (!adj3) {
            fprintf(stderr, "Error: build_adjacency_table3 failed\n");
            dispose_mesh(&m);
            return 1;
        }

        printf("Method 3 (ad-hoc)     : %.6f s\n", (t1 - t0));
        free(adj3);
    }

    dispose_mesh(&m);
    return 0;
}
