%token CLASS EXT IS DEF OVR STAT RET RETS AS VAR NEW
%token IF THEN ELSE
%token AFF
%token ID IDCL
%token CST STR
%token RELOP
%token ADD SUB MUL DIV CONCAT
/* ---- pour l'arbre syntaxique --- */
%token DECL LSTARG BLCDECL CAST INSTA INSTR MSGSNT MSGSNTS SELECT LSTINST CMPAFF DIRAFF 
/* --------------------------------- */

%nonassoc RELOP 
%left ADD SUB CONCAT
%left MUL DIV
%left UNARYADD UNARYSUB

%type <T> AffectO ListArgO ListArg BlocO Bloc ListInstO ListInst Inst DeclV ListDeclV Affect Exp Exp2
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
extern int yychar;
extern int yylex();	/* fournie par Flex */
extern TreeP mainCode;
ClassP current;


void yyerror(char *ignore) {
  printf("erreur de syntaxe: Ligne %d : %d unexpected\n", yylineno, yychar);
}

void pprintf(char *c) {
#ifdef VERBOSE
	printf("--l%d : %s\n", yylineno, c);
#endif
}
void pprintfs(char* c, char* c2) {
#ifdef VERBOSE
	printf("--l%d : %s %s\n", yylineno, c, c2);
#endif
}
void pprintfi(char* c, int i) {
#ifdef VERBOSE
	printf("--l%d : %s %i\n", yylineno, c, i);
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
Program		:	Bloc										{	pprintf("prog bloc");
																mainCode = $1;
															}
			|	Class Program								{ pprintf("prog class"); } /* Pas de traitement */
			;

Class 		:	ClassAlloc Idcl '(' ListParamO ')' ExtendO BlocO IS '{' ListDeclO '}' {
																pprintf("class");
																class_setName(current, $2); /*param: nom de la classe */
																class_setConstructor(current, $4, $7); 
																/*params: classe, paramètres constructeur, code du constructeur */
																/* superclasse gérée dans ExtendO */
																/* declarations gérées dans ListDeclO */
																classList_addClass(current);
															}
			;

ClassAlloc	:	CLASS										{ pprintf("class alloc"); current = NEW(1, Class); } /* uniquement pour faire l'allocation */

ListParamO 	:	/* epsilon */								{ pprintf("listparamo null"); $$ = NULL; }
			|	ListParam									{ pprintf("listparamo non null"); $$ = $1; }
			;

ListParam	:	Param										{ pprintf("listparam final"); $$ = $1; }
			| 	Param ',' ListParam							{
																pprintf("listparam continue"); 
																ParamsListP tmp = $1;
																tmp->next = $3;
																$$=tmp;
															}
			;

Param		:	Id ':' Idcl									{ pprintf("param"); $$ = function_makeParam($1, $3); /*params: nomParam, typeParam */ }
			;

ExtendO		:	/* epsilon */								{ pprintf("extendo null");} /* Pas de traitement */
			|	EXT Idcl '(' ListArgO ')'					{ pprintf("extendo non null"); class_setSuper(current, $2, $4); /*params: classe, superType, arguments constructeur père */ }
			;

ListDeclO	:	/* epsilon */								{ pprintf("listdeclo null");} /* Pas de traitement */
			|	Decl ListDeclO								{ pprintf("listdeclo non null");} /* Pas de traitement */
			;

Decl		:	DeclField									{ pprintf("decl field");} /* Pas de traitement */
			|	DeclMethod									{ pprintf("decl method");} /* Pas de traitement */
			;

DeclField	:	StaticO DeclV								{ pprintf("declField"); class_addField(current, $1, $2); /*params: classe, isStatic, arbre de decl de la var */ }
			;

StaticO		:	/* epsilon */								{ pprintf("statico null"); $$ = 0; }
			|	STAT										{ pprintf("statico non null"); $$ = 1; }
			;

DeclMethod	:	OvOrStatO	DEF	Id '(' ListParamO ')' ReturnO IS Bloc {
																pprintf("declmethod"); 
																class_addMethod(current, $1, $3, $7, $5, $9);
																/*params: classe, visibility, nom, type de retour,liste des paramètres, arbre du corps de la fonction */
															}
			;

OvOrStatO	:	/* epsilon */								{ pprintf("ovorstat null"); $$ = 0; }
			|	OVR											{ pprintf("ovorstat ovr"); $$ = 1; }
			|	STAT										{ pprintf("ovorstat stat"); $$ = 2; }
			;

ReturnO		:	/* epsilon */								{ pprintf("returno null"); $$ = "";}
			|	RETS Idcl									{ pprintf("returno non null"); $$ = $2;}
			;

/* ------------------------------------------------------ Fin creation structures, debut creation arbres --------------------------------------------- */

ListDeclV	:	DeclV										{ pprintf("listdeclv final"); $$ = $1; }
			|	DeclV ListDeclV								{ pprintf("listdeclv continue"); $$ = makeTree(DECL, 2, $1, $2); }
			;

DeclV		:	VAR Id ':' Idcl AffectO	';'					{	pprintf("declv");
																$$ = makeTree(VAR, 3, makeLeafStr(ID, $2), makeLeafStr(IDCL, $4), $5);
																/* voir a pas ajouter un autre type "variable" aux feuilles de l'arbre */
															} 
			;
			
AffectO		:	/* epsilon */								{ pprintf("affect null"); $$ = NULL; }
			|	AFF Exp										{ pprintf("affect non null"); $$ = $2; }
			;

Affect 		:	Exp2 '.' Id AFF Exp ';' 					{ pprintf("affect1"); $$ = makeTree(CMPAFF, 3, $1, makeLeafStr(ID, $3), $5); }
			|	Id AFF Exp ';'								{ pprintf("affect2"); $$ = makeTree(DIRAFF, 2, makeLeafStr(ID, $1), $3); }

ListArgO	:	/* epsilon */								{ pprintf("listargo null"); $$ = NULL; }
			|	ListArg										{ pprintf("listargo non null"); $$ = $1; }
			;

ListArg		:	Exp											{ pprintf("list arg final"); $$ = $1; }
			|	Exp ',' ListArg								{ pprintf("list arg continue"); $$ = makeTree(LSTARG, 2, $1, $3); }
			;

BlocO		:	/* epsilon */								{ pprintf("bloco null"); $$ = NULL; } /* voir a peut etre passer par des leafs avec un code particulier pour eviter les segflt */
			|	Bloc										{ pprintf("bloco non null"); $$ = $1; }
			;

Bloc		:	'{' ListInstO '}'							{ pprintf("bloc final"); $$ = $2; }
			|	'{' ListDeclV IS ListInst '}'				{ pprintf("bloc continue"); $$ = makeTree(BLCDECL, 2, $2, $4); }
			;

ListInstO	:	/* epsilon */								{ pprintf("listinstO null"); $$ = NULL; }
			|	ListInst									{ pprintf("listinstO non null"); $$ = $1; }
			;

ListInst	:	Inst										{ pprintf("listinst final"); $$ = $1; }
			|	Inst ListInst								{ pprintf("listinst continue"); $$ = makeTree(LSTINST, 2,  $1, $2); }
			;

Inst		:	Exp ';'										{ pprintf("inst1"); $$ = makeTree(INSTR, 1, $1); }
			|	Bloc										{ pprintf("inst2"); $$ = $1; }
			|	RET ';'										{ pprintf("inst3"); $$ = makeLeafInt(RET, 0); /* 0 a defaut de savoir quoi mettre*/ }
			|	Affect 										{ pprintf("inst4"); $$ = $1; }
			|	IF Exp THEN Inst ELSE Inst					{ pprintf("inst5"); $$ = makeTree(IF, 3, $2, $4, $6); }
			;

Exp			:	Exp Relop Exp %prec RELOP 					{ pprintf("exp1"); $$ = makeTree($2, 2, $1, $3); }
			|	Exp CONCAT Exp								{ pprintf("exp2"); $$ = makeTree(CONCAT, 2, $1, $3); }
			|	Exp ADD Exp									{ pprintf("exp3"); $$ = makeTree(ADD, 2, $1, $3); }
			|	Exp SUB Exp									{ pprintf("exp4"); $$ = makeTree(SUB, 2, $1, $3); }
			|	Exp MUL Exp									{ pprintf("exp5"); $$ = makeTree(MUL, 2, $1, $3); }
			|	Exp DIV Exp									{ pprintf("exp6"); $$ = makeTree(DIV, 2, $1, $3); }
			|	ADD Exp %prec UNARYADD						{ pprintf("exp7"); $$ = makeTree(UNARYADD, 1, $2); } /* vraiment nécéssaire ? */
			|	SUB Exp %prec UNARYSUB						{ pprintf("exp8"); $$ = makeTree(UNARYSUB, 1, $2); }
			|	Exp2										{ pprintf("exp9"); $$ = $1; }
			;

Exp2		:	'(' Exp ')'									{ pprintf("exp21"); $$ = $2; } 
			|	'(' AS Idcl ':' Exp ')'						{ pprintf("exp22"); $$ = makeTree(CAST, 2, makeLeafStr(IDCL, $3), $5); }
			|	NEW Idcl '(' ListArgO ')'					{ pprintf("exp23"); $$ = makeTree(INSTA, 2, makeLeafStr(IDCL, $2), $4); }
			|	Exp2 '.' Id '(' ListArgO ')'				{ pprintf("exp24"); $$ = makeTree(MSGSNT, 3, $1, makeLeafStr(ID, $3), $5); }
			|	Idcl '.' Id '(' ListArgO ')'				{ pprintf("exp24bis"); $$ = makeTree(MSGSNTS, 3, makeLeafStr(IDCL, $1), makeLeafStr(ID, $3), $5); }
			| 	Exp2 '.' Id									{ pprintf("exp25"); $$ = makeTree(SELECT, 2, $1, makeLeafStr(ID, $3));}
			|	Idcl '.' Id									{ pprintf("exp25"); $$ = makeTree(SELECTS, 2, $1, makeLeafStr(ID, $3));}
			|	CST											{ pprintf("exp26"); $$ = makeLeafInt(CST, yyval.I); }
			|	STR											{ pprintf("exp27"); $$ = makeLeafStr(STR, yyval.S); }
			|	Id 											{ pprintf("exp28"); $$ = makeLeafStr(ID, yyval.S); }
			;

Id 			: 	ID											{ pprintfs("id", yyval.S); $$ = yyval.S; }
			;

Idcl		:	IDCL										{ pprintfs("idcl", yyval.S); $$ = yyval.S; }
			;

Relop		:	RELOP										{ pprintfi("relop", yyval.I); $$ = yyval.I; }
			;
