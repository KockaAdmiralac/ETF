#ifndef _SYNTAX_HPP
#define _SYNTAX_HPP
#include <cstdint>
enum SymbolType {
    SYM_SYM,
    SYM_LIT
};
struct SymbolListElement {
    SymbolType type;
    union {
        int num;
        char* sym;
    } data;
};
struct SymbolList {
    int length;
    SymbolListElement* syms;
};
struct ExpressionOperand {
    char* sym;
    int num;
    int sign;
};
struct Expression {
    int length;
    ExpressionOperand* operands;
};
enum OperandType {
    OP_IMMED,
    OP_REGDIR,
    OP_REGIND,
    OP_REGINDPOM,
    OP_MEM,
    OP_REGDIRADD
};
struct Operand {
    OperandType type;
    int reg;
    int num;
    char* sym;
    bool pcrel;
};
enum DirectiveType {
    DIR_GLOBAL,
    DIR_EXTERN,
    DIR_SECTION,
    DIR_WORD,
    DIR_SKIP,
    DIR_ASCII,
    DIR_EQU,
    DIR_END
};
struct Directive {
    DirectiveType type;
    SymbolList syms;
    Expression expr;
    char* sym;
    char* sym2;
    int num;
};
enum InstructionType {
    INS_HALT,
    INS_INT,
    INS_IRET,
    INS_CALL,
    INS_RET,
    INS_JMP,
    INS_XCHG,
    INS_ARITH,
    INS_LOG,
    INS_SH,
    INS_LDR,
    INS_STR
};
enum JumpInstructionType {
    JMP_UNCND,
    JMP_EQ,
    JMP_NE,
    JMP_GT,
};
enum ArithmeticInstructionType {
    AR_ADD,
    AR_SUB,
    AR_MUL,
    AR_DIV,
    AR_CMP
};
enum LogicInstructionType {
    LOG_NOT,
    LOG_AND,
    LOG_OR,
    LOG_XOR,
    LOG_TEST
};
enum ShiftInstructionType {
    SH_LEFT,
    SH_RIGHT
};
enum LoadInstructionType {
    LD_REG,
    LD_POP
};
enum StoreInstructionType {
    ST_REG,
    ST_PUSH
};
enum UpMode {
    UP_NONE,
    UP_PREDEC,
    UP_PREINC,
    UP_POSTDEC,
    UP_POSTINC
};
struct Instruction {
    InstructionType type;
    uint64_t subtype;
    Operand operand;
    int regS;
    int regD;
};
enum LineType {
    L_NONE,
    L_DIR,
    L_INS
};
struct Line {
    LineType type;
    char* label;
    union {
        Directive dir;
        Instruction ins;
    } data;
};
#endif
