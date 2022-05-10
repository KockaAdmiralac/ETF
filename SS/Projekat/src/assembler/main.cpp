#include <cstdio>
#include <iostream>
#include <vector>
#include "../../inc/syntax.hpp"
#include "../../syntax.tab.hpp"

extern int yylex();
extern void yylex_destroy();
extern FILE *yyin;
extern int lineNumber;

void yyerror(std::vector<Line>& lines, const char *s) {
    std::cout << "Parse error on line " << lineNumber << ", after instruction " << lines.size() << ": " << s << std::endl;
}

int main() {
    return 0;
}
