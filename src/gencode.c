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
	//printf("--treating : %d\n", tree->op);
	switch (tree->op) {
		case STR: 
			return writeCode(NULL, FALSE, NULL, "PUSHS", tree->u.str, "str cst"); 
		case CST:
			sprintf(intToStr, "%d", tree->u.val);
			return writeCode(NULL, FALSE, NULL, "PUSHI", intToStr, "int cst"); 		
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
			sprintf(intToStr2, "suite_%d", nbIf++);

			tmp = writeCode(gencode(getChild(tree, 0)), FALSE, NULL, "JZ", intToStr, "if");
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 1)));
			tmp = writeCode(tmp, FALSE, NULL, "JUMP", intToStr2, NULL);
			tmp = writeCode(tmp, FALSE, intToStr, "NOP", NULL , NULL);
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 2)));
			return writeCode(tmp, FALSE, intToStr2, "NOP", NULL , "fin if");
/**/	case CMPAFF: // Exp2 '.' Id AFF Exp ';'
			sprintf(intToStr, "%d", 0);//getChild(tree, 1)->var->local_offset); // champ rempli a la verif du type de retour de l'exp2.
			
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
			sprintf(intToStr, "%d", 0);//getChild(tree, 1)->var->local_offset); // champ rempli a la verif du type de retour de l'exp2.
			tmp = gencode(getChild(tree, 0));
			return writeCode(tmp, FALSE, NULL, "LOAD", intToStr , NULL);
/**/	case RET:
			return writeCode(NULL, FALSE, NULL, "RETURN", NULL , NULL); // l'adresse de la valeur de retour
		case VAR: //VAR Id ':' Idcl AffectO	';'
			tmp = writeCode(NULL, FALSE, NULL, "PUSHN", "1" , getChild(tree, 0)->u.str); // valeur de result
			if(getChild(tree, 2)!= NULL)
			{
				/* faire l'affectation */
			}
			return tmp; //gencode(getChild(tree, 0));; 		
/**/	case MSGSNT: // Exp2 '.' Id '(' ListArgO ')'
			sprintf(intToStr, "%d", 1 /* nbParams + 1 */); /* +a pour l'appellant */
			
			if(1/*si valeur de retour*/)
				tmp = writeCode(tmp, FALSE, NULL, "PUSHN", "1" , NULL); // pour la valeur de retour 
			/* La valeur/adresse de Exp2 est deja sur la pile (elle doit etre passée a la func) */
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 2))); //push des n arguments
			
			tmp = writeCode(tmp, FALSE, NULL, "PUSHA", getChild(tree, 1)->u.str , NULL);
			tmp = writeCode(tmp, FALSE, NULL, "CALL", NULL , NULL);
			return writeCode(tmp, FALSE, NULL, "POPN", intToStr , NULL);
		case MSGSNTS: // voir a factoriser avec MSGSNT
			return NULL;
/**/	case ID: 
			sprintf(intToStr, "%d", 0);//tree->u.var->local_offset); // champ rempli a la verif du type de retour de l'exp2.
			//switch(tree->u.var->nature)
			{
				//case 1: /* variable locale a un bloc => decalage par rapport au FP*/
					return writeCode(tmp, FALSE, NULL, "PUSHL", intToStr, NULL);
			}
			return NULL;	
/**/	case INSTA: // NEW Idcl '(' ListArgO ')'
			//sprintf(intToStr, "%d", 1 /* nbParams +1 */);
			tmp = writeCode(NULL, FALSE, NULL, "PUSHN", "1" , NULL);
			tmp = strcatwalloc(tmp, gencode(getChild(tree, 1)));
			tmp = writeCode(tmp, FALSE, NULL, "PUSHA", getChild(tree, 0)->u.str, NULL); /* appel de la methode ayant le nom du constructeur */
			tmp = writeCode(tmp, FALSE, NULL, "CALL", NULL , NULL); /* appel du constructeur */
			return tmp; // writeCode(tmp, FALSE, NULL, "POPN", intToStr , NULL); pas nécéssaire a priori si on pop dans le constructeur.
		case INSTR: 
			return strcatwalloc(gencode(getChild(tree, 0)), writeCode(NULL, FALSE, "--", "POPN", "1", NULL)); // TWEEEEEEEEAK
		case LSTARG: case BLCDECL: case DECL: case LSTINST:  
			return strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
		default: // case IDCL: case CAST: (seulement géré a la verif context, va modifier directement l'offset)
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

