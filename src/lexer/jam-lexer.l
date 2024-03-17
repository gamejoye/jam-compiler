%{
  #include <iostream>
  #include "utilities.h"
  #include "table.h"
  #include "jam-parser.tab.hh"

  extern YYSTYPE yylval;
  extern StringTable stringtable;
  extern IntTable inttable;
  extern IdTable idtable;
%}

%Start        STRING

%%
<INITIAL>\" {
  BEGIN STRING;
  yymore();
}

 /* 字符串常量遇见 文件结束符 */
<STRING><<EOF>> {
  yylval.errorMsg = stringtable.add("EOF in string constant");
  BEGIN 0;
  yyrestart(yyin);
  return ERROR;
}
  /* \ " 回车 交给后面处理 */
<STRING>[^\\\"\n]* { yymore(); }

  /* 普通转义字符 */
<STRING>\\[^\n] { yymore(); }

 /* 字符串常量遇见回车 */
<STRING>"\n" {
  yylval.errorMsg = stringtable.add("Unterminated string constant");
  BEGIN 0;
  return ERROR;
}

<STRING>\" {
  std::string input(yytext, yyleng);
  input = input.substr(1, yyleng - 2);
  std::string output;
  std::cout << input << std::endl;

  for(int i = 0; i < input.size(); i++) {
    if(input[i] == '\0') {
      BEGIN 0;
      yylval.errorMsg = stringtable.add("string contains null character");
      return ERROR;
    }
    if(input[i] == '\\') {
      char next_ch = input[i + 1];
      char real_next_ch;
      switch (next_ch) {
        case 'n':
          real_next_ch= '\n';
          break;
        case 't':
          real_next_ch= '\t';
          break;
        case 'b':
          real_next_ch= '\b';
          break;
        case 'f':
          real_next_ch= '\f';
          break;
        default:
          real_next_ch = next_ch;
      }
      output.push_back(real_next_ch);
      i++;
      continue;
    }
    output.push_back(input[i]);
  }
  if(output.size() > 1024) {
    BEGIN 0;
    yylval.errorMsg = stringtable.add("string constant to long");
    return ERROR;
  }
  yylval.symbol = stringtable.add(output);
  BEGIN 0;
  return STR_CONST;
}

"\n" {
  // curr_lineno++;
}

[ \t\r\f]+ {
  // blank
}

"true" {
  return BOOL_CONST;
}

"false" {
  return BOOL_CONST;
}

"Class" {
  return CLASS;
}

"if" {
  return IF;
}

"then" {
  return THEN;
}

"else" {
  return ELSE;
}

"for" {
  return FOR;
}

"in" {
  return IN;
}

"return" {
  return RETURN;
}

"extends" {
  return EXTENDS;
}

"let" {
  return LET;
}

"var" {
  return VAR;
}

"new" {
  return NEW;
}

[0-9]+ {
  return INT_CONST;
}

[a-z][A-Za-z0-9_]* {
  yylval.symbol = idtable.add(yytext);
  return OBJECTID;
}

[A-Z][A-za-z0-9_]* {
  yylval.symbol = idtable.add(yytext);
  return TYPEID;
}

"<=" {
  return LE;
}

">=" {
  return RE;
}

"!=" {
  return NE;
}

"==" {
  return EQ;
}

"+" {
  return int('+');
}

"-" {
  return int('-');
}

"*" {
  return int('*');
}

"/" {
  return int('/');
}

"<" {
  return int('<');
}

">" {
  return int('>');
}

"=" {
  return int('=');
}

"." {
  return int('.');
}

";" {
  return int(';');
}

":" {
  return int(':');
}

"!" {
  return int('!');
}

"{" { 
  return int('{'); 
}

"}" { 
  return int('}'); 
}

"(" { 
  return int('(');
}

")" { 
  return int(')'); 
}

"," { 
  return int(',');
}

[^"\n"] {
  yylval.errorMsg = stringtable.add(yytext);
  return ERROR;
}

%%

int yywrap() {
  return 1;
}