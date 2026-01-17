#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "/root/MU4MA016_Students/ADrieux/TP3/include/mesh_adjacency.h"
#include "/root/MU4MA016_Students/ADrieux/TP3/include/mesh_io.h"

int main(int argc, char** argv)
{
	struct Mesh *m = (struct Mesh *)malloc(sizeof(struct Mesh));
	read_mesh_from_wavefront_file(m,"/root/MU4MA016_Students/TP3/data/bunny.obj");
	clock_t begin, end;

	begin = clock();
	build_adjacency_table1(m);
	end = clock();
	double time_spent1 = (double)(end - begin)/CLOCKS_PER_SEC;

	begin = clock();
	build_adjacency_table2(m);
	end = clock();
	double time_spent2 = (double)(end - begin)/CLOCKS_PER_SEC;

	begin = clock();
	build_adjacency_table3(m);
	end = clock();
	double time_spent3 = (double)(end - begin)/CLOCKS_PER_SEC;

	printf("premier methode : %f\n", time_spent1);
	printf("deuxieme methode : %f\n", time_spent2);
	printf("troisieme methode : %f\n", time_spent3);

	free(m);
}

	
