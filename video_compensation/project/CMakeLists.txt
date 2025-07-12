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


add_executable(VideoCompensation
    main.cpp 
)

target_link_libraries(
    VideoCompensation 
    VideoCompensation_lib)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    .
)
