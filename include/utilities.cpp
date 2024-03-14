#include <string>
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
      return "NEW";
    }
    case 268: {
      return "INT_CONST";
    }
    case 269: {
      return "BOOL_CONST";
    }
    case 270: {
      return "STR_CONST";
    }
    case 271: {
      return "OBJECTID";
    }
    case 272: {
      return "TYPEID";
    }
    case 273: {
      return "LE";
    }
    case 274: {
      return "RE";
    }
    case 275: {
      return "NE";
    }
    case 276: {
      return "EQ";
    }
    case 277: {
      return "ERROR";
    }
    default: {
      return std::string(1, char(val));
    }
  }
  return "";
}