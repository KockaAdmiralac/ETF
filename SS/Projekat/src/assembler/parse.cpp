#include "assembler/parse.hpp"

void yyerror(std::vector<Line>& lines, const char *s) {
    std::string error = "Parse error on line " + std::to_string(lineNumber) + ", after instruction " + std::to_string(lines.size()) + ": " + s;
    throw std::runtime_error(error);
}

ParseResult::ParseResult(std::string& inputFilename) {
    FILE* parseFile = fopen(inputFilename.c_str(), "r");
    yyin = parseFile;
    if (yyin == NULL) {
        throw std::runtime_error("Input file " + inputFilename + " does not exist or cannot be read.");
    }
    int parseRet = yyparse(lines);
    yylex_destroy();
    fclose(parseFile);
    yyin = NULL;
    if (parseRet == 2) {
        throw std::runtime_error("Memory exhaustion during parsing.");
    } else if (parseRet != 0) {
        throw std::runtime_error("Unknown parse error, error code: " + std::to_string(parseRet));
    }
}

ParseResult::~ParseResult() {
    if (yyin != NULL) {
        yylex_destroy();
        fclose(yyin);
    }
}
