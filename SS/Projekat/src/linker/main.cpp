#include <fstream>
#include <iostream>
#include <stdexcept>
#include "linker/cmd.hpp"
#include "linker/place.hpp"
#include "relocatable/relocatable.hpp"

int main(int argc, char* argv[]) {
    try {
        CommandLineArgs args(argc, argv);
        if ((!args.generateHex && !args.relocatable) || (args.generateHex && args.relocatable)) {
            // Nothing to do.
            return EXIT_SUCCESS;
        }
        Relocatable product;
        for (std::string& filename : args.inputFilenames) {
            std::ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                throw std::runtime_error("Failed to open input file: " + filename);
            }
            Relocatable r;
            r.read(inputFile);
            product.merge(r);
        }
        if (args.generateHex) {
            std::ofstream outputFile(args.outputFilename);
            if (outputFile.fail()) {
                throw std::runtime_error("Failed to open output file: " + args.outputFilename);
            }
            place(product, args.places, outputFile);
        }
        if (args.relocatable) {
            std::ofstream outputFile(args.outputFilename, std::ios::binary);
            if (outputFile.fail()) {
                throw std::runtime_error("Failed to open output file: " + args.outputFilename);
            }
            product.write(outputFile);
        }
        return EXIT_SUCCESS;
    } catch (std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
}
