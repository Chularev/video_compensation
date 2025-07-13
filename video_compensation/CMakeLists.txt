cmake_minimum_required(VERSION 3.5)

project(VideoCompensation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_custom_target(data_copy ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMENT "Copying data folder to build directory"
)

add_custom_target(scripts_copy ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts
        ${CMAKE_CURRENT_BINARY_DIR}/scripts
    COMMENT "Copying scripts folder to build directory"
)

add_custom_target(scripts_mainbenchmark_copy ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/scripts/mainbenchmark
        ${CMAKE_CURRENT_BINARY_DIR}/scripts/mainbenchmark
    COMMENT "Copying mainbenchmark folder to build directory"
)

add_subdirectory(project)
add_subdirectory(unittests)
add_subdirectory(benchmark)
