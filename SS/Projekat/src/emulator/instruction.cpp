#include "emulator/context.hpp"
#include "emulator/error.hpp"
#include "emulator/instruction.hpp"

uint8_t DecodedInstruction::getNumBytes(uint8_t byte) {
    switch (byte >> 4) {
        case INS_HALT:
        case INS_IRET:
        case INS_RET:
            return 1;
        case INS_INT:
        case INS_XCHG:
        case INS_ARITH:
        case INS_LOG:
        case INS_SH:
            return 2;
        default:
            return 3;
    }
}

bool DecodedInstruction::hasPayload(uint8_t byte) {
    uint8_t addrMode = byte & 0xF;
    return addrMode == OP_IMMED || addrMode == OP_REGDIRADD || addrMode == OP_REGINDPOM || addrMode == OP_MEM;
}

DecodedInstruction::DecodedInstruction(uint8_t instrDescr, uint8_t regsDescr, uint8_t addrMode, uint8_t dataHigh, uint8_t dataLow) {
    type = InstructionType((instrDescr & 0xF0) >> 4);
    subtype = instrDescr & 0xF;
    regD = regsDescr >> 4;
    regS = regsDescr & 0xF;
    upMode = UpMode(addrMode >> 4);
    opType = OperandType(addrMode & 0xF);
    payload = (int16_t(dataHigh) << 8) + dataLow;
}

void DecodedInstruction::fetchOperand(Context& context) {
    if (type == INS_STR) {
        // No need to fetch operand
        return;
    }
    switch (opType) {
        // When an instruction does not have the third, fourth and fifth byte,
        // it will also fall in this branch, and the operand will be 0
        case OP_IMMED:
            operand = payload;
            break;
        case OP_REGDIR:
            operand = context.cpu.registers[regS];
            break;
        case OP_REGIND:
        case OP_REGINDPOM:
            if (upMode == UP_PREDEC) {
                context.cpu.registers[regS] -= 2;
            } else if (upMode == UP_PREINC) {
                context.cpu.registers[regS] += 2;
            }
            if (opType == OP_REGINDPOM) {
                operand = context.read(context.cpu.registers[regS] + payload);
            } else {
                operand = context.read(context.cpu.registers[regS]);
            }
            if (upMode == UP_POSTDEC) {
                context.cpu.registers[regS] -= 2;
            } else if (upMode == UP_POSTINC) {
                context.cpu.registers[regS] += 2;
            }
            break;
        case OP_MEM:
            operand = context.read(payload);
            break;
        case OP_REGDIRADD:
            operand = context.cpu.registers[regS] + payload;
            break;
    }
}

