#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

struct Vertex {
	double x_cord;
	double y_cord;
};

struct Triangle {
	int alpha;
	int beta;
        int gamma;
};

struct Mesh2D {
	int nv;  // number of vertices
	Vertex* vert; // adress of actual vertices
	int nt;  //number of triangles
	Triangle* tri; //adress of actual triangles

};


struct Mesh2D* initializa_mesh2D( int vtx_capacity, int tri_capacityt){
	struct Mesh2D* m = malloc(sizeof(struct Mesh2D));
	if (m != NULL){
		m-> nv = vtx_capacity;
		m-> nt = tri_capacityt;
		m-> vert = (struct Vertex*) malloc((m->nv)*sizeof(struct Vertex));
		m -> tri = (struct Trangle*) malloc((m->nt)*sizeof(struct Triangle));	
	}
	return(m)	
}

void dispose_mesh2D(struct Mesh2D* m)
{
	if (m == NULL){
		return;
	}
	free(m->vert);
	free(m->tri);
	free(m);
}

double area_mesh2D(struct Mesh2D* m)
{
	if(m->tri == NULL){
		return 0;
	}
	for (j = 0; j < (m->nt); j++){
		trian = m->tri[j];
		cor1 = vert[(trian->alpha)];
		cor2 = vert[(trian->beta)];
		cor3 = vert[(trian->gamma)];
	}

	area = 0.5 * abs((cor1->x_cord)*(cor2->y_cord) - (cor1->y_cord)(cor2->x_cord))
	return area;
}

int main(){
	struct Mesh2D* m = initializa_mesh2D(4, 2);
	printf("%f \n", area_mesh2D(m))
}
