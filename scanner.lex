%{
/* Declarations section */
#include <stdio.h>
#include "Nodes.cpp"
#include "hw3_output.hpp"
#include "parser.tab.hpp"

%}

%option yylineno
%option noyywrap



whitespace		([\t\r\n ])
colon			([:])
sc				([;])
comma			([,])
lparen			([(])
rparen			([)])
lbrace			([{])
rbrace          ([}])
assign          ([=])
equality        (==|!=)
relational      (<|>|<=|>=)
comment         (\/\/[^\r\n]*(\r|\n|\r\n)?)
id             ([a-zA-Z][a-zA-Z0-9]*)
num            (0|[1-9][0-9]*)
string         (\"([^\n\r\"\\]|\\[rnt"\\])+\")



%%
void                        {yylval = new Type(string("VOID")); return VOID;}
int                         {yylval = new Type(string("INT"));return INT;}
byte                         {yylval = new Type(string("BYTE"));return BYTE;}
b                            {yylval = new Type(string("BYTE"));return B;}
bool                        {yylval = new Type(string("BOOL"));return BOOL;}
and                         return AND;
or                          return OR;
not                         return NOT;
true                          {yylval = new Type(string("BOOL"));return TRUE;}
false                         {yylval = new Type(string("BOOL"));return FALSE;}
return                      return RETURN;
if                          return IF;
else                        return ELSE;
while                       return WHILE;
break                       return BREAK;
continue                    return CONTINUE;
switch						return SWITCH;
case						return CASE;
default						return DEFAULT;
{colon}						return COLON;
{sc}						return SC;
{comma}                     return COMMA;
{lparen}                    return LPAREN;
{rparen}                    return RPAREN;
{lbrace}                    return LBRACE;
{rbrace}                    return RBRACE;
{assign}                    return ASSIGN;
{relational}                return RELATION_RELOP;
{equality}                  return EQUALITY_RELOP;
[\*\/]						{yylval = new BinOp(string(yytext)); return MULT_DIV ;}
[\+-]                       {yylval = new BinOp(string(yytext)); return PLUS_MINUS;}
{id}                        {yylval = new Id(string(yytext));return ID;}
{num}                       {yylval = new Num(string(yytext));return NUM;}
{string}                    {yylval = new Type(string("STRING"));return STRING;}
{comment}                   ;
{whitespace}                ;
.                           {output::errorLex(yylineno);exit(0);};
%%