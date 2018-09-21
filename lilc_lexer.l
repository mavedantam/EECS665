%{
#include <string>
#include <limits.h>

/* Provide custom yyFlexScanner subclass and specify the interface */
#include "lilc_scanner.hpp"
#undef  YY_DECL
#define YY_DECL int LILC::LilC_Scanner::yylex( LILC::LilC_Parser::semantic_type * const lval)

/* typedef to make the returns for the tokens shorter */
using TokenTag = LILC::LilC_Parser::token;

/*
Implementations of the non-nullary tokens. These classes are declared
in symbols.hpp and are subclasses of the main Symbol class representing
terminals that contain some value (e.g., a token that contains an integer
value as opposed to a curly brace which always represents exactly 1
literal character string)
 */
namespace LILC{
	IDToken::IDToken(size_t line, size_t col, std::string value)
	: SynSymbol(line,col,TokenTag::ID)
	{
		this->_value = value;
	}
	IntLitToken::IntLitToken(size_t line, size_t col, int value)
	: SynSymbol(line,col,TokenTag::INTLITERAL)
	{
		this->_value = value;
	}
	StringLitToken::StringLitToken(size_t line, size_t col, std::string value)
	: SynSymbol(line,col,TokenTag::STRINGLITERAL)
	{
		this->_value = value;
	}
} // End namespace



/* define yyterminate as this instead of NULL */
#define yyterminate() return( TokenTag::END )

/* Exclude unistd.h for Visual Studio compatability. */
#define YY_NO_UNISTD_H

%}

%option debug
%option nodefault
%option yyclass="LILC::LilC_Scanner"
%option noyywrap
%option c++

DIGIT [0-9]
WHITESPACE   [ \t]

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

{DIGIT}+	{
		//Note: the following computation of the integer value
		// does NOT check for overflow. This must be changed
		int intVal = atoi(yytext);
                yylval->symbolValue = new IntLitToken(lineNum, charNum, intVal);
		charNum += yyleng;
                return TokenTag::INTLITERAL;
		}

\n          {
		// Update line number
		lineNum++;
		charNum = 1;
            }


{WHITESPACE}+	{
		charNum += yyleng;
	    	}

"{"		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::LCURLY);
		charNum++;
		return TokenTag::LCURLY;
	    	}

"}"		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::RCURLY);
		charNum++;
		return TokenTag::RCURLY;
	    	}

"("		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::LPAREN);
		charNum++;
		return TokenTag::LPAREN;
	    	}

")"		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::RPAREN);
		charNum++;
		return TokenTag::RPAREN;
	    	}

";"		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::SEMICOLON);
		charNum++;
		return TokenTag::SEMICOLON;
	    	}

","		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::COMMA);
		charNum++;
		return TokenTag::COMMA;
	    	}

"."		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::DOT);
		charNum++;
		return TokenTag::DOT;
	    	}

"<<"		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::WRITE);
		charNum++;
		return TokenTag::WRITE;
	    	}

">>"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::READ);
		charNum++;
		return TokenTag::READ;
	    	}

"++"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::PLUSPLUS);
		charNum++;
		return TokenTag::PLUSPLUS;
	    	}

"--"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::MINUSMINUS);
		charNum++;
		return TokenTag::MINUSMINUS;
	    	}

"+"		{
		yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::PLUS);
		charNum++;
		return TokenTag::PLUS;
	    	}

"-"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::MINUS);
		charNum++;
		return TokenTag::MINUS;
	    	}

"*"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::TIMES);
		charNum++;
		return TokenTag::TIMES;
	    	}

"/"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::DIVIDE);
		charNum++;
		return TokenTag::DIVIDE;
	    	}

"!"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::NOT);
		charNum++;
		return TokenTag::NOT;
	    	}

"&&"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::AND);
		charNum++;
		return TokenTag::AND;
	    	}

"||"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::OR);
		charNum++;
		return TokenTag::OR;
	    	}

"=="		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::EQUALS);
		charNum++;
		return TokenTag::EQUALS;
	    	}

"!="		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::NOTEQUALS);
		charNum++;
		return TokenTag::NOTEQUALS;
	    	}

"<"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::LESS);
		charNum++;
		return TokenTag::LESS;
	    	}

">"		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::GREATER);
		charNum++;
		return TokenTag::GREATER;
	    	}

"<="		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::LESSEQ);
		charNum++;
		return TokenTag::LESSEQ;
	    	}

">="		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::GREATEREQ);
		charNum++;
		return TokenTag::GREATEREQ;
	    	}

"="		{
	  yylval->symbolValue = new NullaryToken(lineNum, charNum, TokenTag::ASSIGN);
		charNum++;
		return TokenTag::ASSIGN;
	    	}

.           {
		std::string msg = "Ignoring illegal character: ";
		msg += yytext;
		charNum += yyleng;
		error(lineNum, charNum,msg);
            }
%%
