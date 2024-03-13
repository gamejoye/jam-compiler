#include <cstdio>
#include <gtest/gtest.h>
#include <fstream>
#include "utilities.h"
#include "jam-parse.h"

static std::string examplesDir = "tests/lexer_test_examples/";

TEST(Utility_MapToToken_Test, Utility_MapToToken_Test_ShouldReturn_Test) {
  ASSERT_EQ(mapToToken(CLASS), "CLASS");
  ASSERT_EQ(mapToToken(IF), "IF");
  ASSERT_EQ(mapToToken(THEN), "THEN");
  ASSERT_EQ(mapToToken(ELSE), "ELSE");
  ASSERT_EQ(mapToToken(FOR), "FOR");
  ASSERT_EQ(mapToToken(IN), "IN");
  ASSERT_EQ(mapToToken(RETURN), "RETURN");
  ASSERT_EQ(mapToToken(EXTENDS), "EXTENDS");
  ASSERT_EQ(mapToToken(LET), "LET");
  ASSERT_EQ(mapToToken(NEW), "NEW");
  ASSERT_EQ(mapToToken(INT_CONST), "INT_CONST");
  ASSERT_EQ(mapToToken(BOOL_CONST), "BOOL_CONST");
  ASSERT_EQ(mapToToken(STR_CONST), "STR_CONST");
  ASSERT_EQ(mapToToken(OBJECTID), "OBJECTID");
  ASSERT_EQ(mapToToken(TYPEID), "TYPEID");
  ASSERT_EQ(mapToToken(ERROR), "ERROR");
}