%token CLASS EXT IS DEF OVR STAT RET RETS AS VAR NEW
%token IF THEN ELSE
%token AFF
%token ID IDCL
%token CST STR
%token RELOP
%token ADD SUB MUL DIV CONCAT
/* ---- pour l'arbre syntaxique --- */
%token DECL LSTARG BLCDECL CAST INST MSGSNT SELECT LSTINST
/* --------------------------------- */

%nonassoc RELOP CONCAT
%left ADD SUB 
%left MUL DIV
%left UNARYADD UNARYSUB

%type <T> AffectO ListArgO ListArg BlocO Bloc ListInstO ListInst Inst Exp Exp2 LeftAffect DeclV ListDeclV
%type <S> ReturnO Id Idcl 
%type <I> StaticO OvOrStatO Relop
%type <P> ListParamO ListParam Param
/*No type : Program Class ClassAlloc ExtendO ListDeclO Decl DeclField DeclMethod  */



%{
#include <stdio.h>
#include "proj.h"
#include "class.h"
#include "function.h"

#define NOVERBOSE

extern int yylineno;
extern int yylex();	/* fournie par Flex */
extern TreeP mainCode;
ClassP current;


void yyerror(char *ignore) {
  printf("erreur de syntaxe: Ligne %d\n", yylineno);
}

void pprintf(char *c) {
#ifdef VERBOSE
	printf("%s", c);
#endif
}
void pprintfs(char* c, char* c2) {
#ifdef VERBOSE
	printf("%s %s\n", c, c2);
#endif
}
void pprintfi(char* c, int i) {
#ifdef VERBOSE
	printf("%s %i\n", c, i);
#endif
}
/* Méthodes utilisées : 
	classList_addClass($2);  (nom de la classe)
	class_setConstructor(classList->current, $4, $7);  (classe, paramètres constructeur, code du constructeur)
	function_makeParam($1, $3); (params: nomParam, typeParam)
	class_setSuper(classList->current, $2, $4); (params: classe, superType, arguments constructeur père)
	class_addVar(classList->current, $1, $2); (params: classe, isStatic, arbre de decl de la var)
	class_addMethod($1, $3, $7, $5, $9); (params: visibility, nom, type de retour,liste des paramètres, arbre du corps de la fonction)
*/

%}

%%
Program		:	Bloc										{	pprintf("prog bloc\n");
																mainCode = $1;
																/*lancer la verif contextuelle */ 
															}
			|	Class Program								{ pprintf("prog class\n"); } /* Pas de traitement */
			;

Class 		:	ClassAlloc Idcl '(' ListParamO ')' ExtendO BlocO IS '{' ListDeclO '}' {
																pprintf("class\n");
																class_setName(current, $2); /*param: nom de la classe */
																class_setConstructor(current, $4, $7); 
																/*params: classe, paramètres constructeur, code du constructeur */
																/* superclasse gérée dans ExtendO */
																/* declarations gérées dans ListDeclO */
																classList_addClass(current);
															}
			;

ClassAlloc	:	CLASS										{ pprintf("class alloc\n"); current = NEW(1, Class); } /* uniquement pour faire l'allocation */

ListParamO 	:	/* epsilon */								{ pprintf("listparamo null\n"); $$ = NULL; }
			|	ListParam									{ pprintf("listparamo non null\n"); $$ = $1; }
			;

ListParam	:	Param										{ pprintf("listparam final\n"); $$ = $1; }
			| 	Param ',' ListParam							{
																pprintf("listparam continue\n"); 
																ParamsListP tmp = $1;
																tmp->next = $3;
																$$=tmp;
															}
			;

Param		:	Id ':' Idcl									{ pprintf("param\n"); $$ = function_makeParam($1, $3); /*params: nomParam, typeParam */ }
			;

ExtendO		:	/* epsilon */								{ pprintf("extendo null\n");} /* Pas de traitement */
			|	EXT Idcl '(' ListArgO ')'					{ pprintf("extendo non null\n"); class_setSuper(current, $2, $4); /*params: classe, superType, arguments constructeur père */ }
			;

ListDeclO	:	/* epsilon */								{ pprintf("listdeclo null\n");} /* Pas de traitement */
			|	Decl ListDeclO								{ pprintf("listdeclo non null\n");} /* Pas de traitement */
			;

Decl		:	DeclField									{ pprintf("decl field\n");} /* Pas de traitement */
			|	DeclMethod									{ pprintf("decl method\n");} /* Pas de traitement */
			;

DeclField	:	StaticO DeclV								{ pprintf("declField\n"); class_addField(current, $1, $2); /*params: classe, isStatic, arbre de decl de la var */ }
			;

StaticO		:	/* epsilon */								{ pprintf("statico null\n"); $$ = 0; }
			|	STAT										{ pprintf("statico non null\n"); $$ = 1; }
			;

DeclMethod	:	OvOrStatO	DEF	Id '(' ListParamO ')' ReturnO IS Bloc {
																pprintf("declmethod\n"); 
																class_addMethod(current, $1, $3, $7, $5, $9);
																/*params: classe, visibility, nom, type de retour,liste des paramètres, arbre du corps de la fonction */
															}
			;

OvOrStatO	:	/* epsilon */								{ pprintf("ovorstat null\n"); $$ = 0; }
			|	OVR											{ pprintf("ovorstat ovr\n"); $$ = 1; }
			|	STAT										{ pprintf("ovorstat stat\n"); $$ = 2; }
			;

ReturnO		:	/* epsilon */								{ pprintf("returno null\n"); $$ = NULL;}
			|	RETS Idcl									{ pprintf("returno non null\n"); $$ = $2;}
			;

