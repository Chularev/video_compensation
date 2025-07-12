cmake_minimum_required(VERSION 3.5)

project(VideoCompensation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(project)
add_subdirectory(unittests)
add_subdirectory(benchmark)
