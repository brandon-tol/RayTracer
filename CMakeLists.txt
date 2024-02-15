cmake_minimum_required(VERSION 3.10)

project(RayTracer VERSION 0.2 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/eigen)

include_directories(lib/eigen)
include_directories(src)
include_directories(include)

# Group source filess
# set(SOURCES
#     external/simpleppm.cpp
#     external/test_eigen.cpp
#     external/test_json.cpp
#     external/test_ppm.cpp
# )

file(GLOB_RECURSE SOURCES
    src/*.cpp
    external/*.cpp)

file(GLOB_RECURSE HEADERS
    src/*.h)

add_executable(RayTracer ${SOURCES})

target_include_directories(RayTracer
    PRIVATE
    "${PROJECT_SOURCE_DIR}/external"
    lib/eigen
    src
)

target_link_libraries(RayTracer PRIVATE eigen)