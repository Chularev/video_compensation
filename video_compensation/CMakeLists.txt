cmake_minimum_required(VERSION 3.10)

project(VideoCompensation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
        block.cpp 
        filereader.cpp 
        filewriter.cpp 
        frame.cpp 
        frameinfo.cpp 
        main.cpp 
        pixel.cpp 
        videocompensation.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
)
