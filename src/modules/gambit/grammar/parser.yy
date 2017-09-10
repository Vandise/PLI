%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Gambit}
%define parser_class_name {Parser}

%code requires {

  #include <vector>
  #include <string>
  #include "dev/debugnew/debug_new.h"
  #include "shared/datatypes.hpp"

  namespace AST
  {
    class Tree;
    class Node;
  }

  namespace Gambit {
    class Scanner;
    class Tree;
    class LiteralNode;
    class Driver;
    class LocalDefinitionNode;
  }
}

%parse-param { Gambit::Scanner &scanner }
%parse-param { Gambit::Driver  &driver  }

%code {

  #include "modules/gambit/driver.hpp"
  #include "modules/gambit/scanner.hpp"
  #include "modules/gambit/ast/gambitTree.hpp"
  #include "modules/gambit/ast/literalNode.hpp"
  #include "modules/gambit/ast/localDefinitionNode.hpp"

  #undef yylex
  #define yylex scanner.yylex

}

%locations

%token                   END          0  "end of file"
%token       <ival>      T_INTEGER
%token       <sval>      T_STRING
%token       <sval>      T_CONSTANT
%token       <sval>      T_IDENTIFIER
%token                   T_BIND
%token                   T_ASSIGN
%token                   T_NEWLINE

%union {
  int ival;
  std::string *sval;
  DATATYPE type;
  AST::Tree *tree;
  AST::Node *node;
}

%type <tree>    Expressions
%type <node>    Expression Literals LocalDefinition

%%

root:
  END
  | Expressions END                     { driver.setTree($1); }
  ;

Expressions:
  Expression                        {
                                      std::vector<AST::Node *> nodes;
                                      nodes.push_back($1);
                                      $$ = new Gambit::Tree(nodes);
                                      
                                    }
  | Expressions Terminator Expression {
                                        $1->pushNode($3);
                                        $$ = $1;
                                      }

  | Expressions Terminator          { $$ = $1; }
  ;

Expression:
    Literals
  | LocalDefinition
  ;

Literals:
  T_INTEGER                           {
                                        $$ = new Gambit::LiteralNode($1, INTEGER);
                                      }
  | T_STRING                          {
                                        $$ = new Gambit::LiteralNode(*$1, STRING);
                                        delete($1);
                                      }
  ;

LocalDefinition:
    T_CONSTANT T_BIND T_IDENTIFIER    {
                                        $$ = new Gambit::LocalDefinitionNode(*$1, *$3, nullptr);
                                        delete($1);
                                        delete($3);
                                      }
  | T_CONSTANT T_BIND T_IDENTIFIER T_ASSIGN Expression   
                                      {
                                        $$ = new Gambit::LocalDefinitionNode(*$1, *$3, $5);
                                        delete($1);
                                        delete($3);
                                      }
  ;

Terminator:
    T_NEWLINE
  ;

%%


void
Gambit::Parser::error(const location_type& l, const std::string& m )
{
  std::cout << m << std::endl;
}