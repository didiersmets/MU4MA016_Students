#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


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
	struct Vertex* vert; // adress of actual vertices
	int nt;  //number of triangles
	struct Triangle* tri; //adress of actual triangles

};


struct Mesh2D* initialize_mesh2D( int vtx_capacity, int tri_capacityt){
	struct Mesh2D* m = malloc(sizeof(struct Mesh2D));
	if (m != NULL){
		m-> nv = vtx_capacity;
		m-> nt = tri_capacityt;
		m-> vert = (struct Vertex*) malloc((m->nv)*sizeof(struct Vertex));
		m -> tri = (struct Triangle*) malloc((m->nt)*sizeof(struct Triangle));	
	}
	return(m);	
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
	double total_area = 0;
	if(m->tri == NULL){
		return 0;
	}
	for (int j = 0; j < (m->nt); j++){
		struct Triangle trian = m->tri[j];
		struct Vertex cor1 = m->vert[(trian.alpha)];
		struct Vertex cor2 = m->vert[(trian.beta)];
		struct Vertex cor3 = m->vert[(trian.gamma)];
		double area = 0.5 * ((cor1.x_cord)*((cor2.y_cord) - (cor3.y_cord)) + (cor2.x_cord)*((cor3.y_cord) - (cor1.y_cord)) + (cor3.x_cord)*((cor1.y_cord) - (cor2.y_cord)));
		total_area += area;
	}

	return total_area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL){
		perror("Error opening file. \n");
		return 1;
	}

    	char line[256];
    	int reading_vertices = 0, reading_triangles = 0;
	
	int vertex_count = 0;
	int triangle_count = 0;

	while (fgets(line, sizeof(line), file)) {
        	// Remove leading/trailing spaces
        	char *trimmed = strtok(line, "\n");

        	// Start of vertices section
        	if (strstr(trimmed, "Vertices")) {
            		reading_vertices = 1;
            		continue;
        	}

        	// Start of triangles section
        	if (strstr(trimmed, "Triangles")) {
            		reading_triangles = 1;
            		reading_vertices = 0;  // Stop reading vertices
            	continue;
        	}

        	// End of the mesh file
        	if (strstr(trimmed, "End")) {
            		break;
        	}

        	// Reading vertices
        	if (reading_vertices && vertex_count < m->nv) {
            		int index;
            		sscanf(trimmed, "%lf %lf %d", &m->vert->x_cord, &m->vert->y_cord, &index); 
            		(vertex_count)++;
        	}

        	// Reading triangles
        	if (reading_triangles && triangle_count < m->nt) {
            		int dummy;
            		sscanf(trimmed, "%d %d %d %d", &m->tri->alpha, &m->tri->beta, &m->tri->gamma, &dummy);
            		(triangle_count)++;
        }
    }

    fclose(file);

}



int main(){

	struct Mesh2D* m = (struct Mesh2D*) malloc(sizeof(struct Mesh2D));
	m = initialize_mesh2D(4,2);

	m->vert[0] = (struct Vertex) {0.0, 0.0};
	m->vert[1] = (struct Vertex) {0.0, 1.0};
	m->vert[2] = (struct Vertex) {1.0, 1.0};
	m->vert[3] = (struct Vertex) {1.0, 0.0};
	m->tri[0] = (struct Triangle) {0, 1, 2};
	m->tri[1] = (struct Triangle) {3, 0, 2};
	double area = area_mesh2D(m);
	printf("area: %f \n", area);
	dispose_mesh2D(m);

	return 0;
}
