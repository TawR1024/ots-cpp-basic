cmake_minimum_required(VERSION 3.15)
project(astra_counter VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)

unset(OpenCL_FOUND CACHE)
unset(OpenCL_INCLUDE_DIRS CACHE)
unset(OpenCL_LIBRARIES CACHE)

find_package(OpenCL)

if(OpenCL_FOUND)
    find_path(OpenCL_HPP_INCLUDE_DIR CL/opencl.hpp
        PATHS ${OpenCL_INCLUDE_DIRS} /usr/include /usr/local/include
        NO_DEFAULT_PATH
    )
    if(NOT OpenCL_HPP_INCLUDE_DIR)
        find_path(OpenCL_HPP_INCLUDE_DIR CL/opencl.hpp)
    endif()
    if(NOT OpenCL_HPP_INCLUDE_DIR)
        set(OpenCL_FOUND FALSE)
        message(WARNING "OpenCL C API found, but CL/opencl.hpp (C++ API) not found. Building without GPU support.")
        message(STATUS "Install C++ headers: Ubuntu: sudo apt install opencl-clhpp-headers, macOS: install via vcpkg or manually")
    else()
        message(STATUS "OpenCL C++ headers found at: ${OpenCL_HPP_INCLUDE_DIR}")
    endif()
endif()


find_package(Boost REQUIRED COMPONENTS program_options)
find_package(GTest REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()