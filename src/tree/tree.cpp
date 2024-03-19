#include "tree.h"
#include "table.h"
#include "utilities.h"
#include <gtest/gtest.h>
#include <map>
#include <queue>
#include <set>

using AttrTable = SymbolTable<std::string, Symbol>;
using MethodTable = SymbolTable<std::string, Method *>;

extern StringTable stringtable;
extern IntTable inttable;
extern IdTable idtable;
extern int errors;
Program *AstRoot;

AttrTable attrtable;
std::map<std::string, MethodTable> methodtables;
Class *currentClass_global = nullptr;
Method *currentMethod_global = nullptr;
List<Class *> classes_global = nullptr;
std::map<std::string, Class *> mclasses;
bool debug = false;

Symbol Int, Bool, String, Object, Main, NoType, NoClass;

List<Class *> getExtendsLink(std::string subClassname);
bool checkTypeExtends(std::string subClassname, std::string superClassname);
Method *findMethodFromExtendsLink(std::string methodName,
                                  std::string classname);

void enableDebug() {
  std::stringstream buffer;
  std::streambuf *sbuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());
  std::cout.rdbuf(sbuf);
}

void prepareFreshStack() {
  if (debug)
    enableDebug();
  errors = 0;

  attrtable.clear();
  methodtables.clear();
  currentMethod_global = nullptr;
  currentClass_global = nullptr;
  classes_global = nullptr;
  mclasses.clear();
}

void initializeConstants() {
  Int = stringtable.add("Int");
  Bool = stringtable.add("Bool");
  String = stringtable.add("String");
  Object = stringtable.add("Object");
  Main = stringtable.add("Main");
  NoType = stringtable.add("__no_type");
  NoClass = stringtable.add("__no_class");
}

void initializeBasicClass() {
  // load Object Int Bool String classes
  Class *ObjectClass = new Class(Object, NoClass, nilFeatures());
  Class *IntClass = new Class(Int, Object, nilFeatures());
  Class *BoolClass = new Class(Bool, Object, nilFeatures());
  Class *StringClass = new Class(String, Object, nilFeatures());

  mclasses[*Object] = ObjectClass;
  mclasses[*Int] = IntClass;
  mclasses[*Bool] = BoolClass;
  mclasses[*String] = StringClass;
}

void checkClasses() {
  List<Class *> classes = classes_global;
  for (int i = 0; i < classes->size(); i++) {
    Class *class_ = classes->at(i);
    std::string name = *class_->getName();
    if (mclasses.find(name) != mclasses.end()) {
      semant_error("class name duplication");
    }
    mclasses[name] = class_;
  }

  if (mclasses.find(*Main) == mclasses.end()) {
    semant_error("Main class not defined");
  }

  // extends relation
  std::map<std::string, int> din;
  for (int i = 0; i < classes->size(); i++) {
    Class *class_ = classes->at(i);
    std::string name = *class_->getName();
    std::string parent = *class_->getParent();
    if (parent == *Int || parent == *Bool || parent == *String) {
      semant_error("classes can not extends \"", parent, "\"");
    }

    if (mclasses.find(parent) == mclasses.end()) {
      semant_error("class \"", parent, "\" is not defined");
    }
    din[parent]++;
    if (din.find(name) == din.end()) {
      din[name] = 0;
    }
  }

  // toposort check if the extends is legal
  std::queue<std::string> q;
  for (auto [classname, du] : din) {
    if (du == 0) {
      q.push(classname);
    }
  }
  while (!q.empty()) {
    std::string name = q.front();
    q.pop();
    std::string parent = *mclasses[name]->getParent();
    if (parent != *NoClass) {
      din[parent]--;
      if (din[parent] == 0) {
        q.push(parent);
      }
    }
  }
  for (auto [classname, du] : din) {
    if (du != 0) {
      semant_error("extends existing ring in class \"", classname, "\"");
    }
  }
}

