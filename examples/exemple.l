Digit [0-9]
Letter  [a-zA-Z]
LD  ({Letter}|{Digit})
COM ([/]{Star}({NotStar}|{Star}*{NotStarSlash})*{Star}*[*][/])
Star \*
NotStar [^*]
NotStarSlash [^*/]
StrChar [^\\"\n]
StrEsc \\.
Delim [ \n\t\r]
Symbol [;,()]
Guill "\""
Str ({Guill}({StrChar}|{StrEsc})*{Guill})

%{
#include <string.h>	/* pour strdup */
#include "tp.h"
#include "tp_y.h"

extern char *strdup(const char *s);

extern YYSTYPE yylval;
extern bool noEval;

int keywordOrId() { 
  /* reconnaitre ci-dessous tous les mots-cles du langage
   * les tokens sont a declarer dans tp.y (ou tp_y.h dans la premiere partie.
   * si ce n'est pas un mot-clef, sauvegarder le texte de l'identificateur
   * et renvoyer le token associe aux identificateurs
   */
   if(!strcmp(yytext,"if")) return(IF);
   if(!strcmp(yytext,"then")) return(THEN);
   if(!strcmp(yytext,"else")) return(ELSE);
   if(!strcmp(yytext,"begin")) return(BEG);
   if(!strcmp(yytext,"end")) return(END);
  yylval.S = strdup(yytext);
  return(ID);
}


void lexError(char c) {
  fprintf(stderr, "Skipping invalid character: '%c' on line %d\n", c, yylineno);
}


/* les codes symboliques pour les unites lexicales (CST, IF, ADD, ...) sont
 * definis dans tp_y.h et serviront aussi d'etiquettes pour les sommets de
 * l'arbre de syntaxe abstraite qui sera construit par la suite du processus
 * de compilation.
 * 
 * Les "return" qui apparaissent dans les actions associees aux expressions
 * regulieres peuvent renvoyer:
 * - soit le code symbolique d'une U.L.
 * - soit un simple caractere
 * L'eventuelle partie "valeur" de l'U.L. doit etre stockee dans une des
 * variantes de la variable yylval (definie comme etant de type YYSTYPE)
 * afin que les outils compagnons de l'analyseur lexical puisse l'y recuperer.
 * Attention: le contenu de yylval va etre ecrase a chaque appel a l'analyseur
 * lexical et doit donc etre sauvegarde si besoin.
 */
%}

%%
{Digit}+        { yylval.I = strtol(yytext, NULL, 0); return(CST); }
{Letter}{LD}*   { return keywordOrId(); }
":="            { return(AFF); }
"+"             { return(ADD); }
"-"             { return(SUB); }
"*"             { return(MUL); }
"/"            { return(DIV); }
"="             { /* Voir la liste des etiquettes dans tp.h */
                  yylval.C = EQ; return(RELOP);
                }
"<>"            { yylval.C = NE; return(RELOP); }
">"             { yylval.C = GT; return(RELOP); }
"<"             { yylval.C = LT; return(RELOP); }
{Symbol}        { /* Completer la liste des symboles necessaires */
                  return(yytext[0]);
                }
{Delim}         { }
{Str}           { yylval.S = strdup(yytext); return(STR);}
{COM}           { }
%%
