cmake_minimum_required(VERSION 4.2)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE "." "_" PROJECT_NAME_SAFE ${PROJECT_NAME})

project(${PROJECT_NAME_SAFE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "src/*.hpp"
    "main.cpp"
)

# Create executable
add_executable(${PROJECT_NAME_SAFE} ${SOURCE_FILES})