void checkAllTypes() {
  // 1. load method
  for (auto [classname, cla] : mclasses) {
    currentClass_global = cla;
    List<Feature *> features = cla->getFeatures();
    methodtables[classname].enterScope();
    for (Feature *feature : *features) {
      if (!feature->isMethod())
        continue;
      Method *methodFeature = (Method *)feature;
      methodFeature->addToTable(classname);
    }
  }

  // 2. check method rewritten
  for (auto [classname, cla] : mclasses) {
    currentClass_global = cla;
    // 2.1 check all method feature
    List<Feature *> features = cla->getFeatures();
    List<Class *> parentClasses = getExtendsLink(classname);
    for (Feature *feature : *features) {
      if (!feature->isMethod())
        continue;
      Method *methodFeature = (Method *)feature;
      currentMethod_global = methodFeature;
      std::string methodName = *methodFeature->getName();
      for (Class *parentClass : *parentClasses) {
        std::string parentName = *parentClass->getName();
        Method *methodFeatureInParent =
            methodtables[parentName].lookup(methodName);
        if (methodFeatureInParent == nullptr)
          continue;
        List<Formal *> formals = methodFeature->getFormals();
        List<Formal *> formalsInParent = methodFeatureInParent->getFormals();
        if (formals->size() != formalsInParent->size()) {
          semant_error("invalid rewritten in class \"", classname, "\"");
        }
        for (int i = 0; i < formals->size(); i++) {
          Formal *formal = formals->at(i);
          Formal *formalInParent = formalsInParent->at(i);
          // For parameter types
          // the parent method parameter type must be a subclass of the subclass
          // method parameter type or itself (invert)
          if (!checkTypeExtends(*formalInParent->getType(),
                                *formal->getType())) {
            semant_error("invalid rewritten in class \"", classname, "\"");
          }
        }
        /// For return types
        // the parent method return type must be a superclass of the subclass
        // method return type or itself (covariant)
        if (!checkTypeExtends(*methodFeature->getReturnType(),
                              *methodFeatureInParent->getReturnType())) {
          semant_error("invalid rewritten in class \"", classname, "\"");
        }
      }
    }
  }

  // 3. check all types
  for (auto [classname, cla] : mclasses) {
    currentClass_global = cla;
    List<Class *> extendsLink = getExtendsLink(classname);
    // 3.1 load attr
    // from Object(root) to currentClass(leave)
    for (Class *parentClass : *extendsLink) {
      currentClass_global = cla;
      attrtable.enterScope();
      List<Feature *> features = parentClass->getFeatures();
      for (Feature *feature : *features) {
        if (feature->isMethod())
          continue;
        Attribute *attr = (Attribute *)feature;
        attr->addToTable(classname);
      }
    }

    // restore
    currentClass_global = cla;
    // 3.2 check attr or method
    List<Feature *> features = cla->getFeatures();
    for (Feature *feature : *features) {
      if (feature->isMethod()) {
        currentMethod_global = (Method *)(feature);
      }
      feature->checkFeature();
    }

    // 3.3 unload attr
    for (Class *parentClass : *extendsLink) {
      attrtable.exitScope();
    }
  }
}

void Program::checkProgram() {
  prepareFreshStack();
  classes_global = classes;
  initializeConstants();
  initializeBasicClass();
  if (errors) {
    std::cerr << "compliation terminated because of erros" << std::endl;
    return;
  }
  checkClasses();
  if (errors) {
    std::cerr << "compliation terminated because of erros" << std::endl;
    return;
  }
  checkAllTypes();
  if (errors) {
    std::cerr << "compliation terminated because of erros" << std::endl;
    return;
  }
}

void Method::addToTable(std::string classname) {
  // fetch from currentscope to handle rewritten case
  Method *existingMethod = methodtables[classname].lookup(*name);
  if (existingMethod) {
    semant_error("redefined method \"", *name, "\"");
    return;
  }
  methodtables[classname].addid(*name, this);
}

void Method::checkFeature() {
  // 1. check formals
  List<Formal *> formals = getFormals();
  std::set<std::string> existingNames;
  for (int i = 0; i < formals->size(); i++) {
    std::string name = *formals->at(i)->getName();
    std::string type = *formals->at(i)->getType();
    if (existingNames.find(name) != existingNames.end()) {
      semant_error("existing formalname \"", name, "\"");
    }
    existingNames.insert(name);
    if (mclasses.find(type) == mclasses.end()) {
      semant_error("unknow type \"", type, "\" in method \"", *getName(), "\"");
    }
  }

  // 2. check return type
  if (mclasses.find(*returnType) == mclasses.end()) {
    semant_error("unknow return type \"", *returnType, "\" in method \"",
                 *getName(), "\"");
  }

  // 3. add formals to attrtable
  attrtable.enterScope();
  for(int i = 0; i < formals->size(); i++) {
    formals->at(i)->addToTable(*currentClass_global->getName());
  }

  // 4. check statement list
  List<Statement *> statements = getStatements();
  for (int i = 0; i < statements->size(); i++) {
    Statement *statement = statements->at(i);
    statement->checkStat();
  }

  // 5. exitScope
  attrtable.exitScope();
}

