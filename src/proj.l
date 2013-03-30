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
	#include <stdio.h> /* Pour fileno */
	#include <string.h> /* Pour strdup */

	#include "proj.h"
	#include "proj_y.hpp"

	#define YY_NO_INPUT /* pour éviter le warning "input declared but unused" */

	extern char *strdup(const char *s);
	extern int fileno(FILE* f); /* pour éviter le warning "finelo implicitely declared" */

	extern YYSTYPE yylval;
	extern bool noEval;

	int keywordOrId() {
		if(!strcmp(yytext,"if")) return(IF);
		if(!strcmp(yytext,"then")) return(THEN);
		if(!strcmp(yytext,"else")) return(ELSE);
		if(!strcmp(yytext,"class")) return(CLASS);
		if(!strcmp(yytext,"extends")) return(EXT);
		if(!strcmp(yytext,"is")) return(IS);
		if(!strcmp(yytext,"def")) return(DEF);
		if(!strcmp(yytext,"override")) return(OVR);
		if(!strcmp(yytext,"static")) return(STAT);
		if(!strcmp(yytext,"return")) return(RET);
		if(!strcmp(yytext,"returns")) return(RETS);
		if(!strcmp(yytext,"as")) return(AS);
		if(!strcmp(yytext,"var")) return(VAR);
		if(!strcmp(yytext,"new")) return(NEW);
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
{ClassID}		{ yylval.S = strdup(yytext); return(IDCL); }
{NUMBER}+		{ yylval.I = atoi(yytext); return(CST); }
{Symbol}		{ return(yytext[0]); }
{Str}			{ yylval.S = strdup(yytext); return(STR); }
":="			{ return(AFF); }
"+"             { return(ADD); }
"-"             { return(SUB); }
"*"             { return(MUL); }
"/"	            { return(DIV); }
">"				{ yylval.I = GT; return(RELOP); }
">="			{ yylval.I = GE; return(RELOP); }
"<"				{ yylval.I = LT; return(RELOP); }
"<="			{ yylval.I = LE; return(RELOP); }
"<>"			{ yylval.I = NE; return(RELOP); }
"="				{ yylval.I = EQ; return(RELOP); }
"&"				{ return(CONCAT); }
.				{ lexError(yytext[0]);}
%%
