add_library(fukiyomi_core 
            src/version.cpp
            src/page_error.cpp
)

#target_compile_features(fukiyomi_core PRIVATE cxx_std_23)

target_include_directories(fukiyomi_core PUBLIC include)