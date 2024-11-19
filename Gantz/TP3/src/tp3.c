#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/mesh_adjacency.h"
#include "../include/mesh_io.h"

int main(){
	struct Mesh *m = (struct Mesh*) malloc(sizeof(struct Mesh));
	read_mesh_from_wavefront_file(m,"../data/bugatti.obj");
	
	int* adjacency_table = (int*) malloc(3*m->ntri);
	
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	adjacency_table = build_adjacency_table1(m);
	end = clock();
	cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("# time (method 1): %lf\n", cpu_time_used);

	start = clock();
	adjacency_table = build_adjacency_table2(m);
	end = clock();
	cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("# time (method 2): %lf\n", cpu_time_used);

	start = clock();
	adjacency_table = build_adjacency_table3(m);
	end = clock();
	cpu_time_used = ((double) (end-start))/CLOCKS_PER_SEC;
	printf("# time (method 3): %lf\n", cpu_time_used);
	
	free(m);
	free(adjacency_table);
}
