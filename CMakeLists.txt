cmake_minimum_required (VERSION 2.8)

project (cppinterview)

file(GLOB src
    "src/*.cpp"
)

file(GLOB header
    "*.h"
)

include_directories(${PROJECT_SOURCE_DIR}/3rdparty/include)
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/lib)

add_executable (cppinterview ${src})
target_link_libraries(cppinterview gtest)
