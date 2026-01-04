#include "Mesh_Header.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Internal helper: reset fields to a clean empty state. */
static void mesh2d_reset(Mesh2D* m) {
    if (!m) return;
    m->nv = 0;
    m->vert = NULL;
    m->nt = 0;
    m->tri = NULL;
}

int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity) {
    if (!m || vtx_capacity < 0 || tri_capacity < 0) return 1;

    mesh2d_reset(m);

    if (vtx_capacity > 0) {
        m->vert = (Vertex2D*)calloc((size_t)vtx_capacity, sizeof(Vertex2D));
        if (!m->vert) return 2;
    }

    if (tri_capacity > 0) {
        m->tri = (Triangle*)calloc((size_t)tri_capacity, sizeof(Triangle));
        if (!m->tri) {
            free(m->vert);
            mesh2d_reset(m);
            return 3;
        }
    }

    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    return 0;
}

void dispose_mesh2D(Mesh2D* m) {
    if (!m) return;
    free(m->vert);
    free(m->tri);
    mesh2d_reset(m);
}

double signed_area_triangle(Vertex2D a, Vertex2D b, Vertex2D c) {
    /* Signed area = 0.5 * det(b-a, c-a) */
    const double abx = b.x - a.x;
    const double aby = b.y - a.y;
    const double acx = c.x - a.x;
    const double acy = c.y - a.y;
    return 0.5 * (abx * acy - aby * acx);
}

double area_mesh2D(const Mesh2D* m) {
    if (!m || !m->vert || !m->tri) return 0.0;

    double total = 0.0;
    for (int t = 0; t < m->nt; ++t) {
        const Triangle tri = m->tri[t];
        const Vertex2D a = m->vert[tri.v[0]];
        const Vertex2D b = m->vert[tri.v[1]];
        const Vertex2D c = m->vert[tri.v[2]];
        total += signed_area_triangle(a, b, c);
    }
    return total;
}

/*
 * Read next token (whitespace-delimited), skipping comment lines that start with '#'.
 * Returns 1 if token read, 0 on EOF.
 */
static int next_token(FILE* f, char* buf, size_t buf_sz) {
    (void)buf_sz; /* buf is sized by caller; fscanf hard-caps below. */
    for (;;) {
        int rc = fscanf(f, "%255s", buf);
        if (rc != 1) return 0;

        if (buf[0] == '#') {
            /* Discard rest of the comment line. */
            int ch;
            do { ch = fgetc(f); } while (ch != '\n' && ch != EOF);
            continue;
        }
        return 1;
    }
}

/* Skip a block of n entries, each entry containing k integers. */
static int skip_int_block(FILE* f, int n, int k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            int tmp;
            if (fscanf(f, "%d", &tmp) != 1) return 1;
        }
    }
    return 0;
}

