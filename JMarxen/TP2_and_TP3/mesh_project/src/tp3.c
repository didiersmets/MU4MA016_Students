#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash_tables.h"
#include "mesh_3D.h"

int main(int argc, char *argv[]) {
	printf("Program started. \n");
	const char *filename = argv[1];
	printf("filename: %s. \n", filename);
	struct Mesh3D m;
	// read_mesh3D(&m, filename);
	read_mesh_from_wavefront_file(&m, filename);
	printf("Mesh succesfully read. \n");
	clock_t start, end;
	double cpu_time_used;
	// Timing for the first adjacency table construction (method 1)
	// If bugatti.obj, skip Method 1
	char *basename_file = basename(filename);
	if (strstr(basename_file, "bugatti.obj") != NULL) {
	} else {
		printf("Timing method 1... \n");
		start = clock();
		int *adj1 = build_adjacency_table1(&m);
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Method 1 took %f seconds\n", cpu_time_used);
		free(adj1);
	}
	// Timing for the second adjacency table construction (method 2)
	printf("Timing method 2... \n");
	start = clock();
	int *adj2 = build_adjacency_table2(&m);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Method 2 took %f seconds\n", cpu_time_used);
	free(adj2);
	// Timing for the third adjacency table construction (method 3)
	printf("Timing method 3... \n");
	start = clock();
	int *adj3 = build_adjacency_table3(&m);
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Method 3 took %f seconds\n", cpu_time_used);
	free(adj3);
	return 0;
}

