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
	// Need to creat a string that should store the content of the file
    	char line[256];
    	int reading_vertices = 0, reading_triangles = 0;
	
	int vertex_count = 0;
	int triangle_count = 0;

	while (fgets(line, sizeof(line), file)) {
        	// Remove leading/trailing spaces
		//  strtok() method splits str[] according to given delimiters and returns the next token
        	char *trimmed = strtok(line, "\n");

        	// Start of vertices section
		// Takes two strings s1 and s2 as arguments and finds the first occurrence 
		// of the string s2 in the string s1.
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
			// sscanf() is used for parsing the formatted strings by extracting data from a string.
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

int mesh2D_to_gnuplot(struct Mesh2D* mesh, const char* filename)
{
	// Open the file for writing
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
        	return -1; 
    	}
	

	fprintf(file, "\n# Triangle\n");
    	
    	for (int i = 0; i < mesh->nt; i++) {
        	struct Triangle t = mesh->tri[i];
        
        	struct Vertex v1 = mesh->vert[t.alpha];
        	struct Vertex v2 = mesh->vert[t.beta];
        	struct Vertex v3 = mesh->vert[t.gamma];

		
        	fprintf(file, "%f %f\n", v1.x_cord, v1.y_cord);
        	fprintf(file, "%f %f\n", v2.x_cord, v2.y_cord);

		fprintf(file, "\n");

		fprintf(file, "%f %f\n", v2.x_cord, v2.y_cord);
            	fprintf(file, "%f %f\n", v3.x_cord, v3.y_cord);

        	fprintf(file, "\n");

		fprintf(file, "%f %f\n", v1.x_cord, v1.y_cord);
                fprintf(file, "%f %f\n", v3.x_cord, v3.y_cord);

		fprintf(file, "\n");
    	}

	// Close the file
	fclose(file);
    	return 0;  
}

int write_mesh2D(struct Mesh2D* mesh, const char*filename)
{
        // Open the file for writing
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
                return -1;
        }
	
	fprintf(file, "MeshVersionFormatted 2\n");

	fprintf(file, "Dimension 2\n");


	fprintf(file, "Vertices %d\n", mesh->nv);
    	for (int i = 0; i < mesh->nv; i++) {
        	fprintf(file, "%f %f\n", mesh->vert[i].x_cord, mesh->vert[i].y_cord);
    	}


        fprintf(file, "\n Triangles %d\n", mesh->nt);
        for (int i = 0; i < mesh->nt; i++) {
                struct Triangle t = mesh->tri[i];
		fprintf(file, "%d %d %d\n", t.alpha, t.beta, t.gamma);

        }
	
	fprintf(file, "End");
        // Close the file
        fclose(file);
        return 0;
}
	
int main(){

	// Example: Initialize a Mesh2D with 4 vertices and 2 triangles
	// struct Mesh2D* m = (struct Mesh2D*) malloc(sizeof(struct Mesh2D));
	// m = initialize_mesh2D(4,2);

	// m->vert[0] = (struct Vertex) {0.0, 0.0};
	// m->vert[1] = (struct Vertex) {0.0, 1.0};
	// m->vert[2] = (struct Vertex) {1.0, 1.0};
	// m->vert[3] = (struct Vertex) {1.0, 0.0};
	// m->tri[0] = (struct Triangle) {0, 1, 2};
	// m->tri[1] = (struct Triangle) {3, 0, 2};
	// double area = area_mesh2D(m);
	// printf("area: %f \n", area);
	// dispose_mesh2D(m);


	// Example: Initialize a Mesh2D with 5 vertices and 2 triangles
    	struct Mesh2D* mesh = initialize_mesh2D(5, 2);

    	
    	mesh->vert[0] = (struct Vertex) {0.0, 0.0};
    	mesh->vert[1] = (struct Vertex) {1.0, 0.0};
    	mesh->vert[2] = (struct Vertex) {1.0, 1.0};
    	mesh->vert[3] = (struct Vertex) {0.0, 1.0};
    	mesh->vert[4] = (struct Vertex) {0.5, 0.5};
    	mesh->tri[0] = (struct Triangle) {0, 1, 4}; 
    	mesh->tri[1] = (struct Triangle) {1, 2, 4}; 

    	// Write the mesh data to a file for gnuplot
    	if (write_mesh2D(mesh, "write_m.mesh") == 0) {
        	printf("Data successfully written to write_m.mesh\n");
    	}
	else {
        	printf("Error writing data to file\n");
    	}

    	dispose_mesh2D(mesh);

    	return 0;
}
