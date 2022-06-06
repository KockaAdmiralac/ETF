#include <fstream>
#include "emulator/context.hpp"
#include "emulator/error.hpp"

Context::Context(const char* filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open input file: " + std::string(filename));
    }
    memory.read(inputFile);
    cpu.registers[6] = 0xFF00;
    cpu.registers[7] = read(0);
    cpu.registers[8] = 0;
}

uint16_t Context::read(uint64_t addr) {
    return (uint16_t(readByte(addr)) << 8) + readByte(addr + 1);
}

void Context::write(uint64_t addr, uint16_t data) {
    if ((addr & 0xFF00) == 0xFF00) {
        switch (addr & 0xFFFF) {
            case 0xFF00:
                terminal.write(data);
                break;
            case 0xFF01:
                terminal.write(data >> 8);
                break;
            case 0xFF10:
                timer.timCfg = data;
                break;
            case 0xFF11:
                timer.timCfg = data >> 8;
                break;
            default:
                throw CPUError("Segmentation fault while writing to memory.");
        }
    } else {
        writeByte(addr, (data & 0xFF00) >> 8);
        writeByte(addr + 1, data & 0xFF);
    }
}

uint8_t Context::readByte(uint64_t addr) {
    if ((addr & 0xFF00) == 0xFF00) {
        switch (addr & 0xFFFF) {
            case 0xFF02:
                return (terminal.termIn >> 8);
            case 0xFF03:
                return terminal.termIn & 0xFF;
            default:
                throw CPUError("Segmentation fault while reading from memory.");
        }
    }
    return memory.readMemory(addr);
}

void Context::writeByte(uint64_t addr, uint8_t data) {
    memory.writeMemory(addr, data);
}

void Context::push(uint16_t data) {
    cpu.registers[6] -= 2;
    write(cpu.registers[6], data);
}

int16_t Context::pop() {
    int16_t data = read(cpu.registers[6]);
    cpu.registers[6] += 2;
    return data;
}

bool Context::running() {
    return !cpu.halted;
}

void Context::checkInterrupts() {
    if (cpu.halted || cpu.interruptsMasked()) {
        return;
    }
    bool hasInterrupt = false;
    uint64_t entry;
    if (terminal.interrupt && !cpu.terminalMasked()) {
        terminal.interrupt = false;
        hasInterrupt = true;
        entry = 3;
    } else if (timer.interrupt && !cpu.timerMasked()) {
        timer.interrupt = false;
        hasInterrupt = true;
        entry = 2;
    }
    if (hasInterrupt) {
        push(cpu.registers[7]);
        push(cpu.registers[8]);
        cpu.interruptsMasked(true);
        cpu.registers[7] = read(entry * 2);
    }
}

DecodedInstruction Context::fetch() {
    uint8_t instrDescr = readByte(cpu.registers[7]++);
    uint8_t numBytes = DecodedInstruction::getNumBytes(instrDescr);
    if (numBytes == 1) {
        return DecodedInstruction(instrDescr);
    }
    uint8_t regsDescr = readByte(cpu.registers[7]++);
    if (numBytes == 2) {
        return DecodedInstruction(instrDescr, regsDescr);
    }
    uint8_t addrMode = readByte(cpu.registers[7]++);
    if (!DecodedInstruction::hasPayload(addrMode)) {
        return DecodedInstruction(instrDescr, regsDescr, addrMode);
    }
    uint8_t dataHigh = readByte(cpu.registers[7]++);
    uint8_t dataLow = readByte(cpu.registers[7]++);
    return DecodedInstruction(instrDescr, regsDescr, addrMode, dataHigh, dataLow);
}
