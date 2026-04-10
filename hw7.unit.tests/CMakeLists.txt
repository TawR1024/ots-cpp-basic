cmake_minimum_required(VERSION 4.2)

#setup global variables 
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE "." "_" PROJECT_NAME_SAFE ${PROJECT_NAME})

project(${PROJECT_NAME_SAFE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add dependencies
find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
    "include/*.cpp"
)

file(GLOB_RECURSE HEADER_FILES
    "src/*.hpp"
    "include/*.hpp"
)

# Create executable Main only if we have source files
if(SOURCE_FILES)
    add_executable(${PROJECT_NAME_SAFE} ${SOURCE_FILES} ${HEADER_FILES})
else()
    message(STATUS "No source files found for main executable, skipping ${PROJECT_NAME_SAFE}")
endif()

# Configure tests
enable_testing()
include(GoogleTest)

add_executable(
  custom_vector_test
  tests/custom_vector_test.cc
)

target_include_directories(
  custom_vector_test PRIVATE
  "src"
  "include"
)

add_executable(
  custom_list_test
  tests/custom_list_test.cc
)

target_include_directories(
  custom_list_test PRIVATE
  "src"
  "include"
)

# Link Google Test libraries
target_link_libraries(custom_vector_test GTest::gtest_main GTest::gtest)
target_link_libraries(custom_list_test GTest::gtest_main GTest::gtest)

# Discover tests after targets are created
gtest_discover_tests(custom_vector_test)
gtest_discover_tests(custom_list_test)


