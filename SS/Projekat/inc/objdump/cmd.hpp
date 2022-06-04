#ifndef _CMD_HPP
#define _CMD_HPP
#include <string>

struct CommandLineArgs {
    std::string inputFilename;
    CommandLineArgs(int argc, char* argv[]);
};
#endif