string genCodeFunc(FunctionP func) {
	string code;

	code = writeCode(NULL, FALSE, func->ID, "NOP", NULL, NULL); /* voir a faire quelque chose pour la multiplicité des noms */
	code = strcatwalloc(code, gencode(func->code));
	code = writeCode(code, FALSE, NULL, "RETURN", NULL, NULL);
	printf("%s", code);
	return code; //strcatwalloc(code, gencode(func->code));
}

string genCodeConst(ClassP c) {
	string code = NULL;
	char intToStr[20] = "";

	code = writeCode(NULL, FALSE, c->IDClass, "NOP", NULL, "constructor");

	if(c->superName != NULL) {
		code = writeCode(code, FALSE, NULL, "PUSHN", "1" , NULL); // pour la valeur de retour 
		code = strcatwalloc(code, gencode(c->superCallArgs)); //push des n arguments
		code = writeCode(code, FALSE, NULL, "PUSHA", c->superName , NULL);
		code = writeCode(code, FALSE, NULL, "CALL", NULL , NULL);
		//code = writeCode(code, FALSE, NULL, "POPN", intToStr , NULL);
	}
	else {
		sprintf(intToStr, "%d", c->size);
		code = writeCode(code, FALSE, NULL, "ALLOC", intToStr, NULL);
	}

	code = strcatwalloc(code, gencode(c->constructor->code));

	sprintf(intToStr, "%d", -1 - c->constructor->nbParam);
	code = writeCode(code, FALSE, NULL, "STOREL", intToStr, NULL);

	sprintf(intToStr, "%d", c->constructor->nbParam);
	code =  writeCode(code, FALSE, NULL, "POPN", intToStr, NULL); // a priori on peut le faire ici sans problème et ca simplifie le traitement
	
	return writeCode(code, FALSE, NULL, "RETURN", NULL, NULL);
}

string genBaseCode(ClassListP cl_par)
{
	string code = NULL;
	char intToStr[30] = "";
	ClassListP cl;

	code = strcatwalloc(code, "\n--champs statiques :");
	cl = cl_par;
	while(cl!=NULL)
	{
		ClassFieldListP scfl = cl->current->staticCfl;
		while(scfl!=NULL) // réservation d'un espace pour chaque champ statique
		{
			sprintf(intToStr, "%s_%s", cl->current->IDClass, scfl->current->ID);
			code = writeCode(code, FALSE, NULL, "PUSHN", "1" , intToStr);
			scfl = scfl->next;
		}
		cl = cl->next;
	}
	code = writeCode(code, FALSE, NULL, "JUMP", "start" , NULL);

	code = strcatwalloc(code, "\n--methodes statiques :");
	cl = cl_par;
	while(cl!=NULL)
	{
		ClassMethodListP scml = cl->current->staticCml;
		sprintf(intToStr, "\n\t--classe %s", cl->current->IDClass);
		code = strcatwalloc(code, intToStr);
		while(scml!=NULL)
		{
			code = strcatwalloc(code, genCodeFunc(scml->current));
			scml = scml->next;
		}
		cl = cl->next;
	}

	code = strcatwalloc(code, "\n--methodes non statiques :");
	cl = cl_par;
	while(cl!=NULL)
	{
		ClassMethodListP cml = cl->current->cml;
		sprintf(intToStr, "\n\t--classe %s", cl->current->IDClass);
		code = strcatwalloc(code, intToStr);

		code = strcatwalloc(code, genCodeConst(cl->current)); // constructeur
		while(cml!=NULL)
		{
			code = strcatwalloc(code, genCodeFunc(cml->current));
			cml = cml->next;
		}
		cl = cl->next;
	}

	return writeCode(code, FALSE, "start", "START", NULL , "main function");
}

/*
struct _Class{
	  string IDClass;
	  FunctionP constructor;
	  ClassFieldListP staticCfl;
	  ClassMethodListP staticCml;
	  ClassFieldListP cfl;
	  ClassMethodListP cml;
	  struct  _Class * super;
	  string superName;
	  TreeP superCallArgs;

	  JumpTableP instance;
	  JumpTableP statics;

	};


struct _Function {
		bool override;
		string ID;
		ParamsListP paramsList;
		TreeP code;
		ClassP returnType;
		string returnName;
		int nbParam
	};
*/