/*
    TP2 – Section 1: Indexed triangular meshes
    ------------------------------------------------------------
    This single C file implements:

    1) struct Vertex           : a 2D point (double precision)
    2) struct Triangle         : an indexed triangle (stores 3 vertex indices)
    3) struct Mesh2D           : stores nv, vert[], nt, tri[]
    4) initialize_mesh2D(...)  : allocates memory to load a given #vertices/#triangles
       dispose_mesh2D(...)     : releases that memory
    5) area_mesh2D(...)        : computes signed area of the mesh

    6) More challenging (3D extension):
       - struct Vertex3D / Triangle3D / Mesh3D
       - volume_mesh3D(...) computes signed enclosed volume for a CLOSED, CONSISTENTLY
         ORIENTED surface mesh, using the divergence theorem hint.

    Notes on "indexed" triangles:
      - Triangles do NOT store vertex coordinates directly.
      - They store integer indices into the mesh's vert[] array.

    Notes on "signed" area / "signed" volume:
      - The sign depends on orientation.
      - For 2D: CCW triangles contribute positive area; CW contributes negative.
      - For 3D: outward-oriented triangles contribute positive volume (typically).

    Build example:
      gcc -Wall -Wextra -O2 -std=c11 mesh_section1.c -o mesh_section1 -lm
*/

#include <stdlib.h>   // malloc, calloc, free
#include <stdio.h>    // fprintf (optional debugging)
#include <math.h>     // fabs (optional)

/* ============================================================
   2D DATA STRUCTURES (Section 1, points 1–3)
   ============================================================ */

/* (1) Vertex: a point in 2D space, using double precision. */
struct Vertex {
    double x;
    double y;
};

/* (2) Triangle: an indexed triangle in the plane.
       The triangle's vertices are stored as indices into an array of Vertex. */
struct Triangle {
    int v[3]; /* v[0], v[1], v[2] are vertex indices */
};

/* (3) Mesh2D: a triangular 2D mesh:
       - nv: number of vertices in the mesh
       - vert: address of an array of Vertex
       - nt: number of triangles in the mesh
       - tri: address of an array of Triangle */
struct Mesh2D {
    int nv;
    struct Vertex *vert;

    int nt;
    struct Triangle *tri;
};

/* ============================================================
   2D HELPERS
   ============================================================ */

/* Compute signed area of ONE triangle given its 3 vertices (2D).
   Formula: area = 0.5 * cross( (b-a), (c-a) )
   where cross((ux,uy),(vx,vy)) = ux*vy - uy*vx
*/
static double triangle_signed_area2D(const struct Vertex *a,
                                     const struct Vertex *b,
                                     const struct Vertex *c)
{
    const double abx = b->x - a->x;
    const double aby = b->y - a->y;
    const double acx = c->x - a->x;
    const double acy = c->y - a->y;

    const double cross = abx * acy - aby * acx;
    return 0.5 * cross;
}

/* ============================================================
   2D FUNCTIONS (Section 1, points 4–5)
   ============================================================ */

/* (4) Initialize a Mesh2D to be able to load a given number of vertices and triangles.
   Prototype requested:
      int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity);

   What this does:
     - Allocates m->vert for vtx_capacity vertices
     - Allocates m->tri  for tri_capacity triangles
     - Stores vtx_capacity in m->nv and tri_capacity in m->nt
       (Later, if you load fewer items, you can update nv/nt accordingly.)

   Return value convention (not specified by the brief, so we choose a standard one):
     - returns 0 on success
     - returns -1 on failure (invalid args or allocation failure)
*/
int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity)
{
    /* Defensive programming: check pointer validity */
    if (m == NULL) {
        return -1;
    }

    /* Negative capacities make no sense. Zero is allowed, but results in empty arrays. */
    if (vtx_capacity < 0 || tri_capacity < 0) {
        m->nv = 0;  m->vert = NULL;
        m->nt = 0;  m->tri  = NULL;
        return -1;
    }

    /* Initialize fields first to a safe state (important for cleanup on partial failure) */
    m->nv = 0;  m->vert = NULL;
    m->nt = 0;  m->tri  = NULL;

    /* Allocate vertices array */
    if (vtx_capacity > 0) {
        m->vert = (struct Vertex*)calloc((size_t)vtx_capacity, sizeof(struct Vertex));
        if (m->vert == NULL) {
            /* Allocation failed */
            return -1;
        }
    }

    /* Allocate triangles array */
    if (tri_capacity > 0) {
        m->tri = (struct Triangle*)calloc((size_t)tri_capacity, sizeof(struct Triangle));
        if (m->tri == NULL) {
            /* Allocation failed: free vertices if they were allocated */
            free(m->vert);
            m->vert = NULL;
            return -1;
        }
    }

    /* Store capacities / intended counts */
    m->nv = vtx_capacity;
    m->nt = tri_capacity;

    return 0;
}

