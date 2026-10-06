cmake_minimum_required(VERSION 3.25)

project(fukiyomi LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_compile_options(-funsigned-char)

enable_testing()

add_subdirectory(core)
add_subdirectory(sources)
add_subdirectory(apps/desktop)
add_subdirectory(apps/cli)

add_subdirectory(tests)