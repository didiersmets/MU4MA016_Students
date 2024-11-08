#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

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

struct Mesh2D* initialize_mesh2D(){
	struct Mesh2D* m = (struct Mesh2D*) malloc(sizeof(struct Mesh2D));
	return m;
}

void reserve_vertices(struct Mesh2D* m, int vtx_capacity){
	m->nv = vtx_capacity;
	m->vert = (struct Vertex*) malloc((m->nv)*sizeof(struct Vertex));
}

void reserve_triangles(struct Mesh2D* m, int tri_capacity){
	m->nt = tri_capacity;
	m->tri = (struct Triangle*) malloc((m->nt)*sizeof(struct Triangle));
}


void dispose_mesh2D(struct Mesh2D* m){
	free(m->vert);
	free(m->tri); 
	free(m);
}

// Reads (x,y,z) of a 3D mesh as (x,y) into a 2D mesh
struct Mesh2D* read_mesh2D(const char* filename){
	
	struct Mesh2D* m = initialize_mesh2D(); 
	
	FILE *fptr = fopen(filename, "r");
	char line[100];
	
	int nv = 0;
	int nt = 0;
	int i = 0; 
	int j = 0;

	while(!(feof(fptr))){
		
		fgets(line,100,fptr);
		printf("%s", line);
		
		if(1==sscanf(line, "Vertices %d", &nv)){
			printf("nv: %d", nv); 
			reserve_vertices(m,nv);
		}
		if(1==sscanf(line, "Triangles %d", &nt)){
			printf("nt: %d", nt); 
			reserve_triangles(m,nt);
		}
		
		// Read vertices
		if(nv>0){
			struct Vertex vert = (m->vert)[i];
			int places_filled = sscanf(line, "%lf %lf", &(vert.x), &(vert.y));
			if(places_filled<2) printf("vertex error");
			nv--;
			i++;
		}

		
		// Read triangles
		if(nt>0){
			struct Triangle tri = (m->tri)[j];
			int places_filled = sscanf(line, "%d %d %d", &(tri.a), &(tri.b), &(tri.c));
			if(places_filled<3) printf("triangle error");
			nt--;
			j++;
		}
	}
	fclose(fptr);
	return m;
}

void write_mesh2D(const struct Mesh2D* m, const char* filename){ 
	
	FILE *fptr = fopen(filename, "w");

	fprintf(fptr, "MeshVersionFormatted 2\n");
	fprintf(fptr, "Dimension 2\n");
	
	// Write vertices
	fprintf(fptr, "Vertices %d", m->nv);
	for(int i=0; i<m->nv; i++){
		struct Vertex vert = (m->vert)[i];
		fprintf(fptr, "%lf %lf\n", vert.x, vert.y);
	}

	// Write triangles
	fprintf(fptr, "Triangles %d", m->nt);
	for(int i=0; i<m->nt; i++){
		struct Triangle tri = (m->tri)[i];
		fprintf(fptr, "%d %d %d\n", tri.a, tri.b, tri.c);
	}

	fprintf(fptr, "End\n");
}

int main(int agrc, char* argv[]){
	
	// Raed from .mesh file
	char* filename = argv[1];
	struct Mesh2D* m = read_mesh2D(filename);
	printf("m->nv: %d\n", m->nv);
	printf("m->nt: %d\n", m->nt);
	
	// Write back to a different (i.e. copy) .mesh file
	write_mesh2D(m,strcat(filename,"_copy"));
	dispose_mesh2D(m);

	return 0;
}

