#ifndef _INSTRUCTIONS_HPP
#define _INSTRUCTIONS_HPP
#include "syntax.hpp"
#include "assembler/context.hpp"

typedef void (*InstructionHandler)(Context& context, Instruction& instruction);
extern const InstructionHandler INSTRUCTIONS[];
#endif