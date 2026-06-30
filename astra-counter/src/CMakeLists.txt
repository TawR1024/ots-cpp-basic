add_library(astra_counter_lib
    cli/parser.cpp
    scanner/directory_scanner.cpp
    loader/jpeg_loader.cpp
    opencl/engine.cpp
    detector/star_detector.cpp
    utils/thread_pool.cpp
    utils/result_writer.cpp
)

target_include_directories(astra_counter_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(astra_counter_lib
    PUBLIC opencv_core opencv_imgcodecs opencv_imgproc
    PUBLIC Boost::program_options
)

if(OpenCL_FOUND)
    target_compile_definitions(astra_counter_lib PUBLIC HAVE_OPENCL)
    target_link_libraries(astra_counter_lib PUBLIC OpenCL::OpenCL)
else()
    message(WARNING "OpenCL not found. Building without GPU support.")
endif()

add_executable(astra_counter ${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp)
target_link_libraries(astra_counter PRIVATE astra_counter_lib)
