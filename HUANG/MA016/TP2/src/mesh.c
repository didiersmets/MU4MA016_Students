#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include "mesh.h"

int init_mesh2D(struct Mesh2D* m,int vtx_capacity, int tri_capacity)
{
  if (m != NULL){
    m->nv = vtx_capacity;
    m->nt = tri_capacity;
    m->vert = malloc(vtx_capacity *sizeof(struct Vertex));
    m->tri = malloc(tri_capacity * sizeof(struct Triangle));
  }
  return 0;
}

void dispose_mesh2D(struct Mesh2D* m)
{
  if (m!= NULL){
    free(m->vert);
    free(m->tri);
  }
  free(m);
}

double area_mesh2D(struct Mesh2D* m)
{
  if(m->tri == NULL){
    return 0;
  }
  
  double area=0;

  for(int j=0;j<(m->nt);j++){
    struct Vertex* c1=&m->vert[m->tri[j].a];
    struct Vertex* c2=&m->vert[m->tri[j].b];
    struct Vertex* c3=&m->vert[m->tri[j].c];
    double surface =0.5* ((c2->x - c1->x)*(c3->y - c1->y)-(c2->y - c1-> y)*(c3->x - c1->x));
    area += surface; 
  }
  return area;
}

int read_mesh2D(struct Mesh2D* m,const char* filename)
{
	FILE* f= fopen(filename,"r");
	if(f==NULL){
		printf("unenable to open this file");
		return 1;
	}

	char strline[512];
	while(!feof(f)){
		fgets(strline,512,f);
		if (sscanf(strline,"Vertices %d",&m->nv)==1){
			m->vert = malloc(m->nv*sizeof(struct Vertex));
			printf("%d \n",m->nv);
			for(int i=0;i<(m->nv);i++){
				fgets(strline,512,f);
				sscanf(strline,"%lf %lf",&m->vert[i].x,&m->vert[i].y);
			}
		}
		if (sscanf(strline,"Triangles %d ",&m->nt)==1){
			m->tri = malloc(m->nt*sizeof(struct Triangle));
			printf("%d \n",m->nt);
			for(int i=0;i<(m->nt);i++){
				fgets(strline,512,f);
				sscanf(strline,"%d %d %d",&m->tri[i].a,&m->tri[i].b,&m->tri[i].c);
			}

		}	
	}
	

	fclose(f);
	return 0;
}

int mesh2D_to_gnuplot(struct Mesh2D *m,const char* filename)
{
	FILE* f = fopen(filename,"w+");
	if(f==NULL){
		printf("this file do not exist");
		return 1;
	}
	if(m==NULL){
		printf("can't write without data");
		return 1;
	}
	fprintf(f,"# x y \n");
	for(int i=0;i<(m->nt);i++){
		int a=m->tri[i].a;
		int b=m->tri[i].b;
		int c=m->tri[i].c;
		fprintf(f,"%f %f \n",m->vert[a].x,m->vert[a].y);
		fprintf(f,"%f %f \n",m->vert[b].x,m->vert[b].y);
		fprintf(f,"%f %f \n",m->vert[c].x,m->vert[c].y);
		fprintf(f,"%f %f \n",m->vert[a].x,m->vert[a].y);
		fprintf(f,"\n");
	}
	fclose(f);
	return 0;
}

int write_mesh2D(struct Mesh2D* m,const char*filename)
{
	if(m==NULL){
		printf("can't write without data");
		return 1;
	}

	FILE* f= fopen(filename,"w+");

	fprintf(f,"MeshVersionFormatted %d \n",2);
	fprintf(f,"Dimension 2 \n");
	fprintf(f,"Vertices %d \n",m->nv);
	for(int i=0;i < (m->nv);i++){
		fprintf(f,"%f %f \n",m->vert[i].x,m->vert[i].y);
	}
	fprintf(f,"Triangles %d \n",m->nt);
	for(int i=0;i < (m->nt);i++){
		fprintf(f,"%d %d %d \n",m->tri[i].a,m->tri[i].b,m->tri[i].c);
	}
	fclose(f);
	return 0;
}