void Attribute::addToTable(std::string classname) {
  Symbol existing = attrtable.lookup(*name);
  if (existing) {
    semant_error("redefined attr \"", *name, "\"");
    return;
  }
  attrtable.addid(*name, type);
}

void Attribute::checkFeature() {
  if (mclasses.find(*type) == mclasses.end()) {
    semant_error("unknow type \"", *type, "\"");
    return;
  }
  Symbol initType = init->checkExpr();
  if (*initType != *NoType && !checkTypeExtends(*initType, *type)) {
    semant_error("type \"", *initType, "\" can not assign to type \"", *type,
                 "\"");
  }
}

void Formal::addToTable(std::string classname) {
  Symbol existing = attrtable.lookupFromCurrentScope(*name);
  if(existing) {
    semant_error("formal \"", *name, "\" duplication");
  }
  attrtable.addid(*name, type);
}

Symbol NilExpression::checkExpr() { return NoType; }

Symbol PlusExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("plus operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Int;
}

Symbol SubExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("sub operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Int;
}

Symbol DivExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("div operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Int;
}

Symbol MulExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("mul operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Int;
}

Symbol EqExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int && *type1 != *Bool && *type1 != *String ||
      *type2 != *Int && *type2 != *Bool && *type2 != *String) {
    semant_error("equal operation type must basic type");
    // error recovery
    return Object;
  }
  if (*type1 != *type2) {
    semant_error("equal operation type must be the same");
    // error recovery
    return Object;
  }
  return Bool;
}

Symbol NeExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int && *type1 != *Bool && *type1 != *String ||
      *type2 != *Int && *type2 != *Bool && *type2 != *String) {
    semant_error("not equal operation type must basic type");
    // error recovery
    return Object;
  }
  if (*type1 != *type2) {
    semant_error("not equal operation type must be the same");
    // error recovery
    return Object;
  }
  return Bool;
}

Symbol LtExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("lt operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Bool;
}

Symbol LeqExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("leq operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Bool;
}

Symbol RtExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("rt operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Bool;
}

Symbol ReqExpr::checkExpr() {
  Symbol type1 = e1->checkExpr();
  Symbol type2 = e2->checkExpr();
  if (*type1 != *Int || *type2 != *Int) {
    semant_error("req operation type must be the Int type");
    // error recovery
    return Object;
  }
  return Bool;
}

Symbol AssignExpr::checkExpr() {
  Symbol existing = attrtable.lookup(*name);
  if (!existing) {
    semant_error("undefined variable or attribute \"", *name, "\"");
    // error recovery
    return Object;
  }
  Symbol type = expr->checkExpr();
  if (!checkTypeExtends(*type, *existing)) {
    semant_error("type \"", *type, "\" can not assign to type \"", *existing,
                 "\"");
    // error recovery
    return Object;
  }
  return existing;
}

Symbol NotExpr::checkExpr() {
  Symbol type = e1->checkExpr();
  if (*type != *Bool) {
    semant_error("not operation type must be the Bool type");
    return Object;
  }
  return Bool;
}

