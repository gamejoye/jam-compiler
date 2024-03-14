#include <cstdio>
#include <gtest/gtest.h>
#include <fstream>
#include "utilities.h"

extern int yylex(void);
extern int yy_scan_string(const char *str);
extern FILE *yyin;

static std::string examplesDir = "tests/lexer_test_examples/";

TEST(LexerGoodTest, CanRecognizeTokens1) {
  yyin = fopen((examplesDir + "good_test1.jam").c_str(), "r");
  std::ifstream targetFile(examplesDir + "good_test1.expected");
  int token;
  std::string expected;
  while ((token = yylex()) != 0 && std::getline(targetFile, expected)) {
    ASSERT_EQ(expected, mapToToken(token));
  }

  if(token != 0) {
    ASSERT_TRUE(false);
  }

  fclose(yyin);
}

TEST(LexerGoodTest, CanRecognizeTokens2) {
  yyin = fopen((examplesDir + "good_test2.jam").c_str(), "r");
  std::ifstream targetFile(examplesDir + "good_test2.expected");
  int token;
  std::string expected;
  while ((token = yylex()) != 0 && std::getline(targetFile, expected)) {
    ASSERT_EQ(expected, mapToToken(token));
  }

  if(token != 0) {
    ASSERT_TRUE(false);
  }

  fclose(yyin);
}

TEST(LexerGoodTest, CanRecognizeTokens3) {
  yyin = fopen((examplesDir + "good_test3.jam").c_str(), "r");
  std::ifstream targetFile(examplesDir + "good_test3.expected");
  int token;
  std::string expected;
  while ((token = yylex()) != 0 && std::getline(targetFile, expected)) {
    ASSERT_EQ(expected, mapToToken(token));
  }

  if(token != 0) {
    ASSERT_TRUE(false);
  }

  fclose(yyin);
}

TEST(LexerGoodTest, CanRecognizeTokens4) {
  yyin = fopen((examplesDir + "good_test4.jam").c_str(), "r");
  std::ifstream targetFile(examplesDir + "good_test4.expected");
  int token;
  std::string expected;
  while ((token = yylex()) != 0 && std::getline(targetFile, expected)) {
    ASSERT_EQ(expected, mapToToken(token));
  }

  if(token != 0) {
    ASSERT_TRUE(false);
  }

  fclose(yyin);
}