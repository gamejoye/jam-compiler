#include <string>

#define YYTOKENTYPE
enum yytokentype {
  CLASS = 258,
  IF = 259,
  THEN = 260,
  ELSE = 261,
  FOR = 262,
  IN = 263,
  RETURN = 264,
  EXTENDS = 265,
  LET = 266,
  NEW = 267,
  INT_CONST = 268,
  BOOL_CONST = 269,
  STR_CONST = 270,
  OBJECTID = 271,
  TYPEID = 272,
  LE = 273,
  RE = 274,
  NE = 275,
  EQ = 276,
  ERROR = 277,
};

#define CLASS 258
#define IF 259
#define THEN 260
#define ELSE 261
#define FOR 262
#define IN 263
#define RETURN 264
#define EXTENDS 265
#define LET 266
#define NEW 267
#define INT_CONST 268
#define BOOL_CONST 269
#define STR_CONST 270
#define OBJECTID 271
#define TYPEID 272
#define LE 273
#define RE 274
#define NE 275
#define EQ 276
#define ERROR 277

typedef union YYSTYPE {
  int boolean;
  std::string symbol;
  std::string errorMsg;
};