#include <stdlib.h>
#include <stdio.h>
#include <FILE.h>

struct Vertex{
	union{
		struct{
			double x, y;
		};
		double coord[2];
	};
};

struct Triangle{
	union{
		struct{
			int A, B, C;
		};
		int idx[3];
	};
};

struct Mesh2D{
	int nv; /*number of vertices in the mesh*/
	struct Vertex* vert;/*array of vertices*/
	int nt; /*number of triangles*/
	struct Triangle* tri; /*array of triangles*/
};

int initialise_mesh2D(int vtx_capacity, int tri_capacity)
{
	struct Mesh2D* m = (struct Mesh2D*)malloc(sizeof(Mesh2D));
	m->nv = vtx_capacity;
	m->vert = (struct Vertex*)malloc(vtx_capacity*sizeof(struct Vertex));
	m->nt = tri_capacity;
	m->tri = (struct Triangle*)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

double area_mesh2D(struct Mesh2D* m)
{
	double res = 0;
	for (int i = 0; i < m->nt; i++){
		struct Vertex v1 = m->vert[m->tri[i].A];
		struct Vertex v2 = m->vert[m->tri[i].B];
		struct Vertex v3 = m->vert[m->tri[i].C];
		res += ((v1.x - v2.x) * (v3.y - v2.y) - (v1.y - v2.y) * (v3.x - v1.x))/2;
	}
	return res;
}

int read_mesh2D(struct Mesh2D *m, const char *file)
{
	FILE *fp = fopen(file, "r");
	if (fp == NULL){
		printf("impossible de lire le fichier\n");
		return -1;
	}
	char ligne[100];
	int n;
	while(!feof(fp)){
		fgets(ligne, 100, fp);
		if (sscanf(ligne, "MeshVersionFormatted %d", &n) == 1){
			if (n != 2)
				return -1;
		}
		if (sscanf(ligne,"Vertices %d", &m->nv) == 1){
			m->vert = (struct Vertex*)malloc(m->nv*sizeof(struct Vertex));
			for (int i = 0; i < m->nv; i++){
				fgets(ligne, 100, fp);
				sscanf(ligne, "%lf %lf", &m->vert[i].x, &m->vert[i].y);
			}
		}
		if (sscanf(ligne, "Triangles %d", &m->nt) == 1){
			m->tri = (struct Triangle*)malloc(m->nt*sizeof(struct Vertex));
			for (int i = 0; i < m->nt; i++){
				fgets(ligne, 100,fp);
				sscanf(ligne,"%d %d %d", &m->tri[i].A, &m->tri[i].B, &m->tri[i].C);
			}
		}
	}
	return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename)
{
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
		return -1;
	for (int i = 0; i < m->nt; i++){
		fprintf(fp, "%lf", m->vert[m->tri[i].A - 1].x);
		fprintf(fp, "%lf", m->vert[m->tri[i].A - 1].y);
		fprintf(fp, "\n");
		fprintf(fp, "%lf", m->vert[m->tri[i].B - 1].x);
		fprintf(fp, "%lf", m->vert[m->tri[i].B - 1].y);
		fprintf(fp, "\n");
		fprintf(fp, "%lf", m->vert[m->tri[i].C - 1].x);
		fprintf(fp, "%lf", m->vert[m->tri[i].C - 1].y);
		fprintf(fp, "\n");
		fprintf(fp, "%lf", m->vert[m->tri[i].A - 1].x);
		fprintf(fp, "%lf", m->vert[m->tri[i].A - 1].y);
		fprintf(fp, "\n");
		fprintf(fp, "\n");
		fprintf(fp, "\n");
	}
	return 0;
}
