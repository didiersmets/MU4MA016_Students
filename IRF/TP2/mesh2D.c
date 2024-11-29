#include <stdio.h>
#include <stdlib.h>

struct Vertex { 
	union {
		struct{
			double x,y,z;
		};
		double coord[3];
	};
};

struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
};

struct Mesh2D {
	int nvert; // numero de vectores en el mallado
	int ntri;  // numero triangulos en el mallado
	struct Vertex *vert; // matriz de vertices
	struct Triangle *tri; // matriz de triangulos
};


int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity)
{
	m->nvert = vtx_capacity;
	m->ntri = tri_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->tri = (struct Triangle*)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

struct Vertex vector(struct Vertex A, struct Vertex B) 
{
	struct Vertex AB;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;
        AB.z = B.z - A.z;
	return AB;
}

double area_mesh2D(struct Mesh2D* m)
{
	double total = 0;
	for (int i = 0; i < m->ntri; i++){
		struct Vertex AB = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[1]]);
		struct Vertex AC = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[2]]);
		total += ((AB.x * AC.y) - (AB.y * AC.x));
	}
	return total*0.5;
}

struct Vertex prodvector(struct Vertex AB, struct Vertex AC)
{
	struct Vertex ABC;
	ABC.x = (AB.y * AC.z) - (AB.z * AC.y);
	ABC.y = (AB.x * AC.z) - (AB.z * AC.x);
	ABC.x = (AB.x * AC.y) - (AB.y * AC.x);
	return ABC;
}

double area_mesh3D(struct Mesh2D* m)
{
	double total = 0;
	for (int i = 0; i < m->ntri; i++){
		struct Vertex AB = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[1]]);
		struct Vertex AC = vector(m->vert[m->tri[i].idx[0]], m->vert[m->tri[i].idx[2]]);
		struct Vertex ABC = prodvector(AB, AC); 
		total += sqrt((ABC.x)^2 + (ABC.y)^2 + (ABC.z)^2);
	}
	return total*0.5;
}


int read_mesh2D(struct Mesh2D* m, const char* filename)
{
	FILE *file = fopen("filename", "r");
	char line[100];
	if (file != NULL){
		while(fgets(line, 100, file) != NULL){
			if (sscanf(line, "Vertices %d", &m->nvert) == 1){
				m->vert = (struct Vertex *)malloc(m->nvert*sizeof(struct Vertex));
				for (int i = 0; i<m->nvert; i++){
					fgets(line, 100, file);
					sscanf(line, "%lf %lf", &m->vert[i].coord[0], &m->vert[i].coord[1]);
				}
			}
	        	if (sscanf(line, "Triangle %d", &m->ntri) == 1){
				m->tri = (struct Triangle *)malloc(m->ntri*sizeof(struct Triangle));
				for (int i = 0; i<m->ntri; i++){
					fgets(line, 100, file);
					sscanf(line, "%d %d %d", &m->tri[i].idx[1], &m->tri[i].idx[2], &m->tri[i].idx[3]);
				}
			}
		}
	}
	return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename)
{
	FILE *file = fopen("filename", "w");
	if (file != NULL){
		for (int i = 0; i<m->ntri; i++){
			fprintf(file, "%lf", m->vert[(m->tri[i].v1)].x);
			fprintf(file, "%lf", m->vert[(m->tri[i].v1)].y);
			fprintf(file, "\n");
			fprintf(file, "%lf", m->vert[(m->tri[i].v2)].x);
			fprintf(file, "%lf", m->vert[(m->tri[i].v2)].y);
			fprintf(file, "\n");
			fprintf(file, "%lf", m->vert[(m->tri[i].v3)].x);
			fprintf(file, "%lf", m->vert[(m->tri[i].v3)].y);
			fprintf(file, "\n");	
			fprintf(file, "%lf", m->vert[(m->tri[i].v1)].x);	
			fprintf(file, "%lf", m->vert[(m->tri[i].v1)].y);
			fprintf(file, "\n");	
			fprintf(file, "\n");	
			fprintf(file, "\n");	
		}
	}
	fclose(file);
	return 0;
}





int write_mesh2D(struct Mesh2D* m, const char* filename)
{
	FILE *file = fopen("filename", "w");
	fprintf(file, "MeshVersionFormatted 2\n");
	fprintf(file, "Dimension 2\n");
	fprintf(file, "Vertices %d", m->nvert);
	for (int i = 0; i < m->nvert; i++){
		struct Vertex vert = (m->vert)[i];
		fprintf(file, "%lf %lf\n", vert.x, vert.y);
	}
	fprintf(file, "Triangle %d", m->ntri);
	for (int i = 0; i < m->ntri; i++){
		struct Triangle tri = (m->tri)[i];
		fprintf(file, "%d %d %d\n", tri.v1, tri.v2, tri.v3);
	}
	fprintf(file, "End");
}


//int main(int argc, char* argv[])
//{
//	char* filename = argv[1];
//	struct Mesh2D* m = read_mesh2D(m,filename);
//	printf("m->nvert: %d\n", m->nvert);
//	printf("m->ntri: %d\n", m->ntri);
//	write_mesh2D(m, strcat(filename, "_copy"));
//	dispose_mesh2D(m);
//	return 0;
//}




