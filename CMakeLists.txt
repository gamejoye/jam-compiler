enable_testing()

cmake_minimum_required(VERSION 3.10)
project(jam VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含src、tests目录
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(tests)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "include/*.cpp")
add_library(jamlib ${SOURCES})