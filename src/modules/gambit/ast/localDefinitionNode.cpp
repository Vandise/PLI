#include <iostream>
#include "dev/debugnew/debug_new.h"
#include "modules/gambit/ast/localDefinitionNode.hpp"

Gambit::LocalDefinitionNode::LocalDefinitionNode(std::string className, std::string identifier, AST::Node* expression)
{
  this->identifier = identifier;
  this->className = className;
  this->valueNode = expression;
}

Gambit::LocalDefinitionNode::~LocalDefinitionNode()
{
  if (this->valueNode != nullptr)
  {
    delete(this->valueNode);
  }
}

void
Gambit::LocalDefinitionNode::compile(Generator::ByteCode* bcGenerator)
{
  bcGenerator->setState(LOCALDEFINITION);
  if (this->valueNode != nullptr)
  {
    this->valueNode->compile(bcGenerator);
  }
  bcGenerator->emit->setLocal(this->className, this->identifier);
  bcGenerator->popState();
}