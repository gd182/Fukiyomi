find_package(OpenCV REQUIRED COMPONENTS core imgcodecs imgproc)

add_library(fukiyomi_vision
            src/opencv_bubble_detector.cpp
)

#target_compile_features(fukiyomi_vision PRIVATE cxx_std_23)

target_include_directories(fukiyomi_vision PUBLIC include)
target_link_libraries(fukiyomi_vision PUBLIC fukiyomi_core)
target_link_libraries(fukiyomi_vision PRIVATE ${OpenCV_LIBS})