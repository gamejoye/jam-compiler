%{
  #include <iostream>
  #include <vector>
  #include <string>
  #include "tree.h"
  #include "utilities.h"
    
  extern int yylex();
  void yyerror(const char *s) { std::cerr << "Error: " << s << std::endl; }
  extern Program* AstRoot;
  List<Class*> parseResults;
%}

%union {
  int boolean;
  Symbol symbol;
  Program* program;
  Class* class_;
  List<Class*> classes;
  Feature* feature;
  List<Feature*> features;
  Formal* formal;
  List<Formal*> formals;
  Expression* expression;
  List<Expression*> expressions;
  Statement* statement;
  List<Statement*> statements;
  Symbol errorMsg;
}

%token CLASS 258 IF 259 THEN 260 ELSE 261 FOR 262 IN 263
%token RETURN 264 EXTENDS 265 LET 266 VAR 267 NEW 268 ERROR 278
%token LE 274 RE 275 NE 276 EQ 277
%token<symbol> INT_CONST 269 BOOL_CONST 270 STR_CONST 271
%token<symbol> OBJECTID 272 TYPEID 273

%type <program> program
%type <class_> class
%type <classes> classList
%type <feature> feature
%type <features> notemptyFeatureList
%type <features> featureList
%type <formal> formal
%type <formals> notemptyFormalList
%type <formals> formalList
%type <expression> expression
%type <expressions> notemptyExpressionList
%type <expressions> expressionList
%type <statement> statement
%type <statements> notemptyStatementList
%type <statements> statementList

%left '='
%nonassoc LE RE NE EQ '<' '>'
%left '+' '-'
%left '*' '/'
%left '!'
%left '.'

%%
program: classList
{
  @$ = @1;
  AstRoot = new Program($1);
}
;

class:
CLASS TYPEID '{' featureList '}' {
  $$ = new Class(($2), new std::string("Object"), $4);
}
| CLASS TYPEID EXTENDS TYPEID '{' featureList '}' {
  $$ = new Class($2, $4, $6);
}
;

classList:
class ';' {
  $$ = singleClass($1);
} 
| class ';' classList {
  $$ = mergeClass(singleClass($1), $3);
}
;

feature:
LET OBJECTID ':' TYPEID {
  $$ = new Attribute($2, $4, new NilExpression());
}
| LET OBJECTID ':' TYPEID '=' expression {
  $$ = new Attribute($2, $4, $6);
}
| OBJECTID '(' formalList ')' ':' TYPEID '{' statementList '}' {
  $$ = new Method($1, $3, $6, $8);
}
;

notemptyFeatureList:
feature ';' notemptyFeatureList {
  $$ = mergeFeature(singleFeature($1), $3);
}
| feature ';' {
  $$ = singleFeature($1);
}
;

featureList:
notemptyFeatureList {
  $$ = $1;
} 
| {
  $$ = nilFeatures();
}
;

formal:
OBJECTID ':' TYPEID {
  $$ = new Formal($1, $3);
}
;

notemptyFormalList:
formal ',' notemptyFormalList {
  $$ = mergeFormal(singleFormal($1), $3);
}
| formal {
  $$ = singleFormal($1);
}
;

formalList:
notemptyFormalList {
  $$ = $1;
} 
| {
  $$ = nilFormals();
}
;

expression:
expression '+' expression {
  $$ = new PlusExpr($1, $3);
}
| expression '-' expression {
  $$ = new SubExpr($1, $3);
}
| expression '/' expression {
  $$ = new DivExpr($1, $3);
}
| expression '*' expression {
  $$ = new MulExpr($1, $3);
}
| expression EQ expression {
  $$ = new EqExpr($1, $3);
}
| expression NE expression {
  $$ = new NeExpr($1, $3);
}
| expression '<' expression {
  $$ = new LtExpr($1, $3);
}
| expression LE expression {
  $$ = new LeqExpr($1, $3);
}
| expression '>' expression {
  $$ = new RtExpr($1, $3);
}
| expression RE expression {
  $$ = new ReqExpr($1, $3);
}
| OBJECTID '=' expression {
  $$ = new AssignExpr($1, $3);
}
| '!' expression {
  $$ = new NotExpr($2);
}
| expression '.' OBJECTID '(' expressionList ')' {
  $$ = new DispatchExpr($1, $3, $5);
}
| NEW TYPEID {
  $$ = new NewExpr($2);
}
| '(' expression ')' {
  $$ = $2;
}
| OBJECTID {
  $$ = new ObjectExpr($1);
}
| INT_CONST {
  $$ = new IntExpr($1);
}
| BOOL_CONST {
  $$ = new BoolExpr($1);
}
| STR_CONST {
  $$ = new StrExpr($1);
}
;

notemptyExpressionList:
expression ',' notemptyExpressionList {
  $$ = mergeExpression(singleExpression($1), $3);
}
| expression {
  $$ = singleExpression($1);
}
;

expressionList:
notemptyExpressionList {
  $$ = $1;
}
| {
  $$ = nilExpressions();
}
;

statement:
RETURN expression {
  $$ = new ReturnStat($2);
}
| IF expression THEN '{' statementList '}' {
  $$ = new IfThenElseStat($2, $5, nilStatements());
}
| IF expression THEN '{' statementList '}' ELSE '{' statementList '}' {
  $$ = new IfThenElseStat($2, $5, $9);
}
| FOR '(' expressionList ';' expression ';' expressionList ')' IN '{' statementList '}' {
  $$ = new ForLoopStat($3, $5, $7, $11);
}
| VAR OBJECTID ':' TYPEID {
  $$ = new VarStat($2, $4, new NilExpression());
}
| VAR OBJECTID ':' TYPEID '=' expression {
  $$ = new VarStat($2, $4, $6);
}
;

notemptyStatementList:
statement ';' notemptyStatementList {
  $$ = mergeStatement(singleStatement($1), $3);
}
| statement ';' {
  $$ = singleStatement($1);
}
;

statementList:
notemptyStatementList {
  $$ = $1;
}
| {
  $$ = nilStatements();
}
;