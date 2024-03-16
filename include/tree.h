#pragma once

#include <string>
#include <vector>

class Program;
class Class;
class Feature;
class Formal;
class Expression;
class Statement;

using Symbol = std::string *;
template <typename T> using List = std::vector<T> *;

class Program {
protected:
  List<Class *> classes;

public:
  Program() {}
  Program(List<Class *> classes) { this->classes = classes; }
  List<Class *> getClasses() { return classes; }
};

extern Program *AstRoot;

class Class {
protected:
  Symbol name;
  Symbol parent;
  List<Feature *> features;

public:
  Class(Symbol name, Symbol parent, List<Feature *> features) {
    this->name = name;
    this->parent = parent;
    this->features = features;
  }
  Symbol getName() { return name; }
  Symbol getParent() { return parent; }
  List<Feature *> getFeatures() { return features; }
};

class Feature {
  // public:
  //   virtual Symbol checkFeature() = 0;
};

class Expression {
  // public:
  //   virtual Symbol checkExpr() = 0;
};

class Statement {
  // public:
  //   virtual void checkStat() = 0;
};

class Method : public Feature {
protected:
  Symbol name;
  List<Formal *> formals;
  Symbol returnType;
  List<Statement *> statements;

public:
  Method(Symbol name, List<Formal *> formals, Symbol returnType,
         List<Statement *> statements) {
    this->name = name;
    this->formals = formals;
    this->returnType = returnType;
    this->statements = statements;
  }
  Symbol getName() { return name; }
  List<Formal *> getFormals() { return formals; }
  Symbol getReturnType() { return returnType; }
  List<Statement *> getStatements() { return statements; }
};

class Attribute : public Feature {
protected:
  Symbol name;
  Symbol type;
  Expression *init;

public:
  Attribute(Symbol name, Symbol type, Expression *init) {
    this->name = name;
    this->type = type;
    this->init = init;
  }
  Symbol getName() { return name; }
  Symbol getType() { return type; }
  Expression* getInit() { return init; }
};

class Formal {
protected:
  Symbol name;
  Symbol type;

public:
  Formal(Symbol name, Symbol type) {
    this->name = name;
    this->type = type;
  }
};

class NilExpression : public Expression {
public:
  NilExpression() {}
};

class PlusExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  PlusExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class SubExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  SubExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class DivExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  DivExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class MulExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  MulExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class EqExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  EqExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class NeExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  NeExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class LtExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  LtExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class LeqExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  LeqExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class RtExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  RtExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class ReqExpr : public Expression {
protected:
  Expression *e1;
  Expression *e2;

public:
  ReqExpr(Expression *e1, Expression *e2) {
    this->e1 = e1;
    this->e2 = e2;
  }
};

class AssignExpr : public Expression {
protected:
  Symbol name;
  Expression *expr;

public:
  AssignExpr(Symbol name, Expression *expr) {
    this->name = name;
    this->expr = expr;
  }
};

class NotExpr : public Expression {
protected:
  Expression *e1;

public:
  NotExpr(Expression *e1) { this->e1 = e1; }
};

class DispatchExpr : public Expression {
protected:
  Expression *expr;
  Symbol calleeName;
  List<Expression *> actual;

public:
  DispatchExpr(Expression *expr, Symbol calleeName, List<Expression *> actual) {
    this->expr = expr;
    this->calleeName = calleeName;
    this->actual = actual;
  }
};

class NewExpr : public Expression {
protected:
  Symbol type;

public:
  NewExpr(Symbol type) { this->type = type; }
};

class ObjectExpr : public Expression {
protected:
  Symbol name;

public:
  ObjectExpr(Symbol name) { this->name = name; }
};

class IntExpr : public Expression {
protected:
  Symbol val;

public:
  IntExpr(Symbol val) { this->val = val; }
};

class BoolExpr : public Expression {
protected:
  Symbol val;

public:
  BoolExpr(Symbol val) { this->val = val; }
};

class StrExpr : public Expression {
protected:
  Symbol val;

public:
  StrExpr(Symbol val) { this->val = val; }
};

class ReturnStat : public Statement {
protected:
  Expression *expr;

public:
  ReturnStat(Expression *expr) { this->expr = expr; }
};

class IfThenElseStat : public Statement {
protected:
  Expression *condition;
  List<Statement *> thenBlock;
  List<Statement *> elseBlock;

public:
  IfThenElseStat(Expression *condition, List<Statement *> thenBlock,
                 List<Statement *> elseBlock) {
    this->condition = condition;
    this->thenBlock = thenBlock;
    this->elseBlock = elseBlock;
  }
};

class ForLoopStat : public Statement {
protected:
  List<Expression *> start;
  Expression *condition;
  List<Expression *> next;
  List<Statement *> body;

public:
  ForLoopStat(List<Expression *> start, Expression *condition,
              List<Expression *> next, List<Statement *> body) {
    this->start = start;
    this->condition = condition;
    this->next = next;
    this->body = body;
  }
};

class VarStat : public Statement {
protected:
  Symbol name;
  Symbol type;
  Expression *init;

public:
  VarStat(Symbol name, Symbol type, Expression *init) {
    this->name = name;
    this->type = type;
    this->init = init;
  }
};