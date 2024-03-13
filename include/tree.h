#include <string>
#include <vector>

class Program {};

class Class {
protected:
  std::string name;
  std::string parent;
  std::vector<Feature *> features;

public:
  Class(std::string name, std::string parent, std::vector<Feature *> features) {
    this->name = name;
    this->parent = parent;
    this->features = features;
  }
};

class Feature {
  // public:
  //   virtual void checkFeature() = 0;
};

class Expression {
// public:
//   virtual std::string checkExpr() = 0;
};

class Statement {
// public:
//   virtual void checkStat() = 0;
};

class Method : public Feature {
protected:
  std::string name;
  std::vector<Formal *> formals;
  std::string returnType;
  std::vector<Statement *> statements;

public:
  Method(std::string name, std::vector<Formal *> formals,
         std::string returnType, std::vector<Statement *> statements) {
    this->name = name;
    this->formals = formals;
    this->returnType = returnType;
    this->statements = statements;
  }
};

class Attribute : public Feature {
protected:
  std::string name;
  std::string type;
  Expression *init;

public:
  Attribute(std::string name, std::string type, Expression *init) {
    this->name = name;
    this->type = type;
    this->init = init;
  }
};

class Formal {
protected:
  std::string name;
  std::string type;

public:
  Formal(std::string name, std::string type) {
    this->name = name;
    this->type = type;
  }
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

class NotExpr : public Expression {
protected:
  Expression *e1;

public:
  NotExpr(Expression *e1) { this->e1 = e1; }
};

class DispatchExpr : public Expression {
protected:
  Expression *expr;
  std::string calleeName;
  std::vector<Expression *> actual;

public:
  DispatchExpr(Expression *expr, std::string calleeName,
               std::vector<Expression *> actual) {
    this->expr = expr;
    this->calleeName = calleeName;
    this->actual = actual;
  }
};

class NewExpr : public Expression {
protected:
  std::string type;

public:
  NewExpr(std::string type) { this->type = type; }
};

class IntExpr : public Expression {
protected:
  std::string val;

public:
  IntExpr(std::string val) { this->val = val; }
};

class BoolExpr : public Expression {
protected:
  std::string val;

public:
  BoolExpr(std::string val) { this->val = val; }
};

class StringExpr : public Expression {
protected:
  std::string val;

public:
  StringExpr(std::string val) { this->val = val; }
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
  Statement *thenBlock;
  Statement *elseBlock;

public:
  IfThenElseStat(Expression *condition, Statement *thenBlock,
                 Statement *elseBlock) {
    this->condition = condition;
    this->thenBlock = thenBlock;
    this->elseBlock = elseBlock;
  }
};

class ForLoopStat : public Statement {
protected:
  Statement *start;
  Expression *condition;
  Expression *next;
  Statement *body;

public:
  ForLoopStat(Statement *start, Expression *condition, Expression *next,
              Statement *body) {
    this->start = start;
    this->condition = condition;
    this->next = next;
    this->body = body;
  }
};

class LetStat : public Statement {
protected:
  std::string name;
  std::string type;
  Expression *init;

public:
  LetStat(std::string name, std::string type, Expression *init) {
    this->name = name;
    this->type = type;
    this->init = init;
  }
};