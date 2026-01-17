#include <stdio.h>
#include <stdlib.h>

#include "/users/home/28624202/MU4MA016_Students/ADrieux/TP2/mesh2D.h"

int initialize_mesh2D(struct Mesh2D* m, int vtx_capacity, int tri_capacity)
{
	m->nv = vtx_capacity;
	m->nt = tri_capacity;
	m->vert = (struct Vertex *)malloc(vtx_capacity*sizeof(struct Vertex));
	m->tri = (struct Triangle *)malloc(tri_capacity*sizeof(struct Triangle));
	return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
	free(m->vert);
	free(m->tri);
}

double area_triangle(struct Mesh2D* m, struct Triangle* tri, struct Vertex* vert, int i)
{
	struct Vertex A = m->vert[(m->tri[i].idx[0])];
	struct Vertex B = m->vert[(m->tri[i].idx[1])];
	struct Vertex C = m->vert[(m->tri[i].idx[2])];
	double area = (0.5)*abs((B.x - A.x)*(C.y - A.y) - (C.x - A.x)*(B.y - A.y));
	return(area);
}

double area_mesh2D(struct Mesh2D* m)
{
	double area = 0;
	for (int i = 0; i< m->nt; i++)
	{
		area += area_triangle(m, m->tri, m->vert, i);
	}
	return(area);
}

#define TAILLE_MAX 100
int read_mesh2D(struct Mesh2D* m, const char* filename)
{
	FILE *fichier = fopen("filename", "r");
	char line[TAILLE_MAX];
	if (fichier != NULL)
	{
		while(fgets(line, TAILLE_MAX, fichier) != NULL)
		{
			if (sscanf(line, "Vertices %d", &m->nv) == 1)
			{
				m->vert = (struct Vertex *)malloc(m->nv*sizeof(struct Vertex));
				for (int i=0; i<m->nv; i++)
				{
					fgets(line, TAILLE_MAX, fichier);
					sscanf(line, "%lf %lf", &m->vert[i].coord[0], &m->vert[i].coord[1]);
				}
			}
			if (sscanf(line, "Triangles %d", &m->nt) == 1)
			{ 
				m->tri = (struct Triangle *)malloc(m->nt*sizeof(struct Triangle));
				for (int i=0; i<m->nt; i++)
				{
					fgets(line, TAILLE_MAX, fichier);
					sscanf(line, "%d %d %d", &m->tri[i].idx[0], &m->tri[i].idx[1], &m->tri[i].idx[2]);
				}
			}
		}
	}
	fclose(fichier);
	return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename)
{
	FILE *fichier = fopen("filename", "w");
	if (fichier != NULL)
	{
		for (int i = 0; i<m->nt; i++)
		{
			struct Vertex A = m->vert[(m->tri[i].idx[0])];
			struct Vertex B = m->vert[(m->tri[i].idx[1])];
			struct Vertex C = m->vert[(m->tri[i].idx[2])];	
			fprintf(fichier, "%lf %lf", A.x, A.y);
			fprintf(fichier, "\n");
			fprintf(fichier, "%lf %lf", B.x, B.y);
			fprintf(fichier, "\n");
			fprintf(fichier, "%lf %lf", C.x, C.y);
			fprintf(fichier, "\n");
			fprintf(fichier, "\n");
			fprintf(fichier, "\n");
		}
	}
	fclose(fichier);
	return 0;
}

int write_mesh2D(struct Mesh2D* m, const char* filename)
{
	FILE *fichier = fopen("filename", "w");
	if (fichier != NULL)
	{
		fprintf(fichier, "MeshVersionFormatted 2\n");
		fprintf(fichier, "Dimension 2\n");
		fprintf(fichier, "Vertices %d\n", m->nv);
		for (int i = 0; i < m->nv; i++)
		{
			fprintf(fichier, "%lf %lf\n", m->vert[i].coord[0], m->vert[i].coord[1]);
		}
		fprintf(fichier, "Triangles %d\n", m->nt);
		for (int j = 0; j < m->nt; j++)
		{
			fprintf(fichier, "%d %d %d\n", m->tri[j].idx[0], m->tri[j].idx[1], m->tri[j].idx[2]);
		}
		fprintf(fichier, "End\n");
	}
	fclose(fichier);
	return 0; 
}






								
			

	

			