/* (4) Dispose function: releases allocated memory.
   Prototype requested:
      void dispose_mesh2D(struct Mesh2D* m);

   What this does:
     - Frees m->vert and m->tri
     - Sets pointers to NULL and counts to 0 to avoid dangling pointers
*/
void dispose_mesh2D(struct Mesh2D *m)
{
    if (m == NULL) {
        return;
    }

    free(m->vert);
    free(m->tri);

    m->vert = NULL;
    m->tri  = NULL;
    m->nv   = 0;
    m->nt   = 0;
}

/* (5) Compute (signed) area of a mesh.
   Prototype requested:
      double area_mesh2D(struct Mesh2D* m);

   Interpretation consistent with the brief:
     - Sum signed areas of all triangles.
     - A triangle listed CCW contributes positive area, CW negative.
*/
double area_mesh2D(struct Mesh2D *m)
{
    if (m == NULL || m->vert == NULL || m->tri == NULL) {
        return 0.0;
    }

    /* If nv/nt are zero or negative, there's nothing meaningful to compute. */
    if (m->nv <= 0 || m->nt <= 0) {
        return 0.0;
    }

    double area = 0.0;

    for (int t = 0; t < m->nt; ++t) {
        const int i0 = m->tri[t].v[0];
        const int i1 = m->tri[t].v[1];
        const int i2 = m->tri[t].v[2];

        /* Safety: validate indices are in range [0, nv-1].
           If out of range, skip that triangle (or you could treat as error). */
        if (i0 < 0 || i0 >= m->nv || i1 < 0 || i1 >= m->nv || i2 < 0 || i2 >= m->nv) {
            continue;
        }

        const struct Vertex *a = &m->vert[i0];
        const struct Vertex *b = &m->vert[i1];
        const struct Vertex *c = &m->vert[i2];

        area += triangle_signed_area2D(a, b, c);
    }

    return area;
}

/* ============================================================
   3D EXTENSION (Section 1, point 6)
   ============================================================ */

/* (6) Modify data structures to describe a surface mesh in 3D.
   We keep the "indexed triangles" idea, but vertices are now (x,y,z). */

struct Vertex3D {
    double x;
    double y;
    double z;
};

struct Triangle3D {
    int v[3]; /* indices into Vertex3D array */
};

struct Mesh3D {
    int nv;
    struct Vertex3D *vert;

    int nt;
    struct Triangle3D *tri;
};

/* Small 3D vector helper type for geometric computations */
struct Vec3 {
    double x, y, z;
};

static struct Vec3 vec3_sub(const struct Vertex3D *b, const struct Vertex3D *a)
{
    struct Vec3 r;
    r.x = b->x - a->x;
    r.y = b->y - a->y;
    r.z = b->z - a->z;
    return r;
}

static struct Vec3 vec3_cross(struct Vec3 u, struct Vec3 v)
{
    struct Vec3 r;
    r.x = u.y * v.z - u.z * v.y;
    r.y = u.z * v.x - u.x * v.z;
    r.z = u.x * v.y - u.y * v.x;
    return r;
}

