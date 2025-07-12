cmake_minimum_required(VERSION 3.5)

project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Locate GTest

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_library(tests_lib STATIC
    tests.cpp
    tests.h)
target_include_directories(tests_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
)
add_executable(tests main.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

target_link_libraries(tests "$<LINK_LIBRARY:WHOLE_ARCHIVE,tests_lib>" VideoCompensation_lib)
