%x  incl
%{

#include <iostream>
#include <fstream>
#include <string>
#include "modules/gambit/scanner.hpp"

#undef  YY_DECL
#define YY_DECL int Gambit::Scanner::yylex( Gambit::Parser::semantic_type * const lval, Gambit::Parser::location_type *loc ) 

using token = Gambit::Parser::token;

#define YY_NO_UNISTD_H
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="Gambit::Scanner"
%option noyywrap
%option c++
%option yylineno

digit ([0-9])
integer ({digit}+)
float_num ({digit}+\.{digit}+)

%%

%{
  yylval = lval;
%}

[ \t]*              /* skip whitespace */
\n                  {
                      return( token::T_NEWLINE );
                    }
([A-Z][a-zA-Z]*)+   {
                      yylval->sval = new std::string(yytext);
                      return( token::T_CONSTANT );
                    }
[_a-zA-Z\\?\\!]+    {
                      yylval->sval = new std::string(yytext);
                      return( token::T_IDENTIFIER ); 
                    }
{integer}           {
                      yylval->ival = (atoi(yytext));
                      return( token::T_INTEGER );
                    }
"="                 {
                      return( token::T_ASSIGN );
                    }
"::"                {
                      return( token::T_BIND );
                    }

%%