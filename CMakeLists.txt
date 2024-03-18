enable_testing()

cmake_minimum_required(VERSION 3.10)
project(jam VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(tests)
add_subdirectory(extern/googletest)

include_directories(extern/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/src/table)
include_directories(${CMAKE_SOURCE_DIR}/src/tree)
include_directories(${CMAKE_SOURCE_DIR}/src/utilities)
include_directories(${CMAKE_SOURCE_DIR}/src/parser)

file(GLOB_RECURSE TABLE_SOURCES "src/table/*.cpp")
file(GLOB_RECURSE TREE_SOURCES "src/tree/*.cpp")
file(GLOB_RECURSE UTILITIES_SOURCES "src/utilities/*.cpp")
file(GLOB_RECURSE PARSER_SOURCES "src/parser/*.cc")

set(ALL_SOURCES ${TABLE_SOURCES} ${TREE_SOURCES} ${UTILITIES_SOURCES} ${PARSER_SOURCES})
add_library(jamlib ${ALL_SOURCES})