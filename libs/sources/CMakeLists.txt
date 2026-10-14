add_library(fukiyomi_sources 
            src/folder_page_source.cpp
)

#target_compile_features(fukiyomi_sources PRIVATE cxx_std_23)

target_link_libraries(fukiyomi_sources PUBLIC fukiyomi_core)
target_include_directories(fukiyomi_sources PUBLIC include)