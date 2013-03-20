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

Program		:	Bloc												{ /*lancer la verif contextuelle */ }
				|	Class Program									/* Pas de traitement */

Class 		:	CLASS Idcl '(' ListParamO ')' ExtendO BlocO IS '{' ListDeclO '}'; { classlist_addClass($1); }

ListParamO 	:	/* epsilon */									{ class_setParam(classList.current, NULL); }
				|	ListParam;										{ class_setParam(classList.current, $0); } // pour le constructeur

ListParam	:	Param												{ $$ = $0; }
				| 	Param ',' ListParam;							{ ParamListP tmp = $0;
																		  tmp.next = $2;
																		  $$=tmp;
																		}
			
Param			:	Id ':' Idcl;									{ $$ = function_makeParam($0, $2); }

ExtendO		:	/* epsilon */									{  }
				|	EXT Idcl '(' ListArgO ')';

ListDeclO	:	/* epsilon */
				|	Decl ListDeclO;
			
Decl			:	DeclField
				|	DeclMethod;
		
ListDeclV	:	DeclV
				|	DeclV ListDeclV;
			
DeclV			:	VAR Id ':' Idcl AffectO;

DeclField	:	StaticO DeclV;

StaticO		:	/* epsilon */
				|	STAT;
			
AffectO		:	/* epsilon */
				|	AFF Exp;												{}
			
DeclMethod	:	OvOrStatO	DEF	Id '(' ListParamO ')' ReturnO IS Bloc; { $$ = makeTree(DECLMTD, 5, $0, $2, $4, $6, $8); }

OvOrStatO	:	/* epsilon */
				|	OVR													{ $$ = makeLeafInt(OVR, 0); }
				|	STAT;													{ $$ = makeLeafInt(STAT, 0); }
			
ReturnO		:	/* epsilon */										{ $$ = NULL }
				|	RETS Idcl;											{ $$ = $1; }

ListArgO	:	/* epsilon */
				|	ListArg;
		
ListArg		:	Exp
				|	Exp ',' ListArg;
		
BlocO			:	/* epsilon */
				|	Bloc;
	
Bloc			:	'{' ListInstO '}'
				|	'{' ListDeclV IS ListInst '}';

ListInstO	:	/* epsilon */										{ $$ = NULL; }
				|	ListInst;											{ $$ = $0; }
			
ListInst		:	Inst													{ $$ = $0; }
				|	Inst ListInst;										{ $$ = makeTree(LSTINST, $0, $1); }
			
Inst			:	Exp ';'												{ $$ = $0; }
				|	Bloc													{ $$ = $0; }
				|	RET ';'												{ $$ = makeLeafInt(RET, 0); /* 0 a defaut de savoir quoi mettre*/ }
				|	LeftAffect AFF Exp ';' /* Affectation */	{ $$ = makeTree(AFF, 2, $0, $2); }
				|	IF Exp THEN Inst ELSE Inst;					{ $$ = makeTree(IF, 3, $1, $3, $5); }
	
Exp			:	Exp Relop Exp										{ $$ = makeTree($1, 2, $0, $2); }
				|	Exp CONCAT Exp										{ $$ = makeTree(CONCAT, 2, $0, $2); }
				|	Exp ADD Exp											{ $$ = makeTree(ADD, 2, $0, $2); }
				|	Exp SUB Exp											{ $$ = makeTree(SUB, 2, $0, $2); }
				|	Exp MUL Exp											{ $$ = makeTree(MUL, 2, $0, $2); }
				|	Exp DIV Exp											{ $$ = makeTree(DIV, 2, $0, $2); }
				|	ADD Exp %prec UNARYADD							{ $$ = makeTree(UNARYADD, 1, $1); }
				|	SUB Exp %prec UNARYSUB							{ $$ = makeTree(UNARYSUB, 1, $1); }
				|	Exp2;													{ $$ = $0 }
				
Exp2			:	'(' Exp ')'											{ $$ = $1; }
				|	'(' AS Idcl ':' Exp ')'							{ $$ = makeTree(CAST, 2, makeLeafStr(IDCL, $2), $4); }
				|	NEW Idcl '(' ListArgO ')'						{ $$ = makeTree(INST, 2, makeLeafStr(IDCL, $1), $3); }
				|	Exp2 '.' Id '(' ListArgO ')'					{ $$ = makeTree(MSGSNT, 3, $0, $2, $4); }
				| 	LeftAffect											{ $$ = $0; }
				|	CONST													{ $$ = makeLeafInt(CONST, yyval.I); }
				|	STR;													{ $$ = makeLeafStr(STR, yyval.S); }
	
LeftAffect	:	Exp2 '.' Id											{ $$ = makeTree(LAFFECT, 2, $0, $2); }
				|	Id;													{ $$ = $0; }
			
Id 			: 	ID;													{ $$ = makeLeafStr(ID, yyval.S); }			

Idcl			:	IDCL;													{ $$ = yyval.S }

Relop			:	RELOP;												{ $$ = yyval.I; }

/*
TreeP makeLeafStr(short op, char *str);
TreeP makeLeafInt(short op, int val);
TreeP makeTree(short op, int nbChildren, ...);
*/
