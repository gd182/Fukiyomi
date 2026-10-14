cmake_minimum_required(VERSION 3.25)

project(fukiyomi LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_compile_options(-funsigned-char)

enable_testing()

add_subdirectory(libs/core)
add_subdirectory(libs/sources)
add_subdirectory(libs/vision)
add_subdirectory(apps/desktop)
add_subdirectory(apps/cli)

add_subdirectory(tests)