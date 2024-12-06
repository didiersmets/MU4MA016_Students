cmake_minimum_required(VERSION 3.12)
project(MU4MA016_CC1)

# Set the C standard 
set(CMAKE_C_STANDARD 11)

# Define the executable target
add_executable(main main.c graph.c dijkstra.c)

# Add include directories
#target_include_directories(main PUBLIC include)

# Add compiler options
target_compile_options(main PRIVATE -O3 -Wall)
