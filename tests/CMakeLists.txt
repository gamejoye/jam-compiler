find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 定义一个可执行文件用于运行测试
add_executable(lexer_tests lexer_tests.cpp)
add_executable(parser_tests parser_tests.cpp)
add_executable(table_tests table_tests.cpp)
add_executable(typesystem_tests typesystem_tests.cpp)
add_executable(utilities_tests utilities_tests.cpp)

# 链接Google Test库和lexer库到测试执行文件 /opt/homebrew/lib/libgtest_main.a
target_link_libraries(lexer_tests ${GTEST_LIBRARIES} gtest_main  jamlexer jamlib)
target_link_libraries(parser_tests ${GTEST_LIBRARIES} gtest_main jamparser jamlib)
target_link_libraries(table_tests ${GTEST_LIBRARIES} gtest_main jamlexer jamlib)
target_link_libraries(typesystem_tests ${GTEST_LIBRARIES} gtest_main jamlexer jamlib)
target_link_libraries(utilities_tests ${GTEST_LIBRARIES} gtest_main jamlexer jamlib)

add_test(
  NAME lexer_tests
  COMMAND lexer_tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_test(
  NAME parser_tests
  COMMAND parser_tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_test(
  NAME table_tests
  COMMAND table_tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_test(
  NAME typesystem_tests
  COMMAND typesystem_tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


add_test(
  NAME utilities_tests
  COMMAND utilities_tests
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
