#ifndef _DIRECTIVES_HPP
#define _DIRECTIVES_HPP
#include "syntax.hpp"
#include "assembler/context.hpp"

typedef void (*DirectiveHandler)(Context& context, Directive& directive);
extern const DirectiveHandler DIRECTIVES[];
#endif
