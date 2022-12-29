package rs.etf.pp1.lex;

import java_cup.runtime.Symbol;
import org.apache.log4j.Logger;
import rs.etf.pp1.syntax.sym;
import rs.etf.pp1.mj.runtime.Code;

@SuppressWarnings("unused")
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
/* "enum"		{ return newSymbol(sym.ENUM, yytext()); 	} */
"else"			{ return newSymbol(sym.ELSE, yytext()); 	}
"const"			{ return newSymbol(sym.CONST, yytext()); 	}
"if"			{ return newSymbol(sym.IF, yytext()); 		}
/* "do"			{ return newSymbol(sym.DO, yytext()); 		} */
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
"*"				{ return newSymbol(sym.MULOP, Code.mul); 	}
"/"				{ return newSymbol(sym.MULOP, Code.div); 	}
"%"				{ return newSymbol(sym.MULOP, Code.rem); 	}
"=="			{ return newSymbol(sym.RELOP, Code.eq); 	}
"!="			{ return newSymbol(sym.RELOP, Code.ne); 	}
">="			{ return newSymbol(sym.RELOP, Code.ge);		}
">"				{ return newSymbol(sym.RELOP, Code.gt);		}
"<="			{ return newSymbol(sym.RELOP, Code.le);		}
"<"				{ return newSymbol(sym.RELOP, Code.lt);		}
"&&"			{ return newSymbol(sym.AND, yytext()); 		}
"||"			{ return newSymbol(sym.OR, yytext()); 		}
"=>"			{ return newSymbol(sym.LAMBDA, yytext()); 	}
"="				{ return newSymbol(sym.ASSIGN, yytext());	}
"++"			{ return newSymbol(sym.UPLUS, yytext()); 	}
"+"				{ return newSymbol(sym.ADDOP, Code.add); 	}
"--"			{ return newSymbol(sym.UMINUS, yytext()); 	}
"-"				{ return newSymbol(sym.ADDOP, Code.sub); 	}
";"				{ return newSymbol(sym.SEMI, yytext()); 	}
/* ":"			{ return newSymbol(sym.COLON, yytext()); 	} */
","				{ return newSymbol(sym.COMMA, yytext()); 	}
"."				{ return newSymbol(sym.PERIOD, yytext()); 	}
"("				{ return newSymbol(sym.LPAREN, yytext()); 	}
")"				{ return newSymbol(sym.RPAREN, yytext()); 	}
"["				{ return newSymbol(sym.LBRACKET, yytext());	}
"]"				{ return newSymbol(sym.RBRACKET, yytext());	}
"{"				{ return newSymbol(sym.LBRACE, yytext()); 	}
"}"				{ return newSymbol(sym.RBRACE, yytext()); 	}

/* Tokens */
"true"					{ return newSymbol(sym.BOOL, true); 	}
"false"					{ return newSymbol(sym.BOOL, false); 	}
[0-9]+  				{ return newSymbol(sym.NUMBER, Integer.valueOf(yytext()));	}
['].[']					{ return newSymbol(sym.CHARCONST, yytext().charAt(1));		}
[a-zA-Z][a-zA-Z0-9_]*	{ return newSymbol(sym.IDENT, yytext());					}

. 						{ throw new RuntimeException("Lexical error at character " + yytext() + " (line " + (yyline + 1) + ", column " + (yycolumn + 1) + ")"); }
