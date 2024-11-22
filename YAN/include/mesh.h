#pragma once

/* The Vertex structure, just a triple of double precision floating point 
 * numbers which correspond to the coordinates of the vertex in a given
 * reference frame.
 */
typedef struct Vertex {
	union {
		struct {
			double x,y,z;
		};
		double coord[3];
	};
}Vertex;

/* The Triangle structure, a triple of integers refering to vertex
 * indices inside a vertex table.
 */
typedef struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
}Triangle;

/* The Mesh structure : it contains the number of vertices, the number
 * of triangles, a pointer to the vertices and a pointer to the triangles. 
 */
typedef struct Mesh {
	int nv;
	int nt;
	Vertex *vert;
	Triangle *tri;
}Mesh;

void initialize_mesh(Mesh *m);
void dispose_mesh(Mesh *m);