Symbol DispatchExpr::checkExpr() {
  Symbol exprType = expr->checkExpr();
  Method *existingMethod = findMethodFromExtendsLink(*calleeName, *exprType);
  if (!existingMethod) {
    semant_error("method \"", *calleeName, "\" does not existing for class \"",
                 *exprType, "\"");
    return Object;
  }
  // for all actual type must be satisfied:
  // actual.size() == formal.size() &&
  // actual <= formal (actual type is formal type 's subclass)
  if (actual->size() != existingMethod->getFormals()->size()) {
    semant_error("actual size must be the same as the formal size");
    return Object;
  }
  List<Symbol> actualTypes = new std::vector<Symbol>(0);
  for (int i = 0; i < actual->size(); i++) {
    actualTypes->push_back(actual->at(i)->checkExpr());
  }
  for (int i = 0; i < actual->size(); i++) {
    Symbol actualType = actualTypes->at(i);
    Symbol formalType = existingMethod->getFormals()->at(i)->getType();
    if (!checkTypeExtends(*actualType, *formalType)) {
      semant_error("actual type must be the subclass of formal type");
      return Object;
    }
  }
  return existingMethod->getReturnType();
}

Symbol NewExpr::checkExpr() {
  if (mclasses.find(*type) == mclasses.end()) {
    semant_error("unknow type \"", *type, "\"");
    return Object;
  }
  return type;
}

Symbol ObjectExpr::checkExpr() {
  Symbol existing = attrtable.lookup(*name);
  if (!existing) {
    semant_error("unknow variable or attribute \"", *name, "\"");
    return Object;
  }
  return existing;
}

Symbol IntExpr::checkExpr() { return Int; }

Symbol BoolExpr::checkExpr() { return Bool; }

Symbol StrExpr::checkExpr() { return String; }

void ReturnStat::checkStat() {
  Symbol exprType = expr->checkExpr();
  Symbol methodReturnType = currentMethod_global->getReturnType();
  if (!checkTypeExtends(*exprType, *methodReturnType)) {
    semant_error("invalid return type \"", *exprType, "\"");
  }
}

void IfThenElseStat::checkStat() {
  Symbol conditionType = condition->checkExpr();
  if (*conditionType != *Bool) {
    semant_error("if-then-else condition type must be Bool");
  }
  attrtable.enterScope();
  for (int i = 0; i < thenBlock->size(); i++) {
    thenBlock->at(i)->checkStat();
  }
  attrtable.exitScope();

  attrtable.enterScope();
  for (int i = 0; i < elseBlock->size(); i++) {
    elseBlock->at(i)->checkStat();
  }
  attrtable.exitScope();
}

void ForLoopStat::checkStat() {
  for (int i = 0; i < start->size(); i++) {
    start->at(i)->checkExpr();
  }
  Symbol conditionType = condition->checkExpr();
  if (*conditionType != *Bool) {
    semant_error("for-loop condition type must be Bool");
  }
  for (int i = 0; i < next->size(); i++) {
    next->at(i)->checkExpr();
  }
  attrtable.enterScope();
  for (int i = 0; i < body->size(); i++) {
    body->at(i)->checkStat();
  }
  attrtable.exitScope();
}

void VarStat::checkStat() {
  Symbol initType = init->checkExpr();
  // if(attrtable.lookup())
  if (*initType != *NoType && !checkTypeExtends(*initType, *type)) {
    semant_error("type \"", *initType, "\" can not assign to type \"", *type,
                 "\"");
  }
  addToTable(*currentClass_global->getName());
}

void VarStat::addToTable(std::string classname) {
  Symbol existing = attrtable.lookupFromCurrentScope(*name);
  if(existing) {
    semant_error("variable \"", *name, "\" duplication");
  }
  attrtable.addid(*name, type);
}

List<Class *> getExtendsLink(std::string subClassname) {
  List<Class *> link = new std::vector<Class *>();
  if (mclasses.find(subClassname) == mclasses.end())
    return link;
  Class *currentClass = mclasses[subClassname];
  while (*currentClass->getParent() != *NoClass) {
    link->push_back(currentClass);
    currentClass = mclasses[*currentClass->getParent()];
  }
  std::reverse(link->begin(), link->end());
  return link;
}
bool checkTypeExtends(std::string subClassname, std::string superClassname) {
  List<Class *> link = getExtendsLink(subClassname);
  for (Class *class_ : *link) {
    if (*class_->getName() == superClassname)
      return true;
  }
  return false;
}

Method *findMethodFromExtendsLink(std::string methodName,
                                  std::string classname) {
  List<Class *> link = getExtendsLink(classname);
  for (int i = link->size() - 1; i >= 0; i--) {
    Method *existing = methodtables[classname].lookup(methodName);
    if (existing)
      return existing;
  }
  return nullptr;
}