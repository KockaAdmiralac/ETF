#include "assembler/directives.hpp"

std::string convertSymbol(char* sym) {
    std::string str(sym);
    free(sym);
    return str;
}

std::vector<std::string> convertSymbolList(const SymbolList& syms) {
    std::vector<std::string> vec;
    for (int i = 0; i < syms.length; ++i) {
        vec.push_back(convertSymbol(syms.syms[i]));
    }
    free(syms.syms);
    return vec;
}

const DirectiveHandler DIRECTIVES[] = {
    // .global
    [](Context& context, Directive& directive) {
        std::vector<std::string> syms = convertSymbolList(directive.syms);
        for (std::string& sym : syms) {
            if (context.r.symtab.hasSymbol(sym)) {
                Symbol& symbol = context.r.symtab.getSymbol(sym);
                symbol.flags |= Symbol::SYM_GLOBAL;
            } else {
                context.addSymbol(sym, 0, Symbol::SYM_GLOBAL | Symbol::SYM_UNDEF);
            }
        }
    },
    // .extern
    [](Context& context, Directive& directive) {
        std::vector<std::string> syms = convertSymbolList(directive.syms);
        for (std::string& sym : syms) {
            if (context.r.symtab.hasSymbol(sym)) {
                throw std::runtime_error("External symbol already defined: " + sym);
            }
            context.addSymbol(sym, 0, Symbol::SYM_EXTERN | Symbol::SYM_GLOBAL | Symbol::SYM_UNDEF);
        }
    },
    // .section
    [](Context& context, Directive& directive) {
        std::string sym = convertSymbol(directive.sym);
        context.addSection(sym);
    },
    // .word
    [](Context& context, Directive& directive) {
        if (directive.syms.length == 0) {
            context.addData(directive.num);
        } else {
            std::vector<std::string> syms = convertSymbolList(directive.syms);
            for (std::string& sym : syms) {
                context.addData(context.resolveSymbol(sym));
            }
        }
    },
    // .skip
    [](Context& context, Directive& directive) {
        for (int i = 0; i < directive.num; ++i)  {
            context.currentSection().contents.push_back(0);
        }
    },
    // .ascii
    [](Context& context, Directive& directive) {
        std::string sym = convertSymbol(directive.sym);
        for (char c : sym) {
            context.currentSection().contents.push_back(c);
        }
    },
    // .equ
    [](Context& context, Directive& directive) {
        std::string newSym = convertSymbol(directive.sym);
        convertSymbol(directive.sym2);
        // TODO
    },
    // .end
    [](Context& context, Directive&) {
        context.theEnd = true;
    }
};
