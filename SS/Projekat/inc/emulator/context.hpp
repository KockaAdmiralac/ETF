#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP
#include "hex/hex-file.hpp"
#include "emulator/cpu.hpp"
#include "emulator/instruction.hpp"
#include "emulator/terminal.hpp"
#include "emulator/timer.hpp"

struct Context {
    HexFile memory;
    CPU cpu;
    Timer timer;
    Terminal terminal;
    Context(const char* filename);
    uint16_t read(uint64_t addr);
    void write(uint64_t addr, uint16_t data);
    uint8_t readByte(uint64_t addr);
    void writeByte(uint64_t addr, uint8_t data);
    void push(uint16_t data);
    int16_t pop();
    bool running();
    void checkInterrupts();
    DecodedInstruction fetch();
};
#endif
