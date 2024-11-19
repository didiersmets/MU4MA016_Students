#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include "Structure.h"


//Question 4
int initialize_mesh2D(struct Mesh2D *m, int vtx_capacity, int tri_capacity){

	struct Triangle *Tri_array = malloc(tri_capacity *3* sizeof(struct Triangle));
	struct Vertex *Vert_array = malloc(vtx_capacity * sizeof(struct Vertex));
	m->nv = 0;
	m->vert = Vert_array;
	m->nt = 0;
	m->tri = Tri_array;
	return 0;
};



void dispose_mesh2D(struct Mesh2D *m){
	free(m);
};



//Question 5
static double euclidian_norm(struct Vertex *a, struct Vertex *b){
	double l = sqrt((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
	return l;
};



static int *sort_index(struct Triangle *T, struct Vertex *v){
	int *ind = T->Index;
	int *final_ind;

	int i = (v[ind[0]].x <= v[ind[1]].x)?0:1;
	i = (v[ind[i]].x <= v[ind[2]].x)?i:2;

	int j,k = (v[ind[(i+1)%3]].x <= v[ind[(i+2)%3]].x)? ((i+1)%3,(i+2)%3) : ((i+2)%3,(i+1)%3);

	final_ind[0] = i;
	final_ind[1] = j;
	final_ind[2] = k;

	if (v[ind[i]].x == v[ind[j]].x || v[ind[i]].y > v[ind[j]].y){
		final_ind[0] = j;
		final_ind[1] = i;
	}

	if (v[final_ind[1]].x == v[ind[k]].x || v[ind[k]].y > v[final_ind[1]].y){
		int copy = final_ind[1];
		final_ind[1] = final_ind[2];
		final_ind[2] = copy;
	}

	return final_ind;
};




static double area_triangle(struct Triangle *T, struct Vertex *v){
	double area = 0;

	int *ind = sort_index(T,v);

	struct Vertex A = v[ind[0]];
	struct Vertex B = v[ind[1]];
	struct Vertex C = v[ind[2]];

	double x_min,x_max = (A.x,C.x);

	double y_min = (A.y <= B.y)?A.y:B.y;
	y_min = (C.y <= y_min)?C.y:y_min;

	double y_max = (A.y <= B.y)?B.y:A.y;
	y_max = (C.y <= y_max)?y_max:C.y;


//when the triangle is rectangle
	if ((A.x == B.x && (A.y == C.y || B.y == C.y)) || (C.x == B.x && (C.y == A.y || B.y == A.y))){ // || (A.x == C.x && (A.y == B.y || B.y == C.y))) impossible cases
		if ((A.x == B.x && C.x == B.x) || (A.y == B.y && C.y == B.y)){
			return 0;
		}

		else if (y_min >= 0 || y_max <=0){
			double sign = y_min/abs(y_min);
			double *length;
			length[0] = euclidian_norm(&A,&B);
			length[1] = euclidian_norm(&C,&B);
			length[2] = euclidian_norm(&A,&C);

			int m = (length[0]<=length[1])?1:0;
			m = (length[m]<=length[2])?2:m;

			return sign*(length[(m+1)%3]*length[(m+2)%3]/2); 

		}

		else if (A.x == B.x && A.y == C.y){
			double AC = euclidian_norm(&A,&C);
			double AB = euclidian_norm(&A,&B);
			area -= AC*AB/2;

			double AB_bis = AC*abs(B.y)/AB;
			area += abs(B.y)*AB_bis/2;

		}

		else if (C.x == B.x && A.y == C.y){
			double AC = euclidian_norm(&A,&C);
			double BC = euclidian_norm(&C,&B);
			area -= AC*BC/2;

			double AC_bis = AC*abs(B.y)/BC;
			area += abs(B.y)*AC_bis/2;

		}

		else if (A.x == B.x && B.y == C.y){
			double AB = euclidian_norm(&A,&B);
			double BC = euclidian_norm(&B,&C);
			area += BC*AB/2;

			double BC_bis = BC*abs(A.y)/AB;
			area -= abs(A.y)*BC_bis/2;

		}

		else if (C.x == B.x && B.y == A.y){
			double AB = euclidian_norm(&A,&B);
			double BC = euclidian_norm(&B,&C);
			area += BC*AB/2;

			double AB_bis = AB*abs(C.y)/BC;
			area -= abs(C.y)*AB_bis/2;

		}

		return area;

	}


//when the rectangle is not triangle
	else{
		struct Vertex X = {x_min,y_max};
		struct Vertex Y = {x_max,y_max};
		struct Vertex Z = {x_max,y_min};

		double XY = euclidian_norm(&X,&Y);
		area += (y_max + y_min)*XY; 

		struct Vertex *new_v;
		new_v[0] = A;
		new_v[1] = X;
		new_v[2] = B;
		new_v[3] = Y;
		new_v[4] = C;
		new_v[5] = Z;

		int index_T1[3] = {0, 1, 2};
		struct Triangle T1 = {*index_T1};

		
		int index_T2[3];

		if (Z.x==C.x && Z.y==C.y){
			index_T2[0] = 2;
			index_T2[1] = 3;
			index_T2[2] = 4; 
		}

		else{
			index_T2[0] = 0;
			index_T2[1] = 4;
			index_T2[2] = 5; 
		}

		struct Triangle T2 = {*index_T2};
		area -= area_triangle(&T1, new_v) + area_triangle(&T2, new_v);

		//free(T1);
		//free(T2);
		return area;
	}

};




double area_mesh2D(struct Mesh2D *m){

	double area = 0;

	for (int i = 0; i<(m->nt); i++){

		struct Triangle T = (m->tri)[i];
		area += area_triangle(&T, m->vert);

	}

	return area;
};



//Question 6
static struct Vertex new_vertex(struct Vertex_3D M, struct Vertex_3D N){
	double sign = (N.x - M.x)/abs(N.x - M.x);

	double l = sqrt((M.x - M.x)*(M.x - N.x) + (M.y - N.y)*(M.y - N.y));
	struct Vertex new_N ={M.x + sign*l, N.z};
	return new_N;
}


static double area_pyramid(struct Pyramid *P, struct Vertex_3D *v){
	double area = 0;

	int *ind = P->Index_3D;

	struct Vertex_3D A = v[ind[0]];
	struct Vertex_3D B = v[ind[1]];
	struct Vertex_3D C = v[ind[2]];
	struct Vertex_3D D = v[ind[3]];

	struct Vertex *v_2D;
	v_2D[0] = new_vertex(A,A);
	v_2D[1] = new_vertex(A,B);
	v_2D[2] = new_vertex(A,C);
	v_2D[3] = new_vertex(A,D);

	int ind_1[3] = {0,1,2};
	struct Triangle T_ABC = {*ind_1};
	double surface_ABC = area_triangle(&T_ABC, v_2D);

	int ind_2[3] = {0,1,3};
	struct Triangle T_ABD = {*ind_2};
	double surface_ABD = area_triangle(&T_ABD, v_2D);

	int ind_3[3] = {0,3,2};
	struct Triangle T_ACD = {*ind_3};
	double surface_ACD = area_triangle(&T_ACD, v_2D);

	int ind_4[3] = {1,2,3};
	struct Triangle T_BCD = {*ind_4};
	double surface_BCD = area_triangle(&T_BCD, v_2D);

	area = surface_ABC + surface_ABD + surface_ACD + surface_BCD;

	if (surface_ABC*2 == area || surface_ABD*2 == area || surface_ACD*2 == area || surface_BCD*2 == area){
		area = area/2;
	}

	return area;
}




double area_mesh3D(struct Mesh3D *m){
	double area = 0;

	for (int i = 0; i<(m->nt); i++){

		struct Pyramid P = (m->tri)[i];
		area += area_pyramid(&P, m->vert);
	}

	return area;
}