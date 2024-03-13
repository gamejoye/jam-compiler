cmake_minimum_required(VERSION 3.10)
project(JamLexer)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 查找Flex包
find_package(FLEX REQUIRED)

# 使用Flex处理lexer文件
FLEX_TARGET(JamLexer jam_lexer.l ${CMAKE_CURRENT_BINARY_DIR}/jam_lexer.cpp)

# 创建一个静态库，包含Flex生成的C++代码
add_library(jamlexer STATIC ${FLEX_JamLexer_OUTPUTS})

# 将当前构建目录添加到包含目录，以便找到Flex生成的头文件
target_include_directories(jamlexer PUBLIC ${CMAKE_SOURCE_DIR}/include)
