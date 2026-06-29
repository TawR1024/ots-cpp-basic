enable_testing()

add_executable(astra_counter_tests
    test_main.cpp
    test_cli.cpp
    test_scanner.cpp
    test_loader.cpp
    test_detector.cpp
    test_end_to_end.cpp
)

target_link_libraries(astra_counter_tests
    PRIVATE astra_counter_lib
    PRIVATE GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(astra_counter_tests)
