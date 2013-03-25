cmake_minimum_required (VERSION 2.8)

project (cppinterview)

file(GLOB src
    "src/*.cpp"
)

file(GLOB header
    "*.h"
)

add_subdirectory (externals/gtest)

include_directories(${PROJECT_SOURCE_DIR}/externals/gtest/include)

add_executable (cppinterview ${src})
target_link_libraries(cppinterview gtest)
