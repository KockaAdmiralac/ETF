#ifndef _INSTRUCTION_HPP
#define _INSTRUCTION_HPP
#include "syntax.hpp"
#include "emulator/context.hpp"

class Context;
struct DecodedInstruction {
    InstructionType type;
    uint8_t subtype;
    uint8_t regD;
    uint8_t regS;
    UpMode upMode;
    OperandType opType;
    uint16_t operand;
    int16_t payload;
    static uint8_t getNumBytes(uint8_t byte);
    static bool hasPayload(uint8_t byte);
    DecodedInstruction(uint8_t instrDescr, uint8_t regsDescr = 0, uint8_t addrMode = 0, uint8_t dataHigh = 0, uint8_t dataLow = 0);
    void fetchOperand(Context& context);
    void execute(Context& context);
};
#endif
