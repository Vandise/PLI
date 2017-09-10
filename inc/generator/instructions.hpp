#ifndef __OPCODE_INSTRUCTIONS
#define __OPCODE_INSTRUCTIONS 1

#include <string>

static std::string opInstructions[] = {
  "NOOP",
  "PUSH_INTEGER",
  "PUSH_STRING",
  "PUSH_ARRAY",
  "SET_LOCAL",
  "POP"
};

#endif