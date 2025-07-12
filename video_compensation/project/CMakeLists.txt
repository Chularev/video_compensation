cmake_minimum_required(VERSION 3.10)

project(VideoCompensation LANGUAGES CXX)

add_library(VideoCompensation_lib STATIC
        block.cpp 
        filereader.cpp 
        filewriter.cpp 
        frame.cpp 
        frameinfo.cpp 
        pixel.cpp 
        videocompensation.cpp
)

target_include_directories(VideoCompensation_lib PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(VideoCompensation
    main.cpp 
)

target_link_libraries(
    VideoCompensation 
    VideoCompensation_lib)
