cmake_minimum_required(VERSION 3.12)
project(EX1_cpp)
add_executable(test_queue src/test_queue.cpp)
target_include_directories(test_queue PUBLIC include src)
