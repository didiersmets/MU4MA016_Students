cmake_minimum_required(VERSION 3.12)
project(TP4)

# Set the C standard 
set(CMAKE_C_STANDARD 11)

# Define the executable target
add_executable(main src/main.c src/avl_trees.c)

# Add include directories
target_include_directories(main PUBLIC include)

# Add compiler options
target_compile_options(main PRIVATE -O3 -Wall)
