cmake_minimum_required(VERSION 3.10)
project(JamParser)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找Bison和Flex包
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# 使用Bison处理parser文件
BISON_TARGET(JamParser
             ${CMAKE_CURRENT_SOURCE_DIR}/jam-parser.y
             ${CMAKE_SOURCE_DIR}/include/jam-parser.tab.cpp
             COMPILE_FLAGS "--defines=${CMAKE_SOURCE_DIR}/include/jam-parser.tab.hh")


FLEX_TARGET(JamLexer ${CMAKE_SOURCE_DIR}/src/parser/jam-lexer.l ${CMAKE_CURRENT_BINARY_DIR}/jam-lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(JamLexer JamParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR}) 
             
add_library(jamparser STATIC ${BISON_JamParser_OUTPUTS})

target_include_directories(jamparser PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(jamparser PUBLIC jamlexer)