int read_mesh2D(Mesh2D* m, const char* filename) {
    if (!m || !filename) return 1;

    FILE* f = fopen(filename, "r");
    if (!f) return 2;

    /* If m already owns memory, release it first. */
    dispose_mesh2D(m);

    int dimension = 0;
    int nv = -1;
    int nt = -1;

    Vertex2D* verts = NULL;
    Triangle* tris = NULL;

    char tok[256];
    while (next_token(f, tok, sizeof(tok))) {

        if (strcmp(tok, "MeshVersionFormatted") == 0) {
            int version = 0;
            (void)fscanf(f, "%d", &version); /* accept any version */
        }
        else if (strcmp(tok, "Dimension") == 0) {
            if (fscanf(f, "%d", &dimension) != 1) {
                fclose(f);
                return 3;
            }
            if (dimension != 2 && dimension != 3) {
                fclose(f);
                return 4;
            }
        }
        else if (strcmp(tok, "Vertices") == 0) {
            if (fscanf(f, "%d", &nv) != 1 || nv < 0) {
                fclose(f);
                return 5;
            }

            verts = (Vertex2D*)calloc((size_t)nv, sizeof(Vertex2D));
            if (!verts) {
                fclose(f);
                return 6;
            }

            for (int i = 0; i < nv; ++i) {
                double x = 0.0, y = 0.0, z = 0.0;
                int ref = 0;

                if (dimension == 2) {
                    if (fscanf(f, "%lf %lf %d", &x, &y, &ref) != 3) {
                        free(verts);
                        fclose(f);
                        return 7;
                    }
                } else {
                    if (fscanf(f, "%lf %lf %lf %d", &x, &y, &z, &ref) != 4) {
                        free(verts);
                        fclose(f);
                        return 8;
                    }
                    (void)z; /* ignored in 2D view */
                }

                verts[i].x = x;
                verts[i].y = y;
                verts[i].ref = ref;
            }
        }
        else if (strcmp(tok, "Triangles") == 0) {
            if (fscanf(f, "%d", &nt) != 1 || nt < 0) {
                free(verts);
                fclose(f);
                return 9;
            }

            tris = (Triangle*)calloc((size_t)nt, sizeof(Triangle));
            if (!tris) {
                free(verts);
                fclose(f);
                return 10;
            }

            for (int i = 0; i < nt; ++i) {
                int a = 0, b = 0, c = 0, ref = 0;
                if (fscanf(f, "%d %d %d %d", &a, &b, &c, &ref) != 4) {
                    free(tris);
                    free(verts);
                    fclose(f);
                    return 11;
                }

                /* MEDIT .mesh indices are 1-based; convert to 0-based. */
                a--; b--; c--;
                if (a < 0 || b < 0 || c < 0 || (nv >= 0 && (a >= nv || b >= nv || c >= nv))) {
                    free(tris);
                    free(verts);
                    fclose(f);
                    return 12;
                }

                tris[i].v[0] = a;
                tris[i].v[1] = b;
                tris[i].v[2] = c;
                tris[i].ref = ref;
            }
        }
        else if (strcmp(tok, "Edges") == 0) {
            int ne = 0;
            if (fscanf(f, "%d", &ne) != 1 || ne < 0) {
                free(tris); free(verts);
                fclose(f);
                return 13;
            }
            if (skip_int_block(f, ne, 3) != 0) {
                free(tris); free(verts);
                fclose(f);
                return 14;
            }
        }
        else if (strcmp(tok, "Quadrilaterals") == 0) {
            int nq = 0;
            if (fscanf(f, "%d", &nq) != 1 || nq < 0) {
                free(tris); free(verts);
                fclose(f);
                return 15;
            }
            if (skip_int_block(f, nq, 5) != 0) {
                free(tris); free(verts);
                fclose(f);
                return 16;
            }
        }
        else if (strcmp(tok, "Tetrahedra") == 0) {
            int ntet = 0;
            if (fscanf(f, "%d", &ntet) != 1 || ntet < 0) {
                free(tris); free(verts);
                fclose(f);
                return 17;
            }
            if (skip_int_block(f, ntet, 5) != 0) {
                free(tris); free(verts);
                fclose(f);
                return 18;
            }
        }
        else if (strcmp(tok, "Hexaedra") == 0) {
            int nh = 0;
            if (fscanf(f, "%d", &nh) != 1 || nh < 0) {
                free(tris); free(verts);
                fclose(f);
                return 19;
            }
            if (skip_int_block(f, nh, 9) != 0) {
                free(tris); free(verts);
                fclose(f);
                return 20;
            }
        }
        else if (strcmp(tok, "End") == 0) {
            break;
        }
        else {
            /*
             * If your file contains additional blocks not covered above,
             * add cases here. For the TP meshes you provided, Vertices/Triangles/End
             * are sufficient.
             */
        }
    }

    fclose(f);

    if (!verts || !tris || nv < 0 || nt < 0) {
        free(tris);
        free(verts);
        return 21;
    }

    /* Move ownership into m. */
    m->nv = nv;
    m->nt = nt;
    m->vert = verts;
    m->tri = tris;

    return 0;
}

int mesh2D_to_gnuplot(const Mesh2D* m, const char* filename) {
    if (!m || !filename || !m->vert || !m->tri) return 1;

    FILE* f = fopen(filename, "w");
    if (!f) return 2;

    for (int t = 0; t < m->nt; ++t) {
        const Triangle tri = m->tri[t];
        const Vertex2D a = m->vert[tri.v[0]];
        const Vertex2D b = m->vert[tri.v[1]];
        const Vertex2D c = m->vert[tri.v[2]];

        /* Closed polyline: a -> b -> c -> a, separated by a blank line. */
        fprintf(f, "%.17g %.17g\n", a.x, a.y);
        fprintf(f, "%.17g %.17g\n", b.x, b.y);
        fprintf(f, "%.17g %.17g\n", c.x, c.y);
        fprintf(f, "%.17g %.17g\n\n", a.x, a.y);
    }

    fclose(f);
    return 0;
}

int write_mesh2D(const Mesh2D* m, const char* filename) {
    if (!m || !filename || !m->vert || !m->tri) return 1;

    FILE* f = fopen(filename, "w");
    if (!f) return 2;

    /* Header. */
    fprintf(f, "MeshVersionFormatted 2\n");
    fprintf(f, "Dimension 3\n"); /* keep compatible with many mesh viewers */

    /* Vertices block. We write z=0. */
    fprintf(f, "Vertices %d\n", m->nv);
    for (int i = 0; i < m->nv; ++i) {
        const Vertex2D v = m->vert[i];
        const int ref = (v.ref == 0 ? 1 : v.ref);
        fprintf(f, "  %.17g %.17g 0 %d\n", v.x, v.y, ref);
    }

    /* Triangles block (convert back to 1-based indices). */
    fprintf(f, "Triangles %d\n", m->nt);
    for (int t = 0; t < m->nt; ++t) {
        const Triangle tri = m->tri[t];
        const int ref = (tri.ref == 0 ? 1 : tri.ref);
        fprintf(f, "  %d %d %d %d\n",
                tri.v[0] + 1,
                tri.v[1] + 1,
                tri.v[2] + 1,
                ref);
    }

    fprintf(f, "End\n");
    fclose(f);
    return 0;
}
