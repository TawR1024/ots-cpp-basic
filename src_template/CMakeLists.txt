cmake_minimum_required(VERSION 4.2)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE "." "_" PROJECT_NAME_SAFE ${PROJECT_NAME})

project(${PROJECT_NAME_SAFE})

add_executable(${PROJECT_NAME_SAFE} main.cpp)


set_target_properties(${ROJECT_NAME_SAFE} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)