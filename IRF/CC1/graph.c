#include <stdio.h> 
#include <stdlib.h>

#include "graph.h"

//extras que me pueden hacer falta
struct Vertex {
	union {
		struct{
			double x,y;
		};
		double coord[2];
	};                                                                      
};

int initialize(struct EdgeList* m, int vtx_capacity, int edg_capacity)     
{                                                                               
         m->nverts = vtx_capacity;                                                
         m->nedges = edg_capacity;            
         m->edges = (struct Edge*)malloc(edg_capacity*sizeof(struct Edge));
	 return 0;                                                               
}

struct EdgeList *read_edge_list_from_file(const char *filename, struct EdgeList* m)
{
	FILE *file = fopen("filename", "r");
	char line[100];
	if (file != NULL){
		while (fgets(line, 100, file) != NULL){
			if (sscanf(line, "%d", &m->nedges) == 1){
				m->edges = (struct Edge*)malloc(m->nedges*sizeof(struct Edge));
				for (int i  = 0, i<m->nedges, i++){
					fgets(line, 100, file);
					sscanf(line, "%d %d %lf", &m->edges[i].orig, &m->edges[i].dest, &m->edges[i].cost);

				}
			}
		}
	}
	return 0;
}



struct Graph *build_graph_from_edge_list(const EdgeList *EL);
/* Implement me here. Worth 5 points */








