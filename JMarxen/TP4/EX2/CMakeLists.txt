cmake_minimum_required(VERSION 3.12)
project(EX1)
add_executable(test_queue src/test_queue.c src/priority_queue.c)
target_include_directories(test_queue PUBLIC include)
