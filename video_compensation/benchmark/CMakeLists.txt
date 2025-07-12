cmake_minimum_required(VERSION 3.5)

project(benchmark LANGUAGES CXX)

# benchmark
find_package(benchmark REQUIRED)

add_executable(mainbenchmark mainbenchmark.cpp)
target_link_libraries(mainbenchmark benchmark::benchmark)

add_executable(benchmark benchmark.cpp)

# Locate GTest

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(benchmark ${GTEST_LIBRARIES} pthread)
target_link_libraries(benchmark tests_lib VideoCompensation_lib)

target_include_directories(benchmark PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/project"benchmark
    "${CMAKE_SOURCE_DIR}/unittests"
)
target_link_libraries(benchmark benchmark::benchmark)
