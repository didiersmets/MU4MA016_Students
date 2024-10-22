#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_VERTICES 1000                                                                           #define MAX_TRIANGLES 1000

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

	area = 0.5 * ((cor1->x_cord)*((cor2->y_cord) - (cor3->y_cord + (cor2->x_cord)*((cor3->y_cord) - (cor1->y_cord) + (cor3->x_cord)*((cor1->y_cord) - (cor2->y_cord)))
	return area;
}

int read_mesh2D(struct Mesh2D* m, const char* filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL){
		perror("Error opening file. \n");
		return 1
	}

    	char line[256];
    	int reading_vertices = 0, reading_triangles = 0;
	
	*vertex_count = 0;
    	*triangle_count = 0;

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
        	if (reading_vertices && *vertex_count < MAX_VERTICES) {
            		int index;
            		sscanf(trimmed, "%f %f %d", &m->vert->x_cord, &m->vert->y_cord, &index); 
            		(*vertex_count)++;
        	}

        	// Reading triangles
        	if (reading_triangles && *triangle_count < MAX_TRIANGLES) {
            		Triangle t;
            		int dummy;
            		sscanf(trimmed, "%d %d %d %d", &m->tri->alpha, &m->tri->beta, &m->tri->gamma, &dummy)
            		(*triangle_count)++;
        }
    }

    fclose(file);

}



int main(){
	struct Mesh2D* m = initializa_mesh2D(4, 2);
	printf("%f \n", area_mesh2D(m))
}
