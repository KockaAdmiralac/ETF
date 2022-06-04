#include <iostream>
#include "assembler/cmd.hpp"
#include "assembler/context.hpp"
#include "assembler/directives.hpp"
#include "assembler/instructions.hpp"
#include "assembler/parse.hpp"

int main(int argc, char* argv[]) {
    try {
        CommandLineArgs args(argc, argv);
        ParseResult parseResult(args.inputFilename);
        Context context;
        for (Line& line : parseResult.lines) {
            if (line.label != nullptr) {
                std::string labelStr = line.label;
                context.addLabel(labelStr);
                free(line.label);
            }
            switch (line.type) {
                case L_NONE:
                    // Nothing
                    break;
                case L_DIR:
                    DIRECTIVES[line.data.dir.type](context, line.data.dir);
                    break;
                case L_INS:
                    INSTRUCTIONS[line.data.ins.type](context, line.data.ins);
                    break;
            }
            if (context.theEnd) {
                break;
            }
        }
        context.write(args.outputFilename);
        return EXIT_SUCCESS;
    } catch (std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }
}
