#include "generator/instructionEmitter.hpp"
#include "generator/instructions.hpp"
#include "dev/debugnew/debug_new.h"

Generator::InstructionEmitter::InstructionEmitter(Generator::ByteCode* bcGenerator)
{
  this->bcGenerator = bcGenerator;
}

Generator::InstructionEmitter::~InstructionEmitter()
{
  //delete(this->bcGenerator);
  this->bcGenerator = nullptr;
}

void
Generator::InstructionEmitter::pushInteger(int value)
{
  std::string instructions;
  EMIT_1(PUSH_INTEGER, std::to_string(value));
  if (bcGenerator->getState() == DEFAULT)
  {
    EMIT_0(POP);
  }
  this->bcGenerator->pushBuffer(instructions);
}

void
Generator::InstructionEmitter::pushString(std::string value)
{
  std::string instructions;
  int x = this->bcGenerator->addLiteral(value);
  EMIT_1(PUSH_STRING, std::to_string(x));
  if (bcGenerator->getState() == DEFAULT)
  {
    EMIT_0(POP);
  }
  this->bcGenerator->pushBuffer(instructions);
}

void
Generator::InstructionEmitter::setLocal(std::string className, std::string identifier)
{
  int x = this->bcGenerator->addLiteral(identifier);
  std::string instructions;
  EMIT_2(SET_LOCAL, className, std::to_string(x));
  this->bcGenerator->pushBuffer(instructions);
}