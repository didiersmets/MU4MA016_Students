cmake_minimum_required(VERSION 3.10)
project(Pascal C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
add_executable(pascal pascal.c)
add_executable(read_file read_file.c)
add_executable(sinc_func sinc_func.c)
target_link_libraries(sinc_func m)

