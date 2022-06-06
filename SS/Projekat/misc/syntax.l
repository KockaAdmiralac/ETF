%{
    #include <vector>
    #include "inc/syntax.hpp"
    #include "syntax.tab.hpp"
    int lineNumber = 1;
%}
%option noyywrap
%option nounput
%%
[ \t]                               ;
"+"                                 { return PLUS; }
"-"                                 { return MINUS; }
"*"                                 { return STAR; }
"$"                                 { return DOLLAR; }
"("                                 { return LBRACE; }
")"                                 { return RBRACE; }
"["                                 { return LBRACKET; }
"]"                                 { return RBRACKET; }
"%"                                 { return PERCENT; }
","                                 { return COMMA; }
#.*                                 { return COMMENT; }
halt                                { return INSTRUCTION_HALT; }
int                                 { return INSTRUCTION_INT; }
iret                                { return INSTRUCTION_IRET; }
call                                { return INSTRUCTION_CALL; }
ret                                 { return INSTRUCTION_RET; }
jmp                                 { return INSTRUCTION_JMP; }
jeq                                 { return INSTRUCTION_JEQ; }
jne                                 { return INSTRUCTION_JNE; }
jgt                                 { return INSTRUCTION_JGT; }
push                                { return INSTRUCTION_PUSH; }
pop                                 { return INSTRUCTION_POP; }
xchg                                { return INSTRUCTION_XCHG; }
add                                 { return INSTRUCTION_ADD; }
sub                                 { return INSTRUCTION_SUB; }
mul                                 { return INSTRUCTION_MUL; }
div                                 { return INSTRUCTION_DIV; }
cmp                                 { return INSTRUCTION_CMP; }
not                                 { return INSTRUCTION_NOT; }
and                                 { return INSTRUCTION_AND; }
or                                  { return INSTRUCTION_OR; }
xor                                 { return INSTRUCTION_XOR; }
test                                { return INSTRUCTION_TEST; }
shl                                 { return INSTRUCTION_SHL; }
shr                                 { return INSTRUCTION_SHR; }
ldr                                 { return INSTRUCTION_LDR; }
str                                 { return INSTRUCTION_STR; }
".global"                           { return DIRECTIVE_GLOBAL; }
".extern"                           { return DIRECTIVE_EXTERN; }
".section"                          { return DIRECTIVE_SECTION; }
".word"                             { return DIRECTIVE_WORD; }
".skip"                             { return DIRECTIVE_SKIP; }
".ascii"                            { return DIRECTIVE_ASCII; }
".equ"                              { return DIRECTIVE_EQU; }
".end"                              { return DIRECTIVE_END; }
[a-zA-Z_][a-zA-Z0-9_]*[ \t]*:       {
    yylval.label = strdup(yytext);
    if (yylval.label == NULL) {
        return YYerror;
    }
    int i = 0;
    while (yylval.label[i] != '\0') {
        char c = yylval.label[i];
        if (c == '\t' || c == ' ' || c == ':') {
            yylval.label[i] = '\0';
            break;
        }
        ++i;
    }
    return LABEL;
}
r[0-7]                              { yylval.reg = atoi(yytext + 1); return REG; }
sp                                  { yylval.reg = 6; return REG; }
pc                                  { yylval.reg = 7; return REG; }
psw                                 { yylval.reg = 8; return REG; }
0                                   { yylval.num = 0; return NUM; }
[1-9][0-9]*                         { yylval.num = atoi(yytext); return NUM; }
0[0-9]+                             { yylval.num = strtol(yytext + 1, NULL, 8); return NUM; }
0x[0-9a-fA-F]+                      { yylval.num = strtol(yytext + 2, NULL, 16); return NUM; }
\"[^"]+\"                           { yytext[strlen(yytext)-1] = '\0'; yylval.sym = strdup(yytext + 1); return STRING; }
[a-zA-Z_][a-zA-Z0-9_]*              { yylval.sym = strdup(yytext); if (yylval.sym == NULL) return YYerror; return SYM; }
\n                                  { ++lineNumber; BEGIN(INITIAL); return ENDL; }
.                                   ;
%%
