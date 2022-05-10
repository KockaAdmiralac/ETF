#ifndef _SYNTAX_HPP
#define _SYNTAX_HPP
struct SymbolList {
    int length;
    char** syms;
};
enum OperandType {
    OP_DOLLAR_LITERAL,
    OP_DOLLAR_SYMBOL,
    OP_LITERAL,
    OP_SYMBOL,
    OP_PERCENT_SYMBOL,
    OP_REGISTER,
    OP_BRACKET_REGISTER,
    OP_BRACKET_REGISTER_LITERAL,
    OP_BRACKET_REGISTER_SYMBOL,
    OP_STAR_LITERAL,
    OP_STAR_SYMBOL,
    OP_STAR_REGISTER,
    OP_STAR_BRACKET_REGISTER,
    OP_STAR_BRACKET_REGISTER_LITERAL,
    OP_STAR_BRACKET_REGISTER_SYMBOL
};
struct Operand {
    OperandType type;
    int reg;
    int num;
    char* sym;
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
    char* sym;
    char* sym2;
    int num;
};
enum InstructionType {
    INS_NONE,
    INS_HALT,
    INS_INT,
    INS_IRET,
    INS_CALL,
    INS_RET,
    INS_JMP,
    INS_JEQ,
    INS_JNE,
    INS_JGT,
    INS_PUSH,
    INS_POP,
    INS_XCHG,
    INS_ADD,
    INS_SUB,
    INS_MUL,
    INS_DIV,
    INS_CMP,
    INS_NOT,
    INS_AND,
    INS_OR,
    INS_XOR,
    INS_TEST,
    INS_SHL,
    INS_SHR,
    INS_LDR,
    INS_STR
};
struct Instruction {
    InstructionType type;
    Operand operand;
    int reg1;
    int reg2;
};
enum LineType {
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
