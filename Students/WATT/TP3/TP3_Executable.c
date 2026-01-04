#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "Mesh.h"
#include "Tp3_Actual.h"

/*
  If Tp3_Actual.h does NOT declare these, uncomment:

  int *build_adjacency_table1(const struct Mesh *m);
  int *build_adjacency_table2(const struct Mesh *m);
  int *build_adjacency_table3(const struct Mesh *m);
*/

/* ---------- timing helper ---------- */

static long long now_us(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000000LL + (long long)tv.tv_usec;
}

/* ---------- minimal OBJ loader (self-contained) ---------- */
/*
  Supports:
    v x y z
    f i j k
    f i/... j/... k/...
    f polygons -> triangulated as fan (v0,vi,vi+1)
  Handles negative indices (OBJ relative indexing).
  Converts OBJ 1-based indices to 0-based.
*/

static int parse_obj_vertex_index(const char *tok, int nvert_so_far) {
    /* atoi stops at '/' which is exactly what we want for tokens like "12/3/4" */
    int idx = atoi(tok);

    if (idx > 0) {
        /* 1-based -> 0-based */
        return idx - 1;
    }
    if (idx < 0) {
        /* relative to end: -1 is last defined vertex */
        return nvert_so_far + idx; /* idx is negative */
    }
    return -1; /* invalid */
}

static int load_obj(const char *filename, struct Mesh *m) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 0;
    }

    struct Vertex *verts = NULL;
    struct Triangle *tris = NULL;
    int vcap = 0, tcap = 0;
    int nvert = 0, ntri = 0;

    char line[4096];

    while (fgets(line, sizeof(line), fp)) {
        /* skip empty / comment */
        if (line[0] == '\0' || line[0] == '\n' || line[0] == '#') continue;

        /* vertex line: v x y z */
        if (line[0] == 'v' && (line[1] == ' ' || line[1] == '\t')) {
            double x, y, z;
            if (sscanf(line + 1, "%lf %lf %lf", &x, &y, &z) == 3) {
                if (nvert == vcap) {
                    vcap = (vcap == 0) ? 1024 : vcap * 2;
                    struct Vertex *tmp = (struct Vertex *)realloc(
                        verts, (size_t)vcap * sizeof(*verts)
                    );
                    if (!tmp) {
                        fclose(fp);
                        free(verts);
                        free(tris);
                        return 0;
                    }
                    verts = tmp;
                }
                verts[nvert].x = x;
                verts[nvert].y = y;
                verts[nvert].z = z;
                nvert++;
            }
            continue;
        }

        /* face line: f ... */
        if (line[0] == 'f' && (line[1] == ' ' || line[1] == '\t')) {
            /* tokenize */
            char *p = line + 1;
            while (*p == ' ' || *p == '\t') p++;

            /* collect all vertex indices for this face */
            int *face = NULL;
            int fcap = 0, fn = 0;

            char *tok = strtok(p, " \t\r\n");
            while (tok) {
                int vi = parse_obj_vertex_index(tok, nvert);
                if (vi < 0 || vi >= nvert) {
                    /* invalid index */
                    free(face);
                    fclose(fp);
                    free(verts);
                    free(tris);
                    return 0;
                }
                if (fn == fcap) {
                    fcap = (fcap == 0) ? 8 : fcap * 2;
                    int *tmp = (int *)realloc(face, (size_t)fcap * sizeof(*face));
                    if (!tmp) {
                        free(face);
                        fclose(fp);
                        free(verts);
                        free(tris);
                        return 0;
                    }
                    face = tmp;
                }
                face[fn++] = vi;
                tok = strtok(NULL, " \t\r\n");
            }

            if (fn >= 3) {
                /* triangulate fan: (face[0], face[i], face[i+1]) */
                for (int i = 1; i + 1 < fn; i++) {
                    if (ntri == tcap) {
                        tcap = (tcap == 0) ? 1024 : tcap * 2;
                        struct Triangle *tmp = (struct Triangle *)realloc(
                            tris, (size_t)tcap * sizeof(*tris)
                        );
                        if (!tmp) {
                            free(face);
                            fclose(fp);
                            free(verts);
                            free(tris);
                            return 0;
                        }
                        tris = tmp;
                    }
                    tris[ntri].idx[0] = face[0];
                    tris[ntri].idx[1] = face[i];
                    tris[ntri].idx[2] = face[i + 1];
                    ntri++;
                }
            }

            free(face);
            continue;
        }

        /* ignore other OBJ directives (vn, vt, usemtl, etc.) */
    }

    fclose(fp);

    m->nvert = nvert;
    m->ntri = ntri;
    m->vertices = verts;
    m->triangles = tris;

    return 1;
}

/* Count boundary half-edges (optional sanity check so the compiler can't optimize away work) */
static long long count_boundary_halfedges(const int *adj, int ntri) {
    long long b = 0;
    for (int i = 0; i < 3 * ntri; i++) {
        if (adj[i] < 0) b++;
    }
    return b;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s mesh.obj\n", argv[0]);
        return 1;
    }

    const char *meshfile = argv[1];

    struct Mesh m;
    initialize_mesh(&m);

    if (!load_obj(meshfile, &m)) {
        fprintf(stderr, "Error: failed to read OBJ mesh '%s'\n", meshfile);
        dispose_mesh(&m);
        return 1;
    }

    printf("Loaded mesh: nvert=%d, ntri=%d\n", m.nvert, m.ntri);

    /* Required by statement: skip O(ntri^2) method for bugatti.obj */
    int skip_method1 = (strstr(meshfile, "bugatti") != NULL);

    /* ---- Method 1 ---- */
    if (skip_method1) {
        printf("[Method 1] skipped for bugatti mesh (O(ntri^2) too slow)\n");
    } else {
        long long t0 = now_us();
        int *adj1 = build_adjacency_table1(&m);
        long long t1 = now_us();

        if (!adj1) {
            printf("[Method 1] failed (returned NULL)\n");
        } else {
            double ms = (t1 - t0) / 1000.0;
            long long b = count_boundary_halfedges(adj1, m.ntri);
            printf("[Method 1] time = %.3f ms | boundary half-edges = %lld\n", ms, b);
            free(adj1);
        }
    }

    /* ---- Method 2 ---- */
    {
        long long t0 = now_us();
        int *adj2 = build_adjacency_table2(&m);
        long long t1 = now_us();

        if (!adj2) {
            printf("[Method 2] failed (returned NULL)\n");
        } else {
            double ms = (t1 - t0) / 1000.0;
            long long b = count_boundary_halfedges(adj2, m.ntri);
            printf("[Method 2] time = %.3f ms | boundary half-edges = %lld\n", ms, b);
            free(adj2);
        }
    }

    /* ---- Method 3 ---- */
    {
        long long t0 = now_us();
        int *adj3 = build_adjacency_table3(&m);
        long long t1 = now_us();

        if (!adj3) {
            printf("[Method 3] failed (returned NULL)\n");
        } else {
            double ms = (t1 - t0) / 1000.0;
            long long b = count_boundary_halfedges(adj3, m.ntri);
            printf("[Method 3] time = %.3f ms | boundary half-edges = %lld\n", ms, b);
            free(adj3);
        }
    }

    dispose_mesh(&m);
    return 0;
}