static double vec3_dot(struct Vec3 u, struct Vec3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

/* Optional: initialize/dispose for Mesh3D, mirroring the 2D version. */
int initialize_mesh3D(struct Mesh3D *m, int vtx_capacity, int tri_capacity)
{
    if (m == NULL) return -1;
    if (vtx_capacity < 0 || tri_capacity < 0) return -1;

    m->nv = 0; m->vert = NULL;
    m->nt = 0; m->tri  = NULL;

    if (vtx_capacity > 0) {
        m->vert = (struct Vertex3D*)calloc((size_t)vtx_capacity, sizeof(struct Vertex3D));
        if (m->vert == NULL) return -1;
    }
    if (tri_capacity > 0) {
        m->tri = (struct Triangle3D*)calloc((size_t)tri_capacity, sizeof(struct Triangle3D));
        if (m->tri == NULL) {
            free(m->vert);
            m->vert = NULL;
            return -1;
        }
    }

    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    return 0;
}

void dispose_mesh3D(struct Mesh3D *m)
{
    if (m == NULL) return;
    free(m->vert);
    free(m->tri);
    m->vert = NULL;
    m->tri  = NULL;
    m->nv   = 0;
    m->nt   = 0;
}

/* (6) Compute the volume enclosed by a CLOSED surface mesh.

   Using the divergence theorem hint with X(x,y,z) = (x,y,z) and div(X)=3:
       ∫_Ω 3 dV = ∫_{∂Ω} X · n dS
       => 3*Volume = ∫_{∂Ω} X · n dS
       => Volume = (1/3) * ∫_{∂Ω} X · n dS

   For a triangle:
     - area_vector = (1/2) * cross( (b-a), (c-a) )
       This vector has:
         direction = triangle normal (right-hand rule),
         magnitude = triangle area,
         so area_vector = area * unit_normal.
     - barycenter = (a + b + c)/3
     - flux contribution ≈ barycenter · area_vector  (exact for affine fields like X)
   Therefore:
       Volume = (1/3) * Σ_{triangles} ( barycenter · area_vector )

   IMPORTANT ASSUMPTIONS (as stated in the brief):
     - The surface mesh is CLOSED.
     - The orientation is consistent (ideally outward normals).
     - If orientation is reversed, volume will come out negative.

   Return:
     - Signed volume (take fabs(...) if you want magnitude).
*/
double volume_mesh3D(struct Mesh3D *m)
{
    if (m == NULL || m->vert == NULL || m->tri == NULL) {
        return 0.0;
    }
    if (m->nv <= 0 || m->nt <= 0) {
        return 0.0;
    }

    double sum_flux = 0.0;

    for (int t = 0; t < m->nt; ++t) {
        const int i0 = m->tri[t].v[0];
        const int i1 = m->tri[t].v[1];
        const int i2 = m->tri[t].v[2];

        if (i0 < 0 || i0 >= m->nv || i1 < 0 || i1 >= m->nv || i2 < 0 || i2 >= m->nv) {
            continue;
        }

        const struct Vertex3D *a = &m->vert[i0];
        const struct Vertex3D *b = &m->vert[i1];
        const struct Vertex3D *c = &m->vert[i2];

        /* Compute area_vector = 0.5 * cross(b-a, c-a) */
        const struct Vec3 ab = vec3_sub(b, a);
        const struct Vec3 ac = vec3_sub(c, a);
        struct Vec3 area2 = vec3_cross(ab, ac); /* magnitude = 2*area, direction = normal */
        struct Vec3 area_vector;
        area_vector.x = 0.5 * area2.x;
        area_vector.y = 0.5 * area2.y;
        area_vector.z = 0.5 * area2.z;

        /* barycenter = (a + b + c)/3 */
        struct Vec3 bary;
        bary.x = (a->x + b->x + c->x) / 3.0;
        bary.y = (a->y + b->y + c->y) / 3.0;
        bary.z = (a->z + b->z + c->z) / 3.0;

        /* Flux contribution for X(x)=x is barycenter · area_vector */
        sum_flux += vec3_dot(bary, area_vector);
    }

    /* Volume = (1/3) * total_flux */
    return sum_flux / 3.0;
}

/* ============================================================
   End of Section 1 implementation
   ============================================================ */
