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
  virtual void checkProgram();
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
public:
  virtual void checkFeature() = 0;
  virtual bool isMethod() = 0;
  virtual void addToTable(std::string classname) = 0;
};

class Expression {
public:
  virtual Symbol checkExpr() = 0;
};

class Statement {
public:
  virtual void checkStat() = 0;
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
  void checkFeature();
  bool isMethod() { return true; }
  void addToTable(std::string classname);
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
  Expression *getInit() { return init; }
  void checkFeature();
  bool isMethod() { return false; }
  void addToTable(std::string classname);
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
  Symbol getName() { return name; }
  Symbol getType() { return type; }
  void addToTable(std::string classname);
};

class NilExpression : public Expression {
public:
  NilExpression() {}
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol checkExpr();
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
  Symbol getName() { return name; }
  Symbol checkExpr();
};

class NotExpr : public Expression {
protected:
  Expression *e1;

public:
  NotExpr(Expression *e1) { this->e1 = e1; }
  Symbol checkExpr();
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
  Symbol getCalleName() { return calleeName; }
  Symbol checkExpr();
};

class NewExpr : public Expression {
protected:
  Symbol type;

public:
  NewExpr(Symbol type) { this->type = type; }
  Symbol getType() { return type; }
  Symbol checkExpr();
};

class ObjectExpr : public Expression {
protected:
  Symbol name;
  Symbol getName() { return name; }

public:
  ObjectExpr(Symbol name) { this->name = name; }
  Symbol checkExpr();
};

class IntExpr : public Expression {
protected:
  Symbol val;

public:
  IntExpr(Symbol val) { this->val = val; }
  Symbol checkExpr();
};

class BoolExpr : public Expression {
protected:
  int val;

public:
  BoolExpr(int val) { this->val = val; }
  Symbol checkExpr();
};

class StrExpr : public Expression {
protected:
  Symbol val;

public:
  StrExpr(Symbol val) { this->val = val; }
  Symbol checkExpr();
};

class ReturnStat : public Statement {
protected:
  Expression *expr;

public:
  ReturnStat(Expression *expr) { this->expr = expr; }
  void checkStat();
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
  void checkStat();
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
  void checkStat();
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
  Symbol getName() { return name; }
  Symbol getType() { return type; }
  void checkStat();
  void addToTable(std::string classname);
};