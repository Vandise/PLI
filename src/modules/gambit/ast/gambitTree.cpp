#include "modules/gambit/ast/gambitTree.hpp"
#include <iostream>
#include "dev/debugnew/debug_new.h"

Gambit::Tree::Tree(std::vector<AST::Node*> nodes)
{
  this->nodes = nodes;
}

Gambit::Tree::~Tree()
{

}

void
Gambit::Tree::pushNodes(std::vector<AST::Node*> nodes)
{

}

void
Gambit::Tree::pushNode(AST::Node *node)
{
  this->nodes.push_back(node);
}

int
Gambit::Tree::treeSize()
{
  return this->nodes.size();
}

void
Gambit::Tree::compile(Generator::ByteCode* bcGenerator)
{
  for (auto &n : nodes)
  {
    n->compile(bcGenerator);
  }
}