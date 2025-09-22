cmake_minimum_required(VERSION 3.10)
project(tp1)

# Specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Specify C++ standard for C++ files
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Executables for each project
add_executable(queue src/test_queue.c src/circular_buffer_queue.c)
add_executable(cppqueue src/test_cppqueue.cpp)
add_executable(sorting src/test_sorting_algorithms.c src/bubblesort.c src/insertionsort.c src/mergesort.c)

# Set output directories for all targets
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)