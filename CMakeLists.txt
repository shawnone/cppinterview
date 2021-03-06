cmake_minimum_required (VERSION 2.8)

project (cppinterview)

file(GLOB src
    "src/*.cpp"
)

file(GLOB header
    "*.h"
)

file(GLOB_RECURSE leetcode_src
    "leetcode/src/*.cpp"
)

file(GLOB_RECURSE leetcode_header
    "leetcode/*.h"
)

source_group(source FILES ${src})
source_group(include FILES ${header})
source_group(leetcode\\source FILES ${leetcode_src})
source_group(leetcode\\include FILES ${leetcode_header})


add_definitions(-DGTEST_HAS_TR1_TUPLE=0)

if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG  "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1 /DRDFD_DIAGNOSTIC_MODE /GS" CACHE STRING "Compiler flags for Debug." FORCE)
    set(CMAKE_CXX_FLAGS_MINSIZEREL  "/MT /O1 /Ob1 /D NDEBUG /GS-" CACHE STRING "Compiler flags for MinSizeRel." FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE  "/MT /O2 /Ob2 /D NDEBUG /GL -PogoSafeMode /GS-" CACHE STRING "Compiler flags for Release." FORCE)
    set(CMAKE_CXX_FLAGS_RELEASELOWOPT  "/MT /O2 /Ob2 /D NDEBUG /MP /GS-" CACHE STRING "Compiler flags for Release." FORCE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "/MT /Zi /Ob0 /Od /D NDEBUG /DRDFD_DIAGNOSTIC_MODE /GS-" CACHE STRING "Compiler flags for RelWithDebInfo." FORCE)
else(APPLE)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
endif()

add_subdirectory (externals/gtest)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/externals/gtest/include)

add_executable (cppinterview ${src} ${header} ${leetcode_src} ${leetcode_header})
target_link_libraries(cppinterview gtest)
