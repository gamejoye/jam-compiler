#include "tree.h"
#include "utilities.h"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

extern int yyparse();
extern FILE *yyin;
extern Program *AstRoot;
extern int errors;
extern bool debug;

static std::string examplesDir = "tests/typesystem_test_examples/";

void reset(std::string message) {
  std::cerr << message << std::endl;
  debug = true;
}

TEST(TypeSystemBadTest1, CanRecognizeUnknowError) {
  reset("TypeSystemBadTest1 debug messages: ");
  yyin = fopen((examplesDir + "bad_test1.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);

  AstRoot->checkProgram();
  ASSERT_NE(errors, 0);

  fclose(yyin);
}

TEST(TypeSystemBadTest2, RewrittenCanBeRecognizedBecauseOfReturnTypeIsInvalid) {
  reset("TypeSystemBadTest2 debug messages: ");
  yyin = fopen((examplesDir + "bad_test2.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);

  AstRoot->checkProgram();
  ASSERT_NE(errors, 0);

  fclose(yyin);
}

TEST(TypeSystemTest3, RewrittenCanBeRecognizedBecauseOfFormalTypeIsInvalid) {
  reset("TypeSystemTest3 debug messages: ");
  yyin = fopen((examplesDir + "bad_test3.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);

  AstRoot->checkProgram();
  ASSERT_NE(errors, 0);

  fclose(yyin);
}

TEST(TypeSystemTest4, CanRecognizedExtendsLinkCircle) {
  reset("TypeSystemTest4 debug messages: ");
  yyin = fopen((examplesDir + "bad_test4.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);

  AstRoot->checkProgram();
  ASSERT_NE(errors, 0);

  fclose(yyin);
}

TEST(TypeSystemTest5, CanRecognizedExitedScopeVariableError) {
  reset("TypeSystemTest5 debug messages: ");
  yyin = fopen((examplesDir + "bad_test5.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);

  AstRoot->checkProgram();
  ASSERT_NE(errors, 0);

  fclose(yyin);
}

TEST(TypeSysmGoodTests, CanRecognizedCorrectly) {
  const int N = 7;
  for (int i = 1; i <= N; i++) {
    reset("");
    yyin = fopen(
        (examplesDir + "good_test" + std::to_string(i) + ".jam").c_str(), "r");
    int result = yyparse();
    ASSERT_EQ(result, 0);
    ASSERT_NE(AstRoot, nullptr);

    AstRoot->checkProgram();
    ASSERT_EQ(errors, 0);

    fclose(yyin);
  }
}
