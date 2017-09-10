#ifndef __OPCODES
#define __OPCODES 1

#include <string>
#include <sstream>

enum OPCODE{
  NOOP,
  PUSH_INTEGER,
  PUSH_STRING,
  PUSH_ARRAY,
  SET_LOCAL,
  POP
};

#define EMIT_0(opcode)                                                                          \
{                                                                                               \
  std::stringstream instColStream;                                                              \
  instColStream << std::setw(7) << std::setfill('0') << this->bcGenerator->instructionCount;    \
  instructions.append("\t").append(instColStream.str()).append(" ").append(" ")                              \
    .append(opInstructions[opcode]).append("\n");                                               \
  this->bcGenerator->incrementInstructionCount(1);                                              \
}

#define EMIT_1(opcode, operand1)                                                                \
{                                                                                               \
  std::stringstream instColStream;                                                              \
  instColStream << std::setw(7) << std::setfill('0') << this->bcGenerator->instructionCount;    \
  instructions.append("\t").append(instColStream.str()).append(" ")                                          \
    .append(" ")                                                                                \
    .append(opInstructions[opcode]).append(" ")                                                 \
      .append(operand1).append("\n");                                                           \
  this->bcGenerator->incrementInstructionCount(2);                                              \
}

#define EMIT_2(opcode, operand1, operand2)                                                      \
{                                                                                               \
  std::stringstream instColStream;                                                              \
  instColStream << std::setw(7) << std::setfill('0') << this->bcGenerator->instructionCount;    \
  instructions.append("\t").append(instColStream.str()).append(" ")                                          \
  .append(" ")                                                                                  \
    .append(opInstructions[opcode]).append(" ")                                                 \
    .append(" ").append(operand1).append(" ")                                                   \
      .append(operand2).append("\n");                                                           \
  this->bcGenerator->incrementInstructionCount(3);                                              \
}

#endif