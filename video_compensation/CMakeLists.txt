cmake_minimum_required(VERSION 3.5)

project(my_var LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(unittests)
add_subdirectory(benchmark)
