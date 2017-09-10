#ifndef __GAMBIT_LITERALNODE
#define __GAMBIT_LITERALNODE 1

#include <string>
#include "shared/ast/node.hpp"
#include "shared/datatypes.hpp"

namespace Gambit
{

  class LiteralNode : public AST::Node
  {

    private:
      DATATYPE type;
      int intValue;
      std::string strValue;

    public:

      LiteralNode(int value, DATATYPE type);
      LiteralNode(std::string value, DATATYPE type);
      ~LiteralNode();
      void compile(Generator::ByteCode* bcGenerator);

  };

}

#endif