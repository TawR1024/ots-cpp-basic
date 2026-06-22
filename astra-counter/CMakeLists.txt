cmake_minimum_required(VERSION 3.25)

project(astra_counter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
find_package(OpenCL REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