/* ------------------------------------------------------ Fin creation structures, debut creation arbres --------------------------------------------- */

ListDeclV	:	DeclV										{ pprintf("listdeclv final\n"); $$ = $1; }
			|	DeclV ListDeclV								{ pprintf("listdeclv continue\n"); $$ = makeTree(DECL, 2, $1, $2); }
			;

DeclV		:	VAR Id ':' Idcl AffectO						{	pprintf("declv\n");
																$$ = makeTree(VAR, 3, makeLeafStr(ID, $2), makeLeafStr(IDCL, $4), $5);
																/* voir a pas ajouter un autre type "variable" aux feuilles de l'arbre */
															} 
			;
			
AffectO		:	/* epsilon */								{ pprintf("affect null\n"); $$ = NULL; }
			|	AFF Exp	';'									{ pprintf("affect non null\n"); $$ = $2; }
			;

ListArgO	:	/* epsilon */								{ pprintf("listargo null\n"); $$ = NULL; }
			|	ListArg										{ pprintf("listargo non null\n"); $$ = $1; }
			;

ListArg		:	Exp											{ pprintf("list arg final\n"); $$ = $1; }
			|	Exp ',' ListArg								{ pprintf("list arg continue\n"); $$ = makeTree(LSTARG, 2, $1, $3); }
			;

BlocO		:	/* epsilon */								{ pprintf("bloco null\n"); $$ = NULL; } /* voir a peut etre passer par des leafs avec un code particulier pour eviter les segflt */
			|	Bloc										{ pprintf("bloco non null\n"); $$ = $1; }
			;

Bloc		:	'{' ListInstO '}'							{ pprintf("bloc final\n"); $$ = $2; }
			|	'{' ListDeclV IS ListInst '}'				{ pprintf("bloc continue\n"); $$ = makeTree(BLCDECL, 2, $2, $4); }
			;

ListInstO	:	/* epsilon */								{ pprintf("listinstO null\n"); $$ = NULL; }
			|	ListInst									{ pprintf("listinstO non null\n"); $$ = $1; }
			;

ListInst	:	Inst										{ pprintf("listinst final\n"); $$ = $1; }
			|	Inst ListInst								{ pprintf("listinst continue\n"); $$ = makeTree(LSTINST, 2,  $1, $2); }
			;

Inst		:	Exp ';'										{ pprintf("inst1\n"); $$ = $1; }
			|	Bloc										{ pprintf("inst2\n"); $$ = $1; }
			|	RET ';'										{ pprintf("inst3\n"); $$ = makeLeafInt(RET, 0); /* 0 a defaut de savoir quoi mettre*/ }
			|	LeftAffect AFF Exp ';' /* Affectation */	{ pprintf("inst4\n"); $$ = makeTree(AFF, 2, $1, $3); }
			|	IF Exp THEN Inst ELSE Inst					{ pprintf("inst5\n"); $$ = makeTree(IF, 3, $2, $4, $6); }
			;

Exp			:	Exp Relop Exp %prec RELOP 					{ pprintf("exp1\n"); $$ = makeTree($2, 2, $1, $3); }
			|	Exp CONCAT Exp								{ pprintf("exp2\n"); $$ = makeTree(CONCAT, 2, $1, $3); }
			|	Exp ADD Exp									{ pprintf("exp3\n"); $$ = makeTree(ADD, 2, $1, $3); }
			|	Exp SUB Exp									{ pprintf("exp4\n"); $$ = makeTree(SUB, 2, $1, $3); }
			|	Exp MUL Exp									{ pprintf("exp5\n"); $$ = makeTree(MUL, 2, $1, $3); }
			|	Exp DIV Exp									{ pprintf("exp6\n"); $$ = makeTree(DIV, 2, $1, $3); }
			|	ADD Exp %prec UNARYADD						{ pprintf("exp7\n"); $$ = makeTree(UNARYADD, 1, $2); }
			|	SUB Exp %prec UNARYSUB						{ pprintf("exp8\n"); $$ = makeTree(UNARYSUB, 1, $2); }
			|	Exp2										{ pprintf("exp9\n"); $$ = $1; }
			;

Exp2		:	'(' Exp ')'									{ pprintf("exp21\n"); $$ = $2; } 
			|	'(' AS Idcl ':' Exp ')'						{ pprintf("exp22\n"); $$ = makeTree(CAST, 2, makeLeafStr(IDCL, $3), $5); }
			|	NEW Idcl '(' ListArgO ')'					{ pprintf("exp23\n"); $$ = makeTree(INST, 2, makeLeafStr(IDCL, $2), $4); }
			|	Exp2 '.' Id '(' ListArgO ')'				{ pprintf("exp24\n"); $$ = makeTree(MSGSNT, 3, $1, makeLeafStr(ID, $3), $5); }
			| 	LeftAffect									{ pprintf("exp25\n"); $$ = $1; }
			|	CST											{ pprintf("exp26\n"); $$ = makeLeafInt(CST, yyval.I); }
			|	STR											{ pprintf("exp27\n"); $$ = makeLeafStr(STR, yyval.S); }
			;

LeftAffect	:	Exp2 '.' Id									{ pprintf("left affect\n"); $$ = makeTree(SELECT, 2, $1, makeLeafStr(ID, $3)); }
			|	Id											{ pprintf("left affect2\n"); $$ = makeLeafStr(ID, $1); }
			;

Id 			: 	ID											{ pprintfs("id", yyval.S); $$ = yyval.S; }
			;

Idcl		:	IDCL										{ pprintfs("idcl", yyval.S); $$ = yyval.S; }
			;

Relop		:	RELOP										{ pprintfi("relop", yyval.I); $$ = yyval.I; }
			;
