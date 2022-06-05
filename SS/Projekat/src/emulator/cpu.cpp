#include "emulator/cpu.hpp"

void updateBit(int16_t& num, uint16_t mask, bool value) {
    if (value) {
        num |= mask;
    } else {
        num &= ~mask;
    }
}

bool CPU::zero() {
    return registers[8] & PSW_Z;
}

void CPU::zero(bool value) {
    updateBit(registers[8], PSW_Z, value);
}

bool CPU::overflow() {
    return registers[8] & PSW_O;
}

void CPU::overflow(bool value) {
    updateBit(registers[8], PSW_O, value);
}

bool CPU::carry() {
    return registers[8] & PSW_C;
}

void CPU::carry(bool value) {
    updateBit(registers[8], PSW_C, value);
}

bool CPU::negative() {
    return registers[8] & PSW_N;
}

void CPU::negative(bool value) {
    updateBit(registers[8], PSW_N, value);
}

bool CPU::timerMasked() {
    return registers[8] & PSW_Tr;
}

void CPU::timerMasked(bool value) {
    updateBit(registers[8], PSW_Tr, value);
}

bool CPU::terminalMasked() {
    return registers[8] & PSW_Tl;
}

void CPU::terminalMasked(bool value) {
    updateBit(registers[8], PSW_Tl, value);
}

bool CPU::interruptsMasked() {
    return registers[8] & PSW_I;
}

void CPU::interruptsMasked(bool value) {
    updateBit(registers[8], PSW_I, value);
}

