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

read_mesh2D(struct Mesh2D* m, const char* filename){
	FILE fptr* = fopen(filename, "r");
	char line[100];
	
	size_t nv = 0; 
	while(not(feof(fptr))){
		
		fgets(line,100,fptr);
		if(substr(line == "Vertices){
			sscanf(line, "%d", nv)
		}

		if(nv>0){
			places_filled = sscanf(line, "%f %f", &vert.x, &vert.y);
			if(places_filled<2) printf("error");
			nv--;
		}
		fclose(fptr);
	}
}

int main(){
	

	struct Mesh2D* m = (struct Mesh2D*) malloc(sizeof(struct Mesh2D));
	initialize_mesh2D(m,4,2);
	
	
	double area = area_mesh2D(m);
	dispose_mesh2D(m);
	return 0;
}

