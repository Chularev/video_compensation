cmake_minimum_required(VERSION 3.5)

project(benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# benchmark
find_package(benchmark REQUIRED)

add_executable(benchmark benchmark.cpp)

# Locate GTest

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(benchmark ${GTEST_LIBRARIES} pthread)
target_link_libraries(benchmark gtests_src src_lib)

target_include_directories(benchmark PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/unittests"
)
target_link_libraries(benchmark benchmark::benchmark)
