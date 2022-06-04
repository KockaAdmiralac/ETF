#include <stdexcept>
#include "objdump/cmd.hpp"

CommandLineArgs::CommandLineArgs(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::runtime_error("Invalid number of arguments.");
    }
    inputFilename = argv[1];
}
