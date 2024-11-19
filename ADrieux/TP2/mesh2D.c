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
	int nv;
	int nt;
	double Vx;
	double Vy;
	if (fichier != NULL)
	{
		while(fgets(line, TAILLE_MAX, fichier) != NULL)
		{
			sscanf(line, "Vertices %d", &nv);
			sscanf(line, "%f %f", &Vx, &Vy);



			





