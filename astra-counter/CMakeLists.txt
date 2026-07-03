cmake_minimum_required(VERSION 3.25)

project(astra_counter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

find_package(OpenCL)

if(OpenCL_FOUND)
    include(CheckIncludeFileCXX)
    check_include_file_cxx("CL/opencl.hpp" HAS_OPENCL_HPP)
    if(NOT HAS_OPENCL_HPP)
        set(OpenCL_FOUND FALSE)
        message(WARNING "OpenCL C headers found, but CL/opencl.hpp (C++ API) is missing. Building without GPU support.")
    endif()
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
