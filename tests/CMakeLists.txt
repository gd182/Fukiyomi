include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    SYSTEM
)

FetchContent_MakeAvailable(googletest)

find_package(OpenCV REQUIRED COMPONENTS core imgcodecs)

foreach(target IN ITEMS gtest gtest_main gmock gmock_main)
    target_compile_options(${target} PRIVATE -w)
endforeach()

add_executable(fukiyomi_tests
    page_error_test.cpp
    natural_sort_test.cpp
    opencv_bubble_detector_test.cpp
)

target_link_libraries(fukiyomi_tests
    PRIVATE
        fukiyomi_core
        fukiyomi_vision
        GTest::gtest_main
        ${OpenCV_LIBS}
)

target_compile_options(fukiyomi_tests
    PRIVATE
        -fsanitize=address
)

target_link_options(fukiyomi_tests
    PRIVATE
        -fsanitize=address
)

include(GoogleTest)
gtest_discover_tests(fukiyomi_tests)
