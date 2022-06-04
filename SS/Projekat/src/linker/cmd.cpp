#include <stdexcept>
#include "linker/cmd.hpp"

CommandLineArgs::CommandLineArgs(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-hex") {
            generateHex = true;
        } else if (arg == "-relocatable" || arg == "-relocateable") {
            relocatable = true;
        } else if (arg == "-o") {
            if (i == argc - 1) {
                throw std::runtime_error("Missing filename after the -o option.");
            }
            outputFilename = argv[++i];
        } else if (arg.starts_with("-place=")) {
            size_t pos = arg.find("@", 7);
            if (pos == std::string::npos) {
                throw std::runtime_error("Invalid format of the -place option: " + arg);
            }
            places[arg.substr(7, pos - 7)] = std::stoul(arg.substr(pos + 1), nullptr, 0);
        } else {
            inputFilenames.push_back(arg);
        }
    }
}
