cmake_minimum_required(VERSION 3.5)

project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Locate GTest

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_library(gtests_lib STATIC
    tests.cpp
    tests.h)
target_include_directories(gtests_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
)
add_executable(gtests main.cpp)

target_link_libraries(gtests ${GTEST_LIBRARIES} pthread)

target_link_libraries(gtests "$<LINK_LIBRARY:WHOLE_ARCHIVE,gtests_lib>" VideoCompensation_lib)
