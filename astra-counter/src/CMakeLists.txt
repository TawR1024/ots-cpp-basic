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
    PUBLIC OpenCL::OpenCL
    PUBLIC Boost::program_options
)

add_executable(astra_counter ${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp)
target_link_libraries(astra_counter PRIVATE astra_counter_lib)
