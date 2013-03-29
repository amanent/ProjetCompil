%token CLASS EXT IS DEF OVR STAT RET RETS AS VAR NEW
%token IF THEN ELSE
%token AFF
%token ID IDCL
%token CST STR
%token RELOP
%token ADD SUB MUL DIV CONCAT
/* ---- pour l'arbre syntaxique --- */
%token DECL LSTARG BLCDECL CAST INST MSGSNT LAFFECT LSTINST
/* --------------------------------- */

%nonassoc RELOP CONCAT
%left ADD SUB
%left MUL DIV
%left UNARYADD UNARYSUB

%type <T> AffectO ListArgO ListArg BlocO Bloc ListInstO ListInst Inst Exp Exp2 LeftAffect DeclV ListDeclV
%type <S> ReturnO Id Idcl 
%type <I> StaticO OvOrStatO Relop
%type <P> ListParamO ListParam Param
/*No type : Program Class ExtendO ListDeclO Decl DeclField DeclMethod  */



%{
#include <stdio.h>
#include "proj.h"
#include "class.h"
#include "function.h"

extern ClassListP classList; /* variable globale contenant les classes déclarées */

extern int yylineno;
extern int yylex();	/* fournie par Flex */

void yyerror(char *ignore) {
  printf("erreur de syntaxe: Ligne %d\n", yylineno);
}

%}

%%

Program		:	Bloc										{ /*lancer la verif contextuelle */ }
			|	Class Program								/* Pas de traitement */
			;

Class 		:	CLASS Idcl '(' ListParamO ')' ExtendO BlocO IS '{' ListDeclO '}' {
																classList_addClass($2);
																class_setConstructor(classList->current, $4);
															}
			;

ListParamO 	:	/* epsilon */								{ $$ = NULL; }
			|	ListParam									{ $$ = $1; }
			;

ListParam	:	Param										{ $$ = $1; }
			| 	Param ',' ListParam							{
																ParamsListP tmp = $1;
																tmp->next = $3;
																$$=tmp;
															}
			;

Param		:	Id ':' Idcl									{ $$ = function_makeParam($1, $3); }
			;

ExtendO		:	/* epsilon */								/* Pas de traitement */
			|	EXT Idcl '(' ListArgO ')'					{ class_addParent(classList->current, $2, $4); /* troisiemme paramètres, les paramètres passés par le constructeru au parent */ }
			;

ListDeclO	:	/* epsilon */								/* Pas de traitement */
			|	Decl ListDeclO								/* Pas de traitement */
			;

Decl		:	DeclField									/* Pas de traitement */
			|	DeclMethod									/* Pas de traitement */
			;

DeclField	:	StaticO DeclV								{ class_addVar($1, $2); }
			;

StaticO		:	/* epsilon */								{ $$ = 0; }
			|	STAT										{ $$ = 1; }
			;

DeclMethod	:	OvOrStatO	DEF	Id '(' ListParamO ')' ReturnO IS Bloc {
																class_addMethod($1, $3, $7, $5, $9);
																/* static/overide/rien, nom, type de retour,liste des paramètres, arbre du corps de la fonction */
															}
			;

OvOrStatO	:	/* epsilon */								{ $$ = 0; }
			|	OVR											{ $$ = 1; }
			|	STAT										{ $$ = 2; }
			;

ReturnO		:	/* epsilon */								{ $$ = NULL;}
			|	RETS Idcl									{ $$ = $2;}
			;

/* ------------------------------------------------------ Fin creation structures, debut creation arbres --------------------------------------------- */

ListDeclV	:	DeclV										{ $$ = $1; }
			|	DeclV ListDeclV								{ $$ = makeTree(DECL, 2, $1, $2); }
			;

DeclV		:	VAR Id ':' Idcl AffectO						{ $$ = makeTree(VAR, 3, $2, $4, $5); } /* voir a pas ajouter un autre type "variable" aux feuilles de l'arbre */
			;
			
AffectO		:	/* epsilon */								{ $$ = NULL; }
			|	AFF Exp										{ $$ = $2; }
			;

ListArgO	:	/* epsilon */								{ $$ = NULL; }
			|	ListArg										{ $$ = $1; }
			;

ListArg		:	Exp											{ $$ = $1; }
			|	Exp ',' ListArg								{ $$ = makeTree(LSTARG, 2, $1, $3); }
			;

BlocO		:	/* epsilon */								{ $$ = NULL; } /* voir a peut etre passer par des leafs avec un code particulier pour eviter les segflt */
			|	Bloc										{ $$ = $1; }
			;

Bloc		:	'{' ListInstO '}'							{ $$ = $2; }
			|	'{' ListDeclV IS ListInst '}'				{ $$ = makeTree(BLCDECL, 2, $2, $4); }
			;

ListInstO	:	/* epsilon */								{ $$ = NULL; }
			|	ListInst									{ $$ = $1; }
			;

ListInst	:	Inst										{ $$ = $1; }
			|	Inst ListInst								{ $$ = makeTree(LSTINST, 2,  $1, $2); }
			;

Inst		:	Exp ';'										{ $$ = $1; }
			|	Bloc										{ $$ = $1; }
			|	RET ';'										{ $$ = makeLeafInt(RET, 0); /* 0 a defaut de savoir quoi mettre*/ }
			|	LeftAffect AFF Exp ';' /* Affectation */	{ $$ = makeTree(AFF, 2, $1, $3); }
			|	IF Exp THEN Inst ELSE Inst					{ $$ = makeTree(IF, 3, $2, $4, $6); }
			;

Exp			:	Exp Relop Exp %prec RELOP 					{ $$ = makeTree($2, 2, $1, $3); }
			|	Exp CONCAT Exp								{ $$ = makeTree(CONCAT, 2, $1, $3); }
			|	Exp ADD Exp									{ $$ = makeTree(ADD, 2, $1, $3); }
			|	Exp SUB Exp									{ $$ = makeTree(SUB, 2, $1, $3); }
			|	Exp MUL Exp									{ $$ = makeTree(MUL, 2, $1, $3); }
			|	Exp DIV Exp									{ $$ = makeTree(DIV, 2, $1, $3); }
			|	ADD Exp %prec UNARYADD						{ $$ = makeTree(UNARYADD, 1, $2); }
			|	SUB Exp %prec UNARYSUB						{ $$ = makeTree(UNARYSUB, 1, $2); }
			|	Exp2										{ $$ = $1; }
			;

Exp2		:	'(' Exp ')'									{ $$ = $2; } 
			|	'(' AS Idcl ':' Exp ')'						{ $$ = makeTree(CAST, 2, makeLeafStr(IDCL, $3), $5); }
			|	NEW Idcl '(' ListArgO ')'					{ $$ = makeTree(INST, 2, makeLeafStr(IDCL, $2), $4); }
			|	Exp2 '.' Id '(' ListArgO ')'				{ $$ = makeTree(MSGSNT, 3, $1, makeLeafStr(ID, $3), $5); }
			| 	LeftAffect									{ $$ = $1; }
			|	CST											{ $$ = makeLeafInt(CST, yyval.I); }
			|	STR											{ $$ = makeLeafStr(STR, yyval.S); }
			;

LeftAffect	:	Exp2 '.' Id									{ $$ = makeTree(LAFFECT, 2, $1, makeLeafStr(ID, $3)); }
			|	Id											{ $$ = makeLeafStr(ID, $1); }
			;

Id 			: 	ID											{ $$ = yyval.S; }
			;

Idcl		:	IDCL										{ $$ = yyval.S; }
			;

Relop		:	RELOP										{ $$ = yyval.I; }
			;
