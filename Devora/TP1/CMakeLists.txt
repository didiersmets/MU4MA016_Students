cmake_minimum_required(VERSION 3.26)
project(ProjectName)

# Add your executable or library target here
add_executable(main src/test_sorting.c src/sorting.c src/circular_buffer_queue.c)

# Specify include directories for the target
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