void DecodedInstruction::execute(Context& context) {
    int16_t tmp;
    uint16_t unsignedDiff;
    uint64_t unsignedDiffWider;
    int16_t signedDiff;
    int64_t signedDiffWider;
    bool condition = false;
    switch (type) {
        case INS_HALT:
            context.cpu.halted = true;
            break;
        case INS_INT:
            context.push(context.cpu.registers[7]);
            context.push(context.cpu.registers[8]);
            context.cpu.registers[7] = context.read((context.cpu.registers[regD] % 8) * 2);
            break;
        case INS_IRET:
            context.cpu.registers[8] = context.pop();
            context.cpu.registers[7] = context.pop();
            break;
        case INS_CALL:
            context.push(context.cpu.registers[7]);
            context.cpu.registers[7] = operand;
            break;
        case INS_RET:
            context.cpu.registers[7] = context.pop();
            break;
        case INS_JMP:
            switch (subtype) {
                case JMP_UNCND:
                    condition = true;
                    break;
                case JMP_EQ:
                    condition = context.cpu.zero();
                    break;
                case JMP_NE:
                    condition = !context.cpu.zero();
                    break;
                case JMP_GT:
                    condition = !(context.cpu.zero() || (context.cpu.negative() != context.cpu.overflow()));
                    break;
                default:
                    throw CPUError("Invalid jump instruction subtype encountered.");
            }
            if (condition) {
                context.cpu.registers[7] = operand;
            }
            break;
        case INS_XCHG:
            tmp = context.cpu.registers[regD];
            context.cpu.registers[regD] = context.cpu.registers[regS];
            context.cpu.registers[regS] = tmp;
            break;
        case INS_ARITH:
            switch (subtype) {
                case AR_ADD:
                    context.cpu.registers[regD] += context.cpu.registers[regS];
                    break;
                case AR_SUB:
                    context.cpu.registers[regD] -= context.cpu.registers[regS];
                    break;
                case AR_MUL:
                    context.cpu.registers[regD] *= context.cpu.registers[regS];
                    break;
                case AR_DIV:
                    if (context.cpu.registers[regS] == 0) {
                        throw CPUError("Division by zero.");
                    }
                    context.cpu.registers[regD] /= context.cpu.registers[regS];
                    break;
                case AR_CMP:
                    tmp = context.cpu.registers[regD] - context.cpu.registers[regS];
                    context.cpu.zero(tmp == 0);
                    context.cpu.negative(tmp < 0);
                    unsignedDiff = uint16_t(context.cpu.registers[regD]) - uint16_t(context.cpu.registers[regS]);
                    unsignedDiffWider = uint64_t(context.cpu.registers[regD]) - uint64_t(context.cpu.registers[regS]);
                    context.cpu.carry(unsignedDiff != unsignedDiffWider);
                    signedDiff = context.cpu.registers[regD] - context.cpu.registers[regS];
                    signedDiffWider = int64_t(context.cpu.registers[regD]) - int64_t(context.cpu.registers[regS]);
                    context.cpu.overflow(signedDiff != signedDiffWider);
                    break;
                default:
                    throw CPUError("Invalid arithmetic instruction subtype encountered.");
            }
            break;
        case INS_LOG:
            switch (subtype) {
                case LOG_NOT:
                    context.cpu.registers[regD] = ~context.cpu.registers[regD];
                    break;
                case LOG_AND:
                    context.cpu.registers[regD] &= context.cpu.registers[regS];
                    break;
                case LOG_OR:
                    context.cpu.registers[regD] |= context.cpu.registers[regS];
                    break;
                case LOG_XOR:
                    context.cpu.registers[regD] ^= context.cpu.registers[regS];
                    break;
                case LOG_TEST:
                    tmp = context.cpu.registers[regD] & context.cpu.registers[regS];
                    context.cpu.zero(tmp == 0);
                    context.cpu.negative(tmp < 0);
                    break;
                default:
                    throw CPUError("Invalid logic instruction subtype encountered.");
            }
            break;
        case INS_SH:
            switch (subtype) {
                case SH_LEFT:
                    context.cpu.carry((context.cpu.registers[regD] & 0x8000) != 0);
                    context.cpu.registers[regD] <<= context.cpu.registers[regS];
                    break;
                case SH_RIGHT:
                    context.cpu.carry((context.cpu.registers[regD] & 0x0001) != 0);
                    context.cpu.registers[regD] >>= context.cpu.registers[regS];
                    break;
                default:
                    throw CPUError("Invalid shift instruction subtype encountered.");
            }
            context.cpu.zero(context.cpu.registers[regD] == 0);
            context.cpu.negative(context.cpu.registers[regD] < 0);
            break;
        case INS_LDR:
            context.cpu.registers[regD] = operand;
            break;
        case INS_STR:
            switch (opType) {
                case OP_IMMED:
                    throw CPUError("Cannot store using immediate address mode.");
                case OP_REGDIR:
                    context.cpu.registers[regS] = context.cpu.registers[regD];
                    break;
                case OP_REGIND:
                case OP_REGINDPOM:
                    if (upMode == UP_PREDEC) {
                        context.cpu.registers[regS] -= 2;
                    } else if (upMode == UP_PREINC) {
                        context.cpu.registers[regS] += 2;
                    }
                    if (opType == OP_REGINDPOM) {
                        context.write(context.cpu.registers[regS] + payload, context.cpu.registers[regD]);
                    } else {
                        context.write(context.cpu.registers[regS], context.cpu.registers[regD]);
                    }
                    if (upMode == UP_POSTDEC) {
                        context.cpu.registers[regS] -= 2;
                    } else if (upMode == UP_POSTINC) {
                        context.cpu.registers[regS] += 2;
                    }
                    break;
                case OP_MEM:
                    context.write(payload, context.cpu.registers[regD]);
                    break;
                case OP_REGDIRADD:
                    throw CPUError("Cannot store using register direct mode with addend.");
                    break;
            }
            break;
        default:
            throw CPUError("Invalid instruction encountered.");
    }
}
