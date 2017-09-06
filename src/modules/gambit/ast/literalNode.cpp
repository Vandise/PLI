#include "modules/gambit/ast/literalNode.hpp"
#include <iostream>
#include "dev/debugnew/debug_new.h"

Gambit::LiteralNode::LiteralNode(int value, DATATYPE type)
{
  this->type = type;
  this->intValue = value;
}

Gambit::LiteralNode::~LiteralNode()
{

}

void
Gambit::LiteralNode::compile(Generator::ByteCode* bcGenerator)
{
  switch(this->type)
  {
    case INTEGER:
      bcGenerator->emit->pushInteger(this->intValue);
      break;
    default:
      break;
  }
}