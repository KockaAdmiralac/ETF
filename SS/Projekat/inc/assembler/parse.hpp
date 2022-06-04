#ifndef _PARSE_HPP
#define _PARSE_HPP
#include <cstdio>
#include <stdexcept>
#include <vector>
#include "syntax.hpp"
#include "syntax.tab.hpp"

extern int yylex();
extern void yylex_destroy();
extern FILE *yyin;
extern int lineNumber;

struct ParseResult {
    std::vector<Line> lines;
    ParseResult(std::string& inputFilename);
    ~ParseResult();
};
#endif
