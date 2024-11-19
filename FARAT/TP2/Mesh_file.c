#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Structure.c"    //next : use init and create another fuction (Struct Mesh2D*q, char *textfile)



int Meshstruct_from_Meshfile(struct Mesh2D *q, const char *textfile){  //ATTENTION : const char * != char *
	FILE *text = fopen(textfile,"r");
	char *line = malloc(256*sizeof(char));

	char **keyss = malloc(sizeof(char *)*2);
	keyss[0] = "Vertices";
	keyss[1] = "Triangles";

	while (fgets(line, 256, text) != NULL){

		if (strstr(line,keyss[0]) != NULL){

			for (int i=0; i<(q->nv); i++){
				fgets(line, 256, text);
				sscanf(line,"                         %lf                         %lf",&((q->vert)[i].x),&((q->vert)[i].y));
			}
		}


		if (strstr(line,keyss[1]) != NULL){

			for (int i=0; i<(q->nt); i++){
				fgets(line, 256, text);
				sscanf(line,"%d %d %d",&((q->tri)[i].Index[0]),&((q->tri)[i].Index[1]),&((q->tri)[i].Index[2]));
			}
		}
	}

	free(line);
	free(keyss);
	fclose(text);
	return 0;
}




int read_mesh2D(struct Mesh2D *m, char const *filename){ //ask for prototype

	FILE *text = fopen(filename,"r");
	char *line = malloc(256*sizeof(char));

	int vtx_capacity = 0;
	int tri_capacity = 0;

	char **keys = malloc(sizeof(char *)*3);
	keys[0] = "MeshVersionFormatted";
	keys[1] = "Vertices";
	keys[2] = "Triangles";

	while (fgets(line, 256, text) != NULL){


		if (strstr(line, keys[0]) != NULL){

			char data = line[strlen(keys[0])+2];
			//printf("%c\n",data);
			if (data != '2'){
				printf("it is not a mesh 2D\n");
				break;
			}
		}


		if (strstr(line, keys[1]) != NULL){

			sscanf(line, " Vertices %d", &vtx_capacity);
		}


		if (strstr(line, keys[2]) != NULL){
			sscanf(line, " Triangles %d", &tri_capacity);
		}

	}

	//struct Mesh2D *m = malloc(2*sizeof(int) + tri_capacity*3*sizeof(int) + vtx_capacity*2*sizeof(double));
	//initialize_mesh2D(m,vtx_capacity,tri_capacity);
	

	fclose(text);

	m->nv = vtx_capacity;
	m->nt = tri_capacity;
	Meshstruct_from_Meshfile(m, filename);

/*	printf("{\n");
	printf("nv : %d\n",q->nv);
	for (int i = 0; i < q->nv; ++i)
	{
		printf("vecteur %d : x = %f; y =%f\n",i,(q->vert)[i].x,(q->vert)[i].y);
	}
	
	printf("nt : %d\n",q->nt);

	for (int i = 0; i < q->nt; ++i)
	{
		printf("Triangle %d: A=%d ; B=%d ; C=%d\n",i,(q->tri)[i].Index[0],(q->tri)[i].Index[1],(q->tri)[i].Index[2]);
	}
	printf("}\n");
*/



	free(line);
	free(keys);

	return 0;
}



int mesh2D_to_gnuplot(struct Mesh2D* m, const char* filename){

	FILE *text = fopen(filename, "w");
	if (fgetc(text) == EOF){
		fprintf(text, "# %s\t%s\t%s\t%s\t%s\t%s\t%s\n","Vertex","x","y","Triangle","A","B","C");
	}

	int n = (m->nv >= m->nt)?m->nv:m->nt;

	for (int i = 0; i < n; ++i){
		
		if (i<m->nv){

			if (i<m->nt){
				fprintf(text, "%d\t%f\t%f\t%d\t%d\t%d\t%d\n",i+1,(m->vert)[i].x,(m->vert)[i].y,i+1,(m->tri)[i].Index[0],(m->tri)[i].Index[1],(m->tri)[i].Index[2]);
			}

			else{
				fprintf(text, "%d\t%f\t%f\t%c\t%c\t%c\t%c\n",i+1,(m->vert)[i].x,(m->vert)[i].y,' ',' ',' ',' ');
			}
		}

		else{
			fprintf(text, "%c\t%c\t%c\t%d\t%d\t%d\t%d\n",' ',' ',' ',i+1,(m->tri)[i].Index[0],(m->tri)[i].Index[1],(m->tri)[i].Index[2]);
		}
	}

	fclose(text);
}




int write_mesh2D(struct Mesh2D* m, const char* filename){

	FILE *text = fopen(filename,"w");
	fprintf(text, " MeshVersionFormatted 2\n");
	fprintf(text, " Dimension 3\n");
	fprintf(text, " Vertices %d\n", m->nv);

	for (int i = 0; i < m->nv; ++i)
	{
		fprintf(text,"                         %lf                         %lf\n",(m->vert)[i].x,(m->vert)[i].y);
	}
	fprintf(text," Triangles %d\n", m->nt);

	for (int i = 0; i < m->nt; ++i)
	{
		fprintf(text," %d %d %d\n",(m->tri)[i].Index[0],(m->tri)[i].Index[1],(m->tri)[i].Index[2]);
	}

	fprintf(text," End");

	fclose(text);
}




int main(int argc, char const *argv[])
{
	//char *meshfile = argv[1];
	//char *filename = argv[2];

	struct Mesh2D *m = malloc((2+3)*sizeof(int) + 2*sizeof(double));
	initialize_mesh2D(m,1000,1000);

	read_mesh2D(m,argv[1]);
	//mesh2D_to_gnuplot(m,argv[2]);
	write_mesh2D(m,argv[2]);

	free(m);
	return 0;
}