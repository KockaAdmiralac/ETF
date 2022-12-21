package rs.etf.pp1.lex;

import java_cup.runtime.Symbol;
import org.apache.log4j.Logger;
import rs.etf.pp1.syntax.sym;

%%

%{

	Logger logger = Logger.getLogger(Yylex.class);

	private Symbol newSymbol(int type) {
		return new Symbol(type, yyline+1, yycolumn);
	}

	private Symbol newSymbol(int type, Object value) {
		return new Symbol(type, yyline+1, yycolumn, value);
	}

%}

%cup
%line
%column
%public

%eofval{
	return newSymbol(sym.EOF);
%eofval}

%%

/* Ignore blank characters and comments */
" "				{ }
"\b"			{ }
"\t"			{ }
"\r"			{ }
"\n"			{ }
"\f"			{ }
"//" .* "\n"	{ }

/* Keywords */
"program"		{ return newSymbol(sym.PROG, yytext());		}
"break"			{ return newSymbol(sym.BREAK, yytext()); 	}
"class"			{ return newSymbol(sym.CLASS, yytext()); 	}
"enum"			{ return newSymbol(sym.ENUM, yytext()); 	}
"else"			{ return newSymbol(sym.ELSE, yytext()); 	}
"const"			{ return newSymbol(sym.CONST, yytext()); 	}
"if"			{ return newSymbol(sym.IF, yytext()); 		}
"do"			{ return newSymbol(sym.DO, yytext()); 		}
"while"			{ return newSymbol(sym.WHILE, yytext()); 	}
"new"			{ return newSymbol(sym.NEW, yytext()); 		}
"print"			{ return newSymbol(sym.PRINT, yytext()); 	}
"read"			{ return newSymbol(sym.READ, yytext()); 	}
"return"		{ return newSymbol(sym.RETURN, yytext()); 	}
"void"			{ return newSymbol(sym.VOID, yytext()); 	}
"extends"		{ return newSymbol(sym.EXTENDS, yytext()); 	}
"continue"		{ return newSymbol(sym.CONTINUE, yytext()); }
"foreach"		{ return newSymbol(sym.FOREACH, yytext());	}

/* Operators */
"+"				{ return newSymbol(sym.PLUS, yytext()); 	}
"-"				{ return newSymbol(sym.MINUS, yytext()); 	}
"*"				{ return newSymbol(sym.TIMES, yytext()); 	}
"/"				{ return newSymbol(sym.SLASH, yytext()); 	}
"%"				{ return newSymbol(sym.MODULO, yytext()); 	}
"=="			{ return newSymbol(sym.EQU, yytext()); 		}
"!="			{ return newSymbol(sym.NEQ, yytext()); 		}
">"				{ return newSymbol(sym.GRT, yytext());		}
">="			{ return newSymbol(sym.GEQ, yytext());		}
"<"				{ return newSymbol(sym.LSS, yytext());		}
"<="			{ return newSymbol(sym.LEQ, yytext());		}
"&&"			{ return newSymbol(sym.AND, yytext()); 		}
"||"			{ return newSymbol(sym.OR, yytext()); 		}
"="				{ return newSymbol(sym.ASSIGN, yytext());	}
"++"			{ return newSymbol(sym.UPLUS, yytext()); 	}
"--"			{ return newSymbol(sym.UMINUS, yytext()); 	}
";"				{ return newSymbol(sym.SEMI, yytext()); 	}
":"				{ return newSymbol(sym.COLON, yytext()); 	}
","				{ return newSymbol(sym.COMMA, yytext()); 	}
"."				{ return newSymbol(sym.PERIOD, yytext()); 	}
"("				{ return newSymbol(sym.LPAREN, yytext()); 	}
")"				{ return newSymbol(sym.RPAREN, yytext()); 	}
"["				{ return newSymbol(sym.LBRACKET, yytext());	}
"]"				{ return newSymbol(sym.RBRACKET, yytext());	}
"{"				{ return newSymbol(sym.LBRACE, yytext()); 	}
"}"				{ return newSymbol(sym.RBRACE, yytext()); 	}
"=>"			{ return newSymbol(sym.LAMBDA, yytext()); 	}

/* Tokens */
"true"					{ return newSymbol(sym.BOOL, true); 	}
"false"					{ return newSymbol(sym.BOOL, false); 	}
[0-9]+  				{ return newSymbol(sym.NUMBER, Integer.valueOf(yytext()));	}
['].[']					{ return newSymbol(sym.CHARCONST, yytext().charAt(1));		}
[a-zA-Z][a-zA-Z0-9_]*	{ return newSymbol(sym.IDENT, yytext());					}

. 						{ logger.error("Lexical error (" + yytext() + ") at line " + (yyline + 1) + " and column " + (yycolumn + 1)); }
