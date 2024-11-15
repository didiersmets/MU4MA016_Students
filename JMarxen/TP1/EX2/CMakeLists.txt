cmake_minimum_required(VERSION 3.12)
project(EX2)
add_executable(test_routines src/test_routines.c src/sorting.c)
target_include_directories(test_routines PUBLIC include)
