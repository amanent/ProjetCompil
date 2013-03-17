NUMBER [0-9]
UPPER [A-Z]
LOWER [a-z]
Star \*
NotStar [^*]
NotStarSlash [^*/]
LETTER ({UPPER}|{LOWER})
ClassID ({UPPER}({LETTER}|{NUMBER})*)
DefaultID ({LOWER}({LETTER}|{NUMBER})*)
Symbol [{},;()\.:]
Quote "\""
StrChar [^\\"\n]
StrEsc \\.
Str ({Quote}({StrChar}|{StrEsc})*{Quote})
Delim [ \n\t\r]
Commentary ([/]{Star}({NotStar}|{Star}*{NotStarSlash})*{Star}*[*][/])


%{
#include <string.h>
#include "tp.h"
#include "tp_y.h"

extern char *strdup(const char *s);

extern YYSTYPE yylval;
extern bool noEval;

int keywordOrId() {
	if(!strcmp(yytext,"if")) return(IF);
	if(!strcmp(yytext,"then")) return(THEN);
	if(!strcmp(yytext,"else")) return(ELSE);
	yylval.S = strdup(yytext);
	return(ID);
}


void lexError(char c) {
  fprintf(stderr, "Skipping invalid character: '%c' on line %d\n", c, yylineno);
}
%}

%%

{Delim}			{ }
{Commentary}	{ }
{DefaultID}		{ return keywordOrId(); }
{ClassID}		{ return keywordOrId(); }
{NUMBER}+		{ yylval.I = strtol(yytext,NULL,0); return(CST); }
{Symbol}		{ return(yytext[0]); }
{Str}			{ yylval.S = strdup(yytext); return(STR); }
":="			{ return(AFF); }
"+"             { return(ADD); }
"-"             { return(SUB); }
"*"             { return(MUL); }
"/"	            { return(DIV); }
">"				{ return(RELOP); }
">="			{ return(RELOP); }
"<"				{ return(RELOP); }
"<="			{ return(RELOP); }
"<>"			{ return(RELOP); }
"="				{ return(RELOP); }
"&"				{ return(AND); }
.				{ lexError(yytext[0]);}
%%