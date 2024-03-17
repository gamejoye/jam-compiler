#include "tree.h"
#include <string>
#include <vector>

std::string mapToToken(int val) {
  switch (val) {
  case 258: {
    return "CLASS";
  }
  case 259: {
    return "IF";
  }
  case 260: {
    return "THEN";
  }
  case 261: {
    return "ELSE";
  }
  case 262: {
    return "FOR";
  }
  case 263: {
    return "IN";
  }
  case 264: {
    return "RETURN";
  }
  case 265: {
    return "EXTENDS";
  }
  case 266: {
    return "LET";
  }
  case 267: {
    return "VAR";
  }
  case 268: {
    return "NEW";
  }
  case 269: {
    return "INT_CONST";
  }
  case 270: {
    return "BOOL_CONST";
  }
  case 271: {
    return "STR_CONST";
  }
  case 272: {
    return "OBJECTID";
  }
  case 273: {
    return "TYPEID";
  }
  case 274: {
    return "LE";
  }
  case 275: {
    return "RE";
  }
  case 276: {
    return "NE";
  }
  case 277: {
    return "EQ";
  }
  case 278: {
    return "ERROR";
  }
  default: {
    return std::string(1, char(val));
  }
  }
  return "";
}

// TODO 考虑泛型

List<Class *> mergeClass(List<Class *> classes1, List<Class *> classes2) {
  List<Class *> merged = new std::vector<Class *>;
  for (auto class_ : *classes1)
    merged->push_back(class_);
  for (auto class_ : *classes2)
    merged->push_back(class_);
  return merged;
}
List<Class *> singleClass(Class *class1) {
  return new std::vector<Class *>(1, class1);
}

List<Feature *> mergeFeature(List<Feature *> features1,
                             List<Feature *> features2) {
  List<Feature *> merged = new std::vector<Feature *>;
  for (auto feature : *features1)
    merged->push_back(feature);
  for (auto feature : *features2)
    merged->push_back(feature);
  return merged;
}
List<Feature *> singleFeature(Feature *feature1) {
  return new std::vector<Feature *>(1, feature1);
}
List<Feature *> nilFeatures() { return new std::vector<Feature *>(0); }

List<Formal *> mergeFormal(List<Formal *> formals1, List<Formal *> formals2) {
  List<Formal *> merged = new std::vector<Formal *>;
  for (auto formal : *formals1)
    merged->push_back(formal);
  for (auto formal : *formals2)
    merged->push_back(formal);
  return merged;
}
List<Formal *> singleFormal(Formal *formal1) {
  return new std::vector<Formal *>(1, formal1);
}
List<Formal *> nilFormals() { return new std::vector<Formal *>(0); }

List<Expression *> mergeExpression(List<Expression *> expressions1,
                                   List<Expression *> expressions2) {
  List<Expression *> merged = new std::vector<Expression *>;
  for (auto expr : *expressions1)
    merged->push_back(expr);
  for (auto expr : *expressions2)
    merged->push_back(expr);
  return merged;
}
List<Expression *> singleExpression(Expression *expression1) {
  return new std::vector<Expression *>(1, expression1);
}
List<Expression *> nilExpressions() { return new std::vector<Expression *>(0); }

List<Statement *> mergeStatement(List<Statement *> statements1,
                                 List<Statement *> statements2) {
  List<Statement *> merged = new std::vector<Statement *>;
  for (auto stat : *statements1)
    merged->push_back(stat);
  for (auto stat : *statements2)
    merged->push_back(stat);
  return merged;
}
List<Statement *> singleStatement(Statement *statement1) {
  return new std::vector<Statement *>(1, statement1);
}
List<Statement *> nilStatements() { return new std::vector<Statement *>(0); }