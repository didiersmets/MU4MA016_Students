#include <stdlib.h>
#include <stddef.h>

//question 1
struct Vertex {
	double x;
	double y;
};


//question 2
struct Triangle {
	int Index[3]; //index of the vertices in an array of vertices
};


//Question 3
struct Mesh2D {
	int nv;   				//number of vertices 
	struct Vertex *vert; 	//array where the vertices are to be found or loaded
	int nt; 				//number of triangles
	struct Triangle *tri;	//array where the triangles are to be found or loaded
};


//Question 4
int initialize_mesh2D(struct Mesh2D *m,int vtx_capacity,int tri_capacity);

void dispose_mesh2D(struct Mesh2D *m);    

double area_mesh2D(struct Mesh2D *m);




//Question 6
struct Vertex_3D {
	double x;
	double y;
	double z;
};


struct Pyramid {
	int *Index_3D; 				//index of the vertices in an array of vertices
};


struct Mesh3D {
	int nv;   					//number of vertices (3D) 
	struct Vertex_3D *vert; 	//array where the vertices are to be found or loaded
	int nt; 					//number of pyramids
	struct Pyramid *tri;		//array where the triangles are to be found or loaded
};