cmake_minimum_required(VERSION 3.5)

project(tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Locate GTest

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_library(gtests_src STATIC
    tests.cpp
    tests.h)
target_include_directories(gtests_src PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src"
)
add_executable(gtests main.cpp)

target_link_libraries(gtests ${GTEST_LIBRARIES} pthread)

target_link_libraries(gtests "$<LINK_LIBRARY:WHOLE_ARCHIVE,gtests_src>" VideoCompensation_lib)

function(copy_directory_if_different SRC DEST)
    file(MAKE_DIRECTORY ${DEST})
    file(GLOB_RECURSE FILES "${SRC}/*")
    
    foreach(FILE_PATH ${FILES})
        file(RELATIVE_PATH REL_PATH ${SRC} ${FILE_PATH})
        set(DST "${DEST}/${REL_PATH}")
        get_filename_component(DST_DIR ${DST} DIRECTORY)
        file(MAKE_DIRECTORY ${DST_DIR})
        
        execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FILE_PATH} ${DST})
    endforeach()
endfunction()

copy_directory_if_different(${PROJECT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)
