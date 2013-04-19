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

// Voir a différencier selection et affectation 
string gencode(TreeP tree) {
	char *tmp=NULL;
	char intToStr[20] = "", intToStr2[20] = ""; /* normalement pas de int de plus de 20 digit gérés par la machine (18 max pour un nombre sur 64 bits, plus le signe plus \0 = 20) */

	if (tree == NULL)
	    return "";
	//printf("treating : %d\n", tree->op);
	switch (tree->op) {
		case STR: 
			return writeCode(NULL, FALSE, NULL, "PUSHS", tree->u.str, "chaine de caractere"); 
		case CST:
			sprintf(intToStr, "%d", tree->u.val);
			return writeCode(NULL, FALSE, NULL, "PUSHI", intToStr, "constante entiere"); 		
		case EQ:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "EQUAL", NULL, NULL);
		case NE:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			tmp = writeCode(tmp, FALSE, NULL, "EQUAL", NULL, NULL);
			return writeCode(tmp, FALSE, NULL, "NOT", NULL, NULL);
		case GT:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "SUP", NULL, NULL);
		case GE:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "SUPEQ", NULL, NULL);
		case LT:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "INF", NULL, NULL);
		case LE:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "INFEQ", NULL, NULL);
		case ADD:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "ADD", NULL, NULL);
		case SUB:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "SUB", NULL, NULL);
		case MUL:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "MUL", NULL, NULL);
		case DIV:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "DIV", NULL, NULL);
		case CONCAT:
			tmp = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(tmp, FALSE, NULL, "CONCAT", NULL, NULL);
		case UNARYSUB:
			tmp = writeCode(NULL, FALSE, NULL, "PUSHI", "0", NULL);
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 0)));
			return writeCode(tmp, FALSE, NULL, "SUB", NULL, NULL);
		case UNARYADD: 
			return gencode(getChild(tree, 0));
		case IF: 
			sprintf(intToStr, "else_%d", nbIf);
			tmp = writeCode(gencode(getChild(tree, 0)), FALSE, NULL, "JZ", intToStr, "premiere passe if");
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 1)));
			sprintf(intToStr2, "suite_%d", nbIf++);
			tmp = writeCode(tmp, FALSE, NULL, "JUMP", intToStr2, "deuxieme passe if (fin du then)");
			tmp = writeCode(tmp, FALSE, intToStr, "NOP", NULL , "troisième passe du if (else)");
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 2)));
			return writeCode(tmp, FALSE, intToStr2, "NOP", NULL , "quatrième passe du if (fin du else)");
/**/	case CMPAFF: // Exp2 '.' Id AFF Exp ';'
			sprintf(intToStr, "%d", getChild(tree, 1)->u.var->local_offset); // champ rempli a la verif du type de retour de l'exp2.
			
			tmp = gencode(getChild(tree, 0));
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 2)));

			return writeCode(NULL, FALSE, NULL, "STORE", intToStr , NULL);
/**/	case DIRAFF: // Id AFF Exp ';'
			sprintf(intToStr, "%d", 0);//getChild(tree, 0)->u.var->local_offset);

			tmp = gencode(getChild(tree, 1)); /* le code de l'expression */

			//switch(getChild(tree, 0)->u.var->nature)
			{
				//case 1:
					return writeCode(tmp, FALSE, NULL, "STOREL", intToStr , NULL);
				//tmp = writeCode(NULL, FALSE, NULL, "STOREL", intToStr , NULL);
			}
			return tmp;	
/**/	case SELECT: // Exp2 '.' Id
			sprintf(intToStr, "%d", getChild(tree, 1)->u.var->local_offset); // champ rempli a la verif du type de retour de l'exp2.
			tmp = gencode(getChild(tree, 0));
			return writeCode(tmp, FALSE, NULL, "LOAD", intToStr , NULL);
/**/	case RET:
			/* pas sur que y'ait besoin de faire ca */ 
			sprintf(intToStr, "%d", 10 /* indexofResult */); // champ rempli a la verif du type de retour de l'exp2.
			tmp = writeCode(NULL, FALSE, NULL, "PUSH", intToStr , NULL); // valeur de result
			return writeCode(tmp, FALSE, NULL, "STOREL", "" , NULL); // l'adresse de la valeur de retour
		case VAR: //VAR Id ':' Idcl AffectO	';'
			tmp = writeCode(NULL, FALSE, NULL, "PUSHN", "1" , getChild(tree, 0)->u.str); // valeur de result
			if(getChild(tree, 2)!= NULL)
			{
				/* faire l'affectation */
			}
		break;//return gencode(getChild(tree, 0));; 		
		case MSGSNT:
			/* MSGSNT
			PUSHN 1 // pour la valeur de retour 
			//push des n arguments 
			PUSHA //nom fonction
			CALL
			POP // nbParams 
			*/
			break; 	
		case CAST: break; /* ----------------------------------------------------------------------------------------------WHAT MUST I DO ? */
/**/	case ID: 
			sprintf(intToStr, "%d", 0);//tree->u.var->local_offset); // champ rempli a la verif du type de retour de l'exp2.
			//switch(tree->u.var->nature)
			{
				//case 1: /* variable locale a un bloc => decalage par rapport au FP*/
					return writeCode(tmp, FALSE, NULL, "PUSHL", intToStr , NULL);
			}
			break; 	
		case INSTA:
			/*INST
				ALLOC //taille de lobjet
				//initialisations
				//constructeur
			*/
			break;
		case INSTR: 
			return strcatwalloc(gencode(getChild(tree, 0)), writeCode(NULL, FALSE, "--", "POPN", "1", NULL)); // TWEEEEEEEEAK
		case LSTARG: case BLCDECL: case DECL: case LSTINST:  
			return strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
		default: // case IDCL: 
		fprintf(stderr, "Erreur! pprint : etiquette d'operator inconnue: %d\n", tree->op);
		break; 
	}
	return NULL;
}
/*
!= types de variables :
	- attribut statique
	- attribut non statique
	- paramètre
	- var locale a un bloc
	- var globale
*/