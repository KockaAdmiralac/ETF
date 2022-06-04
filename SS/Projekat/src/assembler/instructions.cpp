#include "assembler/instructions.hpp"

void insertOpcode(Context& context, Instruction& instruction) {
    context.currentSection().contents.push_back(instruction.type << 4 | instruction.subtype);
}

void insertRegsDescr(Context& context, Instruction& instruction) {
    context.currentSection().contents.push_back(instruction.regD << 4 | instruction.regS);
}

void insertAddrMode(Context& context, Instruction& instruction, UpMode upMode) {
    context.currentSection().contents.push_back(upMode << 4 | instruction.operand.type);
}

void insertData(Context& context, Operand& op) {
    if (op.sym == nullptr) {
        context.addData(op.num);
    } else {
        std::string symbol(op.sym);
        free(op.sym);
        context.addData(context.resolveSymbol(symbol, op.pcrel ? REL_PC : REL_ABS));
    }
}

void decodeOperand(Context& context, Instruction& instruction, UpMode upMode = UP_NONE) {
    Operand& op = instruction.operand;
    switch (op.type) {
        case OP_IMMED:
        case OP_MEM:
            insertRegsDescr(context, instruction);
            insertAddrMode(context, instruction, upMode);
            insertData(context, instruction.operand);
            break;
        case OP_REGDIR:
        case OP_REGIND:
            instruction.regS = instruction.operand.reg;
            insertRegsDescr(context, instruction);
            insertAddrMode(context, instruction, upMode);
            break;
        case OP_REGDIRADD:
        case OP_REGINDPOM:
            instruction.regS = instruction.operand.reg;
            insertRegsDescr(context, instruction);
            insertAddrMode(context, instruction, upMode);
            insertData(context, instruction.operand);
            break;
        default:
            throw std::runtime_error("Invalid operand type: " + std::to_string(op.type));
    }
}

const InstructionHandler INSTRUCTIONS[] = {
    // halt
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
    },
    // int
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        insertRegsDescr(context, instruction);
    },
    // iret
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
    },
    // call
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        decodeOperand(context, instruction);
    },
    // ret
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
    },
    // Jump instructions
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        decodeOperand(context, instruction);
    },
    // xchg
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        insertRegsDescr(context, instruction);
    },
    // Arithemtic instructions
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        insertRegsDescr(context, instruction);
    },
    // Logic instructions
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        insertRegsDescr(context, instruction);
    },
    // Shift instructions
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        insertRegsDescr(context, instruction);
    },
    // ldr, pop
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        UpMode upMode = UP_NONE;
        if (instruction.subtype == LD_POP) {
            instruction.operand.type = OP_REGIND;
            instruction.operand.reg = 6;
            upMode = UP_POSTINC;
        }
        decodeOperand(context, instruction, upMode);
    },
    // str, push
    [](Context& context, Instruction& instruction) {
        insertOpcode(context, instruction);
        UpMode upMode = UP_NONE;
        if (instruction.subtype == LD_POP) {
            instruction.operand.type = OP_REGIND;
            instruction.operand.reg = 6;
            upMode = UP_PREDEC;
        }
        decodeOperand(context, instruction, upMode);
    }
};
