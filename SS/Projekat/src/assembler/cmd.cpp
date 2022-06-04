#include <stdexcept>
#include "assembler/cmd.hpp"

CommandLineArgs::CommandLineArgs(int argc, char* argv[]) {
    switch (argc) {
        case 2:
            inputFilename = argv[1];
            outputFilename = "a.out";
            break;
        case 4:
            inputFilename = argv[3];
            if (std::string(argv[1]) != "-o") {
                throw std::runtime_error(std::string("Invalid option: ") + argv[1]);
            }
            outputFilename = argv[2];
            break;
        default:
            throw std::runtime_error("Invalid number of arguments.");
    }
}
