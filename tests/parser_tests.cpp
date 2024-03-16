#include "tree.h"
#include "utilities.h"
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

extern int yyparse();
extern FILE *yyin;
extern Program *AstRoot;

static std::string examplesDir = "tests/parser_test_examples/";

TEST(ParserTest1, ClassesCanBeRecognized) {
  yyin = fopen((examplesDir + "good_test1.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);
  List<Class *> classes = AstRoot->getClasses();
  ASSERT_EQ(classes->size(), 2);
  fclose(yyin);
}

TEST(ParserTest2, ClassNameCanBeRecognizedSequentially) {
  const int N = 3;
  yyin = fopen((examplesDir + "good_test2.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);
  List<Class *> classes = AstRoot->getClasses();
  ASSERT_EQ(classes->size(), N);
  std::vector<std::string> correctNames = {"A", "B", "C"};
  for(int i = 0; i < N; i++) {
    std::string name = *classes->at(i)->getName();
    std::string shouldBe = correctNames[i];
    ASSERT_EQ(name, shouldBe);
  }
  fclose(yyin);
}

TEST(ParserTest3, ClassHasCorrectlyFeatures) {
  yyin = fopen((examplesDir + "good_test3.jam").c_str(), "r");
  int result = yyparse();
  ASSERT_EQ(result, 0);
  ASSERT_NE(AstRoot, nullptr);

  // only one main class
  List<Class *> classes = AstRoot->getClasses();
  ASSERT_EQ(classes->size(), 1);
  Class* MainClass = classes->at(0);
  ASSERT_EQ(*MainClass->getName(), "Main");

  // feature size
  List<Feature*> features = MainClass->getFeatures();
  ASSERT_EQ(features->size(), 4);

  // let x: Int;
  Attribute* attrX = (Attribute*)features->at(0);
  ASSERT_EQ(*attrX->getName(), "x");
  ASSERT_EQ(*attrX->getType(), "Int");

  // age(): Int { return 18; };
  Method* methodAge = (Method*)features->at(1);
  ASSERT_EQ(*methodAge->getName(), "age");
  ASSERT_EQ(*methodAge->getReturnType(), "Int");

  // name(): String { return "gamejoye"; };
  Method* methodName = (Method*)features->at(2);
  ASSERT_EQ(*methodName->getName(), "name");
  ASSERT_EQ(*methodName->getReturnType(), "String");

  // hobby(): String { return "coding"; };
  Method* methodHobby = (Method*)features->at(3);
  ASSERT_EQ(*methodHobby->getName(), "hobby");
  ASSERT_EQ(*methodHobby->getReturnType(), "String");
  fclose(yyin);
}