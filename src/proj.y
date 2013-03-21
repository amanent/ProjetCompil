%token CLASS EXT IS DEF OVR STAT RET RETS AS VAR NEW
%token IF THEN ELSE
%token AFF
%token ID IDCL
%token CONST STR
%token RELOP
%token ADD SUB MUL DIV CONCAT


%nonassoc RELOP CONCAT
%left ADD SUB
%left MUL DIV
%left UNARYADD UNARYSUB

%{

extern int yylex();	/* fournie par Flex */
extern void yyerror();  /* definie dans tp.c */
extern classList;

%}
	
%% 

Program		:	Bloc										{ /*lancer la verif contextuelle */ }
			|	Class Program								/* Pas de traitement */

Class 		:	CLASS Idcl '(' ListParamO ')' ExtendO BlocO IS '{' ListDeclO '}'; { 
																classlist_addClass($1);
																class_setConstructor(classList.current, $3);
															}

ListParamO 	:	/* epsilon */								{ $$ = NULL; }
			|	ListParam;									{ $$ = $0; }

ListParam	:	Param										{ $$ = $0; }
			| 	Param ',' ListParam;						{ 	
																ParamListP tmp = $0;
																tmp.next = $2;
																$$=tmp;
															}
			
Param		:	Id ':' Idcl;								{ $$ = function_makeParam($0, $2); }

ExtendO		:	/* epsilon */								/* Pas de traitement */
			|	EXT Idcl '(' ListArgO ')';					{ class_addParent(classList.current, $1, $3); /* troisiemme paramètres, les paramètres passés par le constructeru au parent */ }

ListDeclO	:	/* epsilon */								/* Pas de traitement */
			|	Decl ListDeclO;								/* Pas de traitement */
			
Decl		:	DeclField									/* Pas de traitement */
			|	DeclMethod;									/* Pas de traitement */
		
ListDeclV	:	DeclV										/* Pas de traitement */
			|	DeclV ListDeclV;							/* Pas de traitement */
			
DeclV		:	VAR Id ':' Idcl AffectO;					{ $$ = class_addVar($1, $3, $4); /* nom, type, arbre de l'expression de sa valeur si existe, NULL sinon */ }

DeclField	:	StaticO DeclV;								{ function_setStatic($1, $0); }

StaticO		:	/* epsilon */								{ $$ = 0; }
			|	STAT;										{ $$ = 1; }
			
AffectO		:	/* epsilon */								{ $$ = NULL; }
			|	AFF Exp;									{ $$ = $1; }
			
DeclMethod	:	OvOrStatO	DEF	Id '(' ListParamO ')' ReturnO IS Bloc; {
																class_addMethod($0, $2, $6, $4, $8); 
																/* static/overide/rien, nom, type de retour,liste des paramètres, arbre du corps de la fonction */ 
															}

OvOrStatO	:	/* epsilon */								{ $$ = 0; }
			|	OVR											{ $$ = 1; }
			|	STAT;										{ $$ = 2; }
			
ReturnO		:	/* epsilon */								{ $$ = NULL;}
			|	RETS Idcl;									{ $$ = $1;}

/* ------------------------------------------------------ Fin creation structures, debut creation arbres --------------------------------------------- */

ListArgO	:	/* epsilon */								{ $$ = NULL; }
			|	ListArg;									{ $$ = $0; }
		
ListArg		:	Exp											{ $$ = $0; }
			|	Exp ',' ListArg;							{ $$ = makeTree(LSTARG, 2, $0, $2); }
		
BlocO		:	/* epsilon */								{ $$ = NULL; } /* voir a peut etre passer par des leafs avec un code particulier pour eviter les segflt */
			|	Bloc;										{ $$ = $0; }
	
Bloc		:	'{' ListInstO '}'							{ $$ = $1; }
			|	'{' ListDeclV IS ListInst '}';				{ $$ = makeTree(BLCDECL, 2, $1, $3); }

ListInstO	:	/* epsilon */								{ $$ = NULL; }
			|	ListInst;									{ $$ = $0; }
			
ListInst	:	Inst										{ $$ = $0; }
			|	Inst ListInst;								{ $$ = makeTree(LSTINST, $0, $1); }
			
Inst		:	Exp ';'										{ $$ = $0; }
			|	Bloc										{ $$ = $0; }
			|	RET ';'										{ $$ = makeLeafInt(RET, 0); /* 0 a defaut de savoir quoi mettre*/ }
			|	LeftAffect AFF Exp ';' /* Affectation */	{ $$ = makeTree(AFF, 2, $0, $2); }
			|	IF Exp THEN Inst ELSE Inst;					{ $$ = makeTree(IF, 3, $1, $3, $5); }
	
Exp			:	Exp Relop Exp								{ $$ = makeTree($1, 2, $0, $2); }
			|	Exp CONCAT Exp								{ $$ = makeTree(CONCAT, 2, $0, $2); }
			|	Exp ADD Exp									{ $$ = makeTree(ADD, 2, $0, $2); }
			|	Exp SUB Exp									{ $$ = makeTree(SUB, 2, $0, $2); }
			|	Exp MUL Exp									{ $$ = makeTree(MUL, 2, $0, $2); }
			|	Exp DIV Exp									{ $$ = makeTree(DIV, 2, $0, $2); }
			|	ADD Exp %prec UNARYADD						{ $$ = makeTree(UNARYADD, 1, $1); }
			|	SUB Exp %prec UNARYSUB						{ $$ = makeTree(UNARYSUB, 1, $1); }
			|	Exp2;										{ $$ = $0 }
			
Exp2		:	'(' Exp ')'									{ $$ = $1; }
			|	'(' AS Idcl ':' Exp ')'						{ $$ = makeTree(CAST, 2, makeLeafStr(IDCL, $2), $4); }
			|	NEW Idcl '(' ListArgO ')'					{ $$ = makeTree(INST, 2, makeLeafStr(IDCL, $1), $3); }
			|	Exp2 '.' Id '(' ListArgO ')'				{ $$ = makeTree(MSGSNT, 3, $0, makeLeafStr(ID, $2), $4); }
			| 	LeftAffect									{ $$ = $0; }
			|	CONST										{ $$ = makeLeafInt(CONST, yyval.I); }
			|	STR;										{ $$ = makeLeafStr(STR, yyval.S); }
	
LeftAffect	:	Exp2 '.' Id									{ $$ = makeTree(LAFFECT, 2, $0, makeLeafStr(ID, $2); }
			|	Id;											{ $$ = makeLeafStr(ID, $0); }
			
Id 			: 	ID;											{ $$ = yyval.S }			

Idcl		:	IDCL;										{ $$ = yyval.S }

Relop		:	RELOP;										{ $$ = yyval.I; }

/*
TreeP makeLeafStr(short op, char *str);
TreeP makeLeafInt(short op, int val);
TreeP makeTree(short op, int nbChildren, ...);
*/
