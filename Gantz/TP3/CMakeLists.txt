cmake_minimum_required(VERSION 3.12)
project(TP3)
add_executable(tp3 src/tp3.c src/hash_tables.c src/mesh.c src/mesh_adjacency.c
	src/mesh_io.c)
target_include_directories(tp3 PUBLIC include)

