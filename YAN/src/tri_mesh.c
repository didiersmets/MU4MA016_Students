#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include "tri_mesh.h"

int initialize_mesh2D( Mesh2D* m, int vtx_capacity, int tri_capacity){
	m->nv=vtx_capacity;
	m->vert = malloc(vtx_capacity*sizeof(Vertex));
	m->nt=tri_capacity;
	m->tri = malloc(tri_capacity*sizeof(Triangle));
	return 0;
}

void dispose_mesh2D(Mesh2D* m){
	free(m->vert);
	free(m->tri);
	free(m);
}

double area_triangle(Vertex A, Vertex B, Vertex C){
	return ((C.x-A.x)*(B.x-A.x)+(C.y-A.y)*(B.y-A.y))/2;
}
	

double area_mesh2D(struct Mesh2D* m){
	int nt = m->nt;
	double area  = 0;
	for(int i=0;i<nt;i++){
		Vertex A = m->vert[m->tri[i].a];	
		Vertex B = m->vert[m->tri[i].b];
		Vertex C = m->vert[m->tri[i].c];
		double at = area_triangle(A,B,C);
		printf(" at = %f \n", at);
		area += at;
	}
	return area;
}


int initialize_mesh3D( Mesh3D* m, int vtx_capacity, int tri_capacity){
	m->nv=vtx_capacity;
	m->vert = malloc(vtx_capacity*sizeof(Vertex3D));
	m->nt=tri_capacity;
	m->tri = malloc(tri_capacity*sizeof(Triangle));
	return 0;
}

void dispose_mesh3D(Mesh3D* m){
	free(m->vert);
	free(m->tri);
	free(m);
}

double area_triangle3D(Vertex3D A, Vertex3D B, Vertex3D C){
	Vertex3D AB;
	Vertex3D AC;
	AB.x = B.x-A.x;
	AB.y = B.y-A.y;
	AB.z = B.z-A.z;
	AC.x = C.x-A.x;
	AC.y = C.y-A.y;
	AC.z = C.z-A.z;
	Vertex3D ABC;
	ABC.x = AB.y*AC.z-AB.z*AC.y;
	ABC.y = AB.z*AC.x-AB.x*AC.z;
	ABC.z= AB.x*AC.y-AB.y*AC.x;
	return  sqrt(ABC.x**2+ABC.y**2+ABC.z**2)/2;

}
	

double area_mesh3D(struct Mesh3D* m){
	int nt = m->nt;
	double area  = 0;
	for(int i=0;i<nt;i++){
		Vertex3D A = m->vert[m->tri[i].a];	
		Vertex3D B = m->vert[m->tri[i].b];
		Vertex3D C = m->vert[m->tri[i].c];
		double at = area_triangle3D(A,B,C);
		printf(" at = %f \n", at);
		area += at;
	}
	return area;

}



