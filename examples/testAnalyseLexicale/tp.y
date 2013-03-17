%token IF THEN ELSE
%token AFF
%token ID STR
%token CST
%token RANGE
%token RELOP
%token AND

%nonassoc ELSE
%left ADD SUB
%left MUL DIV

%{
#include "tp.h"     /* les definition des types et les etiquettes des noeuds */

extern int yylex();	/* fournie par Flex */
extern void yyerror();  /* definie dans tp.c */
%}

%% 
programme : ADD  
;
%%