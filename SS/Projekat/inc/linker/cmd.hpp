#ifndef _CMD_HPP
#define _CMD_HPP
#include <string>
#include <unordered_map>
#include <vector>

struct CommandLineArgs {
    std::string outputFilename;
    std::vector<std::string> inputFilenames;
    std::unordered_map<std::string, uint64_t> places;
    bool generateHex = false;
    bool relocatable = false;
    CommandLineArgs(int argc, char* argv[]);
};
#endif
