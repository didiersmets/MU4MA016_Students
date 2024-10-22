#include <stdlib.h>
#include <math.h>
#include <stdio.h>

struct Vertex{
	double x;
	double y;
};

struct Triangle{
	int a;
	int b;
	int c;
};

struct Mesh2D{
	int nv; // number of vertices in the mesh
	int nt; // number of triangles in the mesh
	struct Vertex* vert;
	struct Triangle* tri;
};

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity){
	m->nv = vtx_capacity;
	m->nt = tri_capacity;
	m->vert = (struct Vertex*) malloc((m->nv)*sizeof(struct Vertex));
	m->tri = (struct Triangle*) malloc((m->nt)*sizeof(struct Triangle));
	return 0;
}


void dispose_mesh2D(struct Mesh2D* m){
	free(m->vert);
	free(m->tri); 
	free(m);
}

// by determinant
double signed_area_triangle(double xa, double ya, double xb, double yb, double xc, double yc){
	return 0.5 * ((xb-xa)*(yc-ya)-(yb-ya)*(xc-xa));
}

double area_mesh2D(struct Mesh2D* m){
	
	double A_total = 0;
	
	// calculate the area of each triangle and sum them up
	for(int t_idx=0; t_idx < m->nt; t_idx++){
		
		struct Triangle t = m->tri[t_idx];
		double xa = ((m->vert)[t.a]).x;
		double ya = ((m->vert)[t.a]).y;
		double xb = ((m->vert)[t.b]).x;
		double yb = ((m->vert)[t.b]).y;
		double xc = ((m->vert)[t.c]).x;
		double yc = ((m->vert)[t.c]).y;
		
		double A = signed_area_triangle(xa,ya,xb,yb,xc,yc);

		A_total += A;
	}

	return A_total;
}

int main(){
	

	struct Mesh2D* m = (struct Mesh2D*) malloc(sizeof(struct Mesh2D));
	initialize_mesh2D(m,4,2);
	
	m->vert[0] = {0.0, 0.0};
	m->vert[1] = {0.0, 1.0};
	m->vert[2] = {1.0, 1.0};
	m->vert[3] = {1.0, 0.0};
	m->tri[0] = {0,1,2};
	m->tri[1] = {3,0,2};
	
	double area = area_mesh2D(m);
	printf("area: %f\n", area);
	dispose_mesh2D(m);
	return 0;
}

