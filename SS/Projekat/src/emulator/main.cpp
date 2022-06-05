#include <bitset>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "emulator/context.hpp"
#include "emulator/error.hpp"

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            throw std::runtime_error("Invalid number of arguments.");
        }
        Context context(argv[1]);
        while (context.running()) {
            try {
                DecodedInstruction ins = context.fetch();
                ins.fetchOperand(context);
                ins.execute(context);
                context.terminal.update();
                context.timer.update();
                if (ins.type != INS_IRET) {
                    // Let at least one instruction execute normally
                    // before entering another interrupt routine
                    context.checkInterrupts();
                }
            } catch (CPUError& error) {
                uint16_t entry = context.read(2);
                if (entry == 0) {
                    std::cerr << "CPU encountered an error: " << error.what() << std::endl
                              << "As there is no error handler assigned for situationes "
                              << "like these, the CPU will now halt." << std::endl;
                    context.cpu.halted = true;
                } else {
                    context.cpu.registers[7] = entry;
                }
            }
        }
        std::cout << std::endl << "------------------------------------------------"
                  << std::endl << "Emulated processor executed halt instruction"
                  << std::endl << "Emulated processor state: psw=0b"
                  << std::bitset<16>(context.cpu.registers[8]) << std::endl;
        for (uint8_t i = 0; i < 2; ++i) {
            for (uint8_t j = 0; j < 4; ++j) {
                uint64_t regnum = i * 4 + j;
                std::cout << "r" << regnum << "=0x" << std::hex << std::setw(4) << std::setfill('0')
                          << context.cpu.registers[regnum] << "    ";
            }
            std::cout << std::endl;
        }
        return EXIT_SUCCESS;
    } catch (std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
