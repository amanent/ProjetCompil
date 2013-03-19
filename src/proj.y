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
%}
	
%% 

Class 		:	CLASS Idcl '(' ListParamO ')' ExtendO BlocO IS '{' ListDeclO '}';

ListParamO 	:	/* epsilon */
			|	ListParam;

ListParam	:	Param
			| 	Param ',' ListParam;
			
Param		:	Id ':' Idcl;

ExtendO		:	/* epsilon */
			|	EXT Idcl '(' ListArgO ')';
		
ListArgO	:	/* epsilon */
			|	ListArg;
		
ListArg		:	Exp
			|	Exp ',' ListArg;
		
BlocO		:	/* epsilon */
			|	Bloc;
	
Bloc		:	'{' ListInstO '}'
			|	'{' ListDeclV IS ListInst '}';

ListInstO	:	/* epsilon */
			|	ListInst;
			
ListInst	:	Inst
			|	Inst ListInst;
			
ListDeclO	:	/* epsilon */
			|	Decl ListDeclO;
			
Decl		:	DeclField
			|	DeclMethod;
		
ListDeclV	:	DeclV
			|	DeclV ListDeclV;
			
DeclV		:	VAR Id ':' Idcl AffectO;

DeclField	:	StaticO DeclV;

StaticO		:	/* epsilon */
			|	STAT;
			
AffectO		:	/* epsilon */
			|	AFF Exp;
			
DeclMethod	:	OvOrStatO	DEF	Id '(' ListParamO ')' ReturnO IS Bloc;

OvOrStatO	:	/* epsilon */
			|	OVR
			|	STAT;
			
ReturnO		:	/* epsilon */
			|	RETS Idcl;
			
Inst		:	Exp ';'
			|	Bloc
			|	RET ';'
			|	LeftAffect AFF Exp ';' /* Affectation */
			|	IF Exp THEN Inst ELSE Inst;
	
Exp			:	Exp RELOP Exp
			|	Exp CONCAT Exp		
			|	Exp ADD Exp
			|	Exp SUB Exp	
			|	Exp MUL Exp
			|	Exp DIV Exp
			|	ADD Exp %prec UNARYADD
			|	SUB Exp %prec UNARYSUB
			|	Exp2;
			
Exp2		:	'(' Exp ')'
			|	'(' AS Idcl ':' Exp ')'
			|	NEW Idcl '(' ListArgO ')'
			|	Exp2 '.' Id '(' ListArgO ')'
			| 	LeftAffect
			|	CONST
			|	STR;

LeftAffect	:	Exp2 '.' Id												{ makeTree( LeaftAffect, // to modify
			|	Id;														{ makeLeafStr(ID, $0); }
			
Id 			: 	ID;														{ $$ = yyval.S; }			

Idcl		:	IDCL;													{ $$ = yyval.S; }
