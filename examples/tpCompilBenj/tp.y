/* les tokens ici sont ceux supposes etre renvoyes par l'analyseur lexical
 * A adapter par chacun en fonction de ce qu'il a ecrit dans tp.l
 *
 * Bison ecrase le contenu de tp_y.h a partir de la description de la ligne
 * suivante. Ce sont donc ces lignes qu'il faut adapter si besoin, pas tp_y.h !
 */
%token BEG END
%token AFF
%token ID STR
%token CST
%token RELOP
%token IF THEN ELSE
%token GET PUT

/* indications de precedence (en ordre croissant) et d'associativite. Les
 * operateurs sur une meme ligne (separes par un espace) ont la meme priorite.
 * On peut mettre soit un token, soit directement un caractere comme '*'
 */
%nonassoc ELSE 
%left ADD SUB
%left MUL DIV

 /* On declare que la valeur associe a NOM_VAR utilise la variante 'S' du
  * type YYSTYPE. Il s'agira donc d'une chaine de caracteres...
  * Ajouter les indications similaires pour les autres nom-terminaux qui ont
  * aussi une notion de valeur associee.
  */
%type <T> NOM_VAR NOM_STR ID
%type <I> NOM_RELOP programme
%type <T> expr bexpr
%type <D> declL declLO

%{
#include <stdio.h>
#include "tp.h"     /* les definition des types et les etiquettes des noeuds */

extern int yylex();	/* fournie par Flex */
extern void yyerror();  /* definie dans tp.c */

VarDecl env;
%}

%% 
programme : declLO BEG expr END { printf("Res : %d", eval($3, $1)); } // dunno the second param
								/*ici, 
								1. evaluer l'expression avec $1
								2 affichage de la valeur
								*/
;

/* l'environnemt variable/valeur etant memorise directement dans une variable
 * globale, les productions qui suivent ne retournent pas de valeur et n'ont
 * pas d'action associee.
 *
 * declL0: liste optionnelle de 'declarations de variable'
 */
declLO :					{ $$ = NIL(VarDecl); }
| declL						{ $$ = $1; }
;

declL : ID AFF expr ';'		{
								VarDecl *dec = NEW(1, VarDecl);
								dec->name = $1->u.str;
								dec->val = eval($3, NULL); // pas sur
								dec->next=NULL;
								$$ = dec;
							}
							/*ici, 
							1. Evaluation expr avec liste decl vide
							2 creation d'un doublet nomvar valeur
							3 retourner ce doublet dans $$
							//4 bonus : désalouer proprement l'expression
							*/
							// {$$= pointeur sur cette liste}				
| declL ID AFF expr ';'	{
							VarDecl *dec = NEW(1, VarDecl);
							dec->name = $2->u.str;
							dec->val = eval($4, $1); // pas sur
							dec->next = $1;
							$$ = dec;
						}/*ici, 
							1. Evaluation expr avec liste decl $1
							2 creation d'un doublet nomvar valeur
							3 retourner ce doublet dans $$
							4 bonus : désalouer proprement l'expression
							*/
							// {$$= pointeur sur cette liste}	
;


/* une declaration de variable ou de fonction, terminee par un ';'.
 * L'action associee devrait correspondre a
 * - evaluer l'arbre correspondant a 'expr', en utilisant la liste courante
 * des couple variable/valeur. Une fois la valeur obtenue ajouter le nouveau
 * couple forme du nom de la variable et de sa valeur, en verifiant au
 * prealable que la variable n'existait pas deja (une seule declaration de
 * chaque variable d'apres l'enonce.
 *
 * Pour l'evaluation, voir l'ebauche de la fonction 'eval' dans tp.c
 */
//decl : ID AFF expr ';'				{  }
//;

/* construire et renvoyer un arbre representant l'expression, en fonction des
 * arbres (deja construits) de ses sous-expressions.
 *
 * Voir les fonctions mises a disposition dans tp.c et en ajouter si besoin.
 */
expr : expr ADD expr				{ $$ = makeTree(ADD, 2, $1, $3); }
| expr SUB expr						{ $$ = makeTree(SUB, 2, $1, $3); }
| expr MUL expr						{ $$ = makeTree(MUL, 2, $1, $3); }
| expr DIV expr						{ $$ = makeTree(DIV, 2, $1, $3); }
| IF bexpr THEN expr ELSE expr		{ $$ = makeTree(IF, 3, $2, $4, $6); }
| CST 								{ $$ = makeLeafInt(CST, yylval.I); }
| GET '(' ')'						{ $$ = makeLeafInt(GET, 0); }
| PUT '(' NOM_STR ',' expr ')'			{ $$ = makeTree(PUT, 2, $3, $5); }
| NOM_VAR 							{ $$ = $1; }
| '(' expr ')' 						{ $$ = $2; }
;

bexpr : expr NOM_RELOP expr 		{ $$ = makeTree($2, 2, $1, $3); }
| '(' bexpr ')' 					{ $$ = $2; }
;

/* Passage de valeur entre analyseur lexical et analyseur syntaxique via la
 * variable yylval (de type YYSTYPE)
 */
NOM_VAR : ID 						{ $$ = makeLeafStr(ID, yylval.S); }
;

NOM_RELOP : RELOP 					{ $$ = yylval.C; }
;

NOM_STR : STR						{ $$ = makeLeafStr(STR, yylval.S); }
;

