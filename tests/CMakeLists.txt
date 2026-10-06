include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    SYSTEM
)

FetchContent_MakeAvailable(googletest)

add_executable(fukiyomi_tests
    page_error_test.cpp
    natural_sort_test.cpp
)

target_link_libraries(fukiyomi_tests
    PRIVATE
        fukiyomi_core
        GTest::gtest_main
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