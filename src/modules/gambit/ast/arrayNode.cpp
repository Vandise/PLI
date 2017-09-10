#include "modules/gambit/ast/arrayNode.hpp"
#include <iostream>
#include "dev/debugnew/debug_new.h"

Gambit::ArrayNode::ArrayNode(AST::Tree* expression)
{
  this->values = expression;
}

Gambit::ArrayNode::~ArrayNode()
{
  delete(this->values);
}

void
Gambit::ArrayNode::compile(Generator::ByteCode* bcGenerator)
{
  bcGenerator->setState(ARRAYDEFINITION);
  if (this->values != nullptr)
  {
    this->values->compile(bcGenerator);
  }
  bcGenerator->emit->pushArray(this->values->treeSize());
  bcGenerator->popState();
}