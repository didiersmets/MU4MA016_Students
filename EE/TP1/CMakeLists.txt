cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(tp1)
add_executable(tp1 
	src/test_queue.c
	src/circular_buffer_queue.c
)
target_include_directories(tp1 PRIVATE include)
