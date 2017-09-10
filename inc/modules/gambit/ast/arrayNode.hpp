#ifndef __GAMBIT_ARRAYNODE
#define __GAMBIT_ARRAYNODE 1

#include "shared/ast/node.hpp"
#include "shared/ast/tree.hpp"
#include "shared/datatypes.hpp"

namespace Gambit
{

  class ArrayNode : public AST::Node
  {

    private:
      AST::Tree* values = nullptr;

    public:

      ArrayNode(AST::Tree* expression);
      ~ArrayNode();
      void compile(Generator::ByteCode* bcGenerator);

  };

}

#endif