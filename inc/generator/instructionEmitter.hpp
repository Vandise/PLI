#ifndef __INSTRUCTIONEMITTER
#define __INSTRUCTIONEMITTER 1

#include <iostream>
#include "generator/opCodes.hpp"
#include "generator/bytecode.hpp"

namespace Generator
{

  class ByteCode;

  class InstructionEmitter
  {

    private:
      Generator::ByteCode* bcGenerator;

    public:
      ~InstructionEmitter();
      InstructionEmitter(Generator::ByteCode* bcGenerator);
      void pushInteger(int value);
      void pushString(std::string value);
      void setLocal(std::string className, std::string identifier);
  };

}

#endif