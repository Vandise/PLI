#ifndef __GAMBIT_LOCALDEFINITIONNODE
#define __GAMBIT_LOCALDEFINITIONNODE 1

#include "shared/ast/node.hpp"
#include "shared/datatypes.hpp"

namespace Gambit
{

  class LocalDefinitionNode : public AST::Node
  {

    private:
      std::string identifier;
      std::string className;
      AST::Node* valueNode = nullptr;

    public:

      LocalDefinitionNode(std::string className, std::string identifier, AST::Node* expression);
      ~LocalDefinitionNode();
      void compile();

  };

}

#endif