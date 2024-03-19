#pragma once

#include "tree.h"
#include <iostream>
#include <string>
#include <vector>

std::string mapToToken(int val);

List<Class *> mergeClass(List<Class *> classes1, List<Class *> classes2);
List<Class *> singleClass(Class *class1);

List<Feature *> mergeFeature(List<Feature *> features1,
                             List<Feature *> features2);
List<Feature *> singleFeature(Feature *feature1);
List<Feature *> nilFeatures();

List<Formal *> mergeFormal(List<Formal *> formals1, List<Formal *> formals2);
List<Formal *> singleFormal(Formal *formal1);
List<Formal *> nilFormals();

List<Expression *> mergeExpression(List<Expression *> expressions1,
                                   List<Expression *> expressions2);
List<Expression *> singleExpression(Expression *expression1);
List<Expression *> nilExpressions();

List<Statement *> mergeStatement(List<Statement *> statements1,
                                 List<Statement *> statements2);
List<Statement *> singleStatement(Statement *statement1);
List<Statement *> nilStatements();

extern int errors;
template <typename First, typename... Rest>
void semant_error(const First &first, const Rest &...rest) {
  std::cerr << first;
  if constexpr (sizeof...(rest) > 0) {
    semant_error(rest...);
  } else {
    errors++;
    std::cerr << std::endl;
  }
}