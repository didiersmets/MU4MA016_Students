#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Vertex
{
  double x;
  double y;
}

struct Triangle
{
  int a;
  int b;
  int c;
}

struct Mesh2D
{
  int nv;//number of vertices
  Vertex* vert;
  int nt;//number of triangles
  Triangle* tri;
}

int init_mesh2D(struct Mesh2D* m,int vtx_capacity, int tri_capacity)
{
  if (m != NULL){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(vtx_capacity *sizeof(struct Vertex));
    m->tri = malloc(tri_capacity * sizeof(struct Triangle));
  }
  return 0
}

void dispose_mesh2D(struct Mesh2D* m)
{
  if (m!= NULL){
    free(m->vert);
    free(m->tri);
  }
}

double area_mesh2D(struct Mesh2D* m)
{
  if(m->tri == NULL){
    return 0
  }
  
  double area=0;

  for(int j=0,j<m->nt,j++){
    struct Vertex *c1=m->tri[j]->a;
    struct Vertex *c2=m->tri[j]->b;
    struct Vertex *c3=m->tri[j]->b;
    double surface =0.5* ((c2->x - c1-> x)*(c3->y - c1->y)-(c2->y - c1-> y)*(c3->x - c1-> x));
    area += surface; 
  }
  return area;
}

int read_mesh2D(struct Mesh2D* m,const char* filename)
{
	FILE* f;
	f= fopen(filename,"r");
	if(f==NULL){
		printf("unable to open this file")
		return 1
	}
	
	struct Mesh2D* m;

	char strline[128];
	while(!feof(f)){
		fgets(strline,128,f);
		if (sscanf(strline,"Vertices %d",&m->nv)==1){
			m->nv = nv;
			m->vert = malloc(nv*sizeof(struct Vertex));
			for(int i=0;i<nv;i++){
				fgets(strline,128,f);
				ssanf(strline,"%f %f",&m->vert[i].x,&m->vert[i].y);
			}
		}
		if (sscanf(strline,"Triangles %d",&m->nt)==1){
			
			m->tri = malloc(nt*sizeof(struct Triangle));
			for(int i=0;i<nt;i++){
				fgets(strline,128,f);
				sscanf(strline,"%d %d %d",&m->tri[i].a,&m->tri[i].b,&m->tri[i].c);
			}

		}	
	}
	

	fclose(f);
	return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D *m,const char* filename)
{
	FILE* f;
	fopen(filename,w+);
	if(m==NULL){
		printf("can't write without data");
		return 1
	}
	fprintf(f,"# x y \n");
	for(int i=0;i<(m->nt);i++){
		for(int j=0;j<=()){
		}
	}

	fclose(f);
	return 0
}

int write_mesh2D(struct Mesh2D* m,const char*filename)
{
	if(m==NULL){
		printf("can't write without data");
		return 1
	}

	FILE* f;
	fopen(filename,w+);

	fprintf(f,"MeshVersionFormatted %d  \n",2);
	fprintf(f,"Dimension 2 \n");
	fprintf(f,"Vertices %f \n",m->nv);
	for(int i=0;i < (m->nv);i++){
		fprintf(f,"%f %f \n",m->vert[i].x,m->vert[i].y)
	}
	fprintf(f,"Triangles %f \n",m->nt);
	for(int i=0;i < (m->nt);i++){
		fprintf(f,"%d %d %d \n",m->tri[i].a,m->tri[i].b,m->tri[i].c)
	}
}
