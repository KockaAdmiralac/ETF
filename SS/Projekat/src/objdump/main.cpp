#include <fstream>
#include <iostream>
#include <vector>
#include "relocatable/relocatable.hpp"
#include "objdump/cmd.hpp"
#include "objdump/format.hpp"
#include "objdump/print.hpp"

int main(int argc, char* argv[]) {
    try {
        CommandLineArgs args(argc, argv);
        std::ifstream relocatableFile(args.inputFilename, std::ios::in);
        if (!relocatableFile.is_open()) {
            throw std::runtime_error("Cannot open file.");
        }
        Relocatable r;
        r.read(relocatableFile);
        std::cout << "#.symtab" << std::endl;
        printTable(
            {"Num", "Value", "Size", "Type", "Bind", "Ndx", "Name"},
            formatSymbolTable(r.symtab)
        );
        for (Section& section : r.sections) {
            if (section.contents.empty()) {
                continue;
            }
            std::cout << "#." << section.name << std::endl;
            printTable(
                {"Offset", "Values"},
                formatSection(section)
            );
        }
        for (RelocationTable& table : r.relocations) {
            if (table.empty()) {
                continue;
            }
            std::cout << "#.rela." << table.getName() << std::endl;
            printTable(
                {"Offset", "Type", "Symbol", "Addend"},
                formatRelocationTable(table, r.symtab)
            );
        }
        return EXIT_SUCCESS;
    } catch (std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
}
