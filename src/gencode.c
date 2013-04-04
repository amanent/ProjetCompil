#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "proj.h"
#include "proj_y.h"

string writeCode(string prevCode, bool breakPoint, string label, string code, string arg, string comm) { // ne marche pas avec une chaine constante en premier paramètre.
	string newCode = realloc(prevCode, (prevCode==NULL?0:strlen(prevCode))
										+ (label==NULL?0:strlen(label))
										+ strlen(code)
										+ (arg==NULL?0:strlen(arg))
										+ (comm==NULL?0:strlen(comm))
										+ 10); // +10 pour gérer les quelques caractères supplémentaires
	
	if(prevCode==NULL)
		newCode[0]='\0'; // au cas ou l'initialisation soit a NULL, équivalent a Malloc, il faut donc initialiser la chaine.
	
	strcat(newCode, "\n");
	if(breakPoint)
		strcat(newCode, "* ");
	if(label!=NULL && strlen(label)>0) {
		strcat(newCode, label);
		strcat(newCode, ":");
	}
	strcat(newCode, "\t");
	strcat(newCode, code);
	strcat(newCode, "\t");
	if(arg!=NULL && strlen(arg)>0)
		strcat(newCode, arg);
	
	strcat(newCode, "\t");
	if(comm!=NULL && strlen(comm)>0) {
		strcat(newCode, "--");
		strcat(newCode, comm);
	}
	return newCode;
}

string strcatwalloc(string s1, string s2) {
	string res = realloc(s1, (s1==NULL?0:strlen(s1)) + (s2==NULL?0:strlen(s2))+1);
	if(s2!=NULL && strlen(s2)>0)
		strcat(res, s2);
	return res;
}

/* variables annexes nécéssaires, je vais les replacer plus loin */
int nbIf=0;
/*-----------------------------------------------*/

string gencode(TreeP tree) {
	char *tmp=NULL;
	char intToStr[20] = "", intToStr2[20] = ""; /* normalement pas de int de plus de 20 digit gérés par la machine (18 max pour un nombre sur 64 bits, plus le signe plus \0 = 20) */

	if (tree == NULL)
	    return "";
	//printf("treating : %d\n", tree->op);
	switch (tree->op) {
		case STR: 
			return writeCode(NULL, TRUE, NULL, "PUSHS", tree->u.str, "chaine de caractere"); 
		case CST:
			sprintf(intToStr, "%d", tree->u.val);
			return writeCode(NULL, FALSE, NULL, "PUSHI", intToStr, "constante entiere"); 		
		case EQ:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "EQUAL", NULL, "relop (egal)");
		case NE:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			tmp = writeCode(tmp, TRUE, NULL, "EQUAL", NULL, "relop (non egal) ...");
			return writeCode(tmp, TRUE, NULL, "NOT", NULL, "... fin");
		case GT:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "SUP", NULL, "relop (plus grand)");
		case GE:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "SUPEQ", NULL, "relop (plus grand ou egal)");
		case LT:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "INF", NULL, "relop (plus petit)");
		case LE:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "INFEQ", NULL, "relop (plus petit ou egal)");
		case ADD:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "ADD", NULL, "addition");
		case SUB:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "SUB", NULL, "soustraction");
		case MUL:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "MUL", NULL, "multiplication");
		case DIV:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "DIV", NULL, "division");
		case CONCAT:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, NULL, "CONCAT", NULL, "concatenation");
		case UNARYSUB:
			tmp = writeCode(NULL, TRUE, NULL, "PUSHI", "0", "moins unaire...");
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 0)));
			return writeCode(tmp, TRUE, NULL, "SUB", NULL, "... fin moins unaire");
		case UNARYADD: 
			return gencode(getChild(tree, 0));
		case IF: 
			sprintf(intToStr, "else_%d", nbIf);
			tmp = writeCode(gencode(getChild(tree, 0)), TRUE, NULL, "JZ", intToStr, "premiere passe if");
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 1)));
			sprintf(intToStr2, "suite_%d", nbIf);
			tmp = writeCode(tmp, TRUE, NULL, "JUMP", intToStr2, "deuxieme passe if (fin du then)");
			tmp = writeCode(tmp, TRUE, intToStr, "NOP", NULL , "troisième passe du if (else)");
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 1)));
			return writeCode(tmp, TRUE, intToStr2, "NOP", NULL , "quatrième passe du if (fin du else)");
		case AFF: break;
		case RET: break;
		case VAR: break; 		
		case MSGSNT: break; 	
		case CAST: break; 		
		case SELECT: break;
		case ID: break;
		case IDCL: break; 
		case LSTARG: case BLCDECL: case DECL: case LSTINST: case INST: 
			return strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
		default:
		fprintf(stderr, "Erreur! pprint : etiquette d'operator inconnue: %d\n", tree->op);
		break; 
	}
	return"";
}
/*

ID
	PUSH? addrIdent
IDCL
	//rien normalement

MSGSNT
	PUSHN 1 // pour la valeur de retour 
	//push des n arguments 
	PUSHA //nom fonction
	CALL
	POP // nbParams 
CAST
	// je vois pas trop, peut etre en empilant une copie de l'objet et changer sa table d'appels
INST
	ALLOC //taille de lobjet
	//initialisations
	//constructeur
	
SELECT
	PUSH //addr objet 
	// ??? 
AFF
	//adresse de la partie gauche deja pushée 
	PUSH // valeur 
	STORE // decalage du champ par rapport a la classe... comment est ce que je le retrouve moi ?) 
RET
VAR

*/