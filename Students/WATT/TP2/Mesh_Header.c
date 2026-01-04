#ifndef MESH2D_H
#define MESH2D_H

#include <stddef.h>

/*
 * Vertex of a 2D mesh.
 *
 * The TP only strictly requires x,y coordinates. We also store an integer "ref"
 * because INRIA/MEDIT .mesh files attach a reference/tag to each vertex.
 * Keeping it makes read/write round-trips lossless.
 */
typedef struct Vertex2D {
    double x;
    double y;
    int ref; /* label/tag from the file (boundary/subdomain id, etc.) */
} Vertex2D;

/*
 * Indexed triangle in a 2D mesh.
 *
 * v[0], v[1], v[2] are 0-based indices into Mesh2D::vert.
 * ref is the triangle tag from the file.
 */
typedef struct Triangle {
    int v[3];
    int ref;
} Triangle;

/*
 * Minimal indexed triangular mesh in 2D.
 */
typedef struct Mesh2D {
    int nv;         /* number of vertices */
    Vertex2D* vert; /* vertex array (length nv) */

    int nt;         /* number of triangles */
    Triangle* tri;  /* triangle array (length nt) */
} Mesh2D;

/* Allocate arrays for a mesh of given sizes. Returns 0 on success. */
int initialize_mesh2D(Mesh2D* m, int vtx_capacity, int tri_capacity);

/* Free arrays and reset to a safe empty state. */
void dispose_mesh2D(Mesh2D* m);

/* Signed area of one triangle (a,b,c). */
double signed_area_triangle(Vertex2D a, Vertex2D b, Vertex2D c);

/* Signed area of the full mesh (sum of signed triangle areas). */
double area_mesh2D(const Mesh2D* m);

/*
 * Read an INRIA/MEDIT ASCII .mesh file into Mesh2D.
 * - Supports Dimension 2 or 3 (if Dimension 3, z is read but ignored).
 * - Requires Vertices and Triangles blocks.
 * - Skips Edges/Quadrilaterals/Tetrahedra/Hexaedra if present.
 * Returns 0 on success.
 */
int read_mesh2D(Mesh2D* m, const char* filename);

/*
 * Export mesh edges as polylines for gnuplot.
 * Each triangle is written as a closed polyline: a->b->c->a, then blank line.
 * Plot with: plot 'out.gnuplot' with lines
 * Returns 0 on success.
 */
int mesh2D_to_gnuplot(const Mesh2D* m, const char* filename);

/*
 * Write mesh back to an INRIA/MEDIT ASCII .mesh file.
 * For compatibility with many viewers, we write Dimension 3 and z=0.
 * Returns 0 on success.
 */
int write_mesh2D(const Mesh2D* m, const char* filename);

#endif /* MESH2D_H */
