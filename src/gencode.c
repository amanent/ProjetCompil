#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "proj.h"
#include "proj_y.h"
#include "variable.h"
#include "gencode.h"

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
		//printf("%s", comm);
	}
	//strcat(newCode, "toy\n\0");
	return newCode;
}

string strcatwalloc(string s1, string s2) {
	string res = realloc(s1, (s1==NULL?0:strlen(s1)) + (s2==NULL?0:strlen(s2))+1);
	
	if(s1==NULL)
		res[0]='\0';

	if(s2!=NULL && strlen(s2)>0)
		strcat(res, s2);
	return res;
}


/* variables annexes nécéssaires, je vais les replacer plus loin */
int nbIf=0;
/*-----------------------------------------------*/

// Voir a différencier selection et affectation 
string gencode(TreeP tree) {
	char *code = NULL;
	char intToStr[40] = "", intToStr2[40] = ""; /* normalement pas de int de plus de 20 digit gérés par la machine (18 max pour un nombre sur 64 bits, plus le signe plus \0 = 20) */

	if (tree == NULL)
	    return NULL;
	//fprintf(stderr, "--treating : %d\n", tree->op);
	switch (tree->op) {
		case STR: 
			return writeCode(NULL, FALSE, NULL, "PUSHS", tree->u.str, "str cst"); 
		case CST:
			sprintf(intToStr, "%d", tree->u.val);
			return writeCode(NULL, FALSE, NULL, "PUSHI", intToStr, "int cst"); 		
		case EQ:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "EQUAL", NULL, NULL);
		case NE:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			code = writeCode(code, FALSE, NULL, "EQUAL", NULL, NULL);
			return writeCode(code, FALSE, NULL, "NOT", NULL, NULL);
		case GT:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "SUP", NULL, NULL);
		case GE:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "SUPEQ", NULL, NULL);
		case LT:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "INF", NULL, NULL);
		case LE:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "INFEQ", NULL, NULL);
		case ADD:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "ADD", NULL, NULL);
		case SUB:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "SUB", NULL, NULL);
		case MUL:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "MUL", NULL, NULL);
		case DIV:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "DIV", NULL, NULL);
		case CONCAT:
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "CONCAT", NULL, NULL);
		case UNARYSUB:
			code = writeCode(NULL, FALSE, NULL, "PUSHI", "0", NULL);
			code = strcatwalloc(code, gencode(getChild(tree, 0)));
			return writeCode(code, FALSE, NULL, "SUB", NULL, NULL);
		case UNARYADD: 
			return gencode(getChild(tree, 0));
		case RET:
			return writeCode(NULL, FALSE, NULL, "RETURN", NULL , NULL);
		case IF: 
			sprintf(intToStr, "else_%d", nbIf);
			sprintf(intToStr2, "suite_%d", nbIf++);

			code = writeCode(gencode(getChild(tree, 0)), FALSE, NULL, "JZ", intToStr, "if");
			code = strcatwalloc(code, gencode(getChild(tree, 1)));
			code = writeCode(code, FALSE, NULL, "JUMP", intToStr2, NULL);
			code = writeCode(code, FALSE, intToStr, "NOP", NULL , NULL);
			code = strcatwalloc(code, gencode(getChild(tree, 2)));
			return writeCode(code, FALSE, intToStr2, "NOP", NULL , "fin if");
		case CMPAFF: // Exp2 '.' Id AFF Exp ';'
			code = gencode(getChild(tree, 0)); /* le code de l'exp2 */
			code = strcatwalloc(code, gencode(getChild(tree, 2))); /* le code de l'expression à affectée */
			
			if(tree->var==NULL) 
				return writeCode(NULL, FALSE, NULL, "ERR", "non gere actuellement", "-----------------------------------------------------------------6");

			sprintf(intToStr, "%d", getChild(tree, 1)->var->offset); // offset du id
			return writeCode(code, FALSE, NULL, "STORE", intToStr , NULL);
		case DIRAFF: // Id AFF Exp ';'
			code = gencode(getChild(tree, 1)); /* le code de l'expression */
			
			if(getChild(tree, 0)->var==NULL) 
				return writeCode(code, FALSE, NULL, "STOREL", "0", "-----------------------------------------------------------------5");

			sprintf(intToStr, "%d", getChild(tree, 0)->var->offset); 
			
			switch(getChild(tree, 0)->var->nature)
			{
				case STATIC: // offset par rapport a GP
					return writeCode(code, FALSE, NULL, "STOREG", intToStr , "static");
				case NONSTATIC: // offset par rapport a adresse Classe
					if(tree->fContext != NULL) {
						sprintf(intToStr2, "%d", - tree->fContext->nbParam - 1); // empilage de l'adresse de l'appelant
						code = writeCode(code, FALSE, NULL, "PUSHL", intToStr2, "instance 1/3");
						code = writeCode(code, FALSE, NULL, "SWAP", NULL, "instance 2/3"); // pour remettre les paramètres dans le bon sens
						return writeCode(code, FALSE, NULL, "STORE", intToStr, "instance 3/3");
					}
				case PARAM: // offset par rapport a FP (negatif)
					return writeCode(code, FALSE, NULL, "STOREL", intToStr , "param");
				case LOCAL: // offset par rapport a FP (positif)
					return writeCode(code, FALSE, NULL, "STOREL", intToStr , "local");
			}

			return writeCode(code, TRUE, NULL, "NOP", NULL, "erreur d'adressage");	
		case SELECTS: // Idcl '.' Id
			/*if(getChild(tree, 1)->var != NULL)
				sprintf(intToStr, "%d", getChild(tree, 1)->var->offset); // on suppose que pour les séléctions, l'offset de l'adresse (si besoin) est dans le membre, et celle du décalage dans le fils.
			else
				sprintf(intToStr, "%d------------4", 0); // debug
*/
			if(tree->var != NULL)
				sprintf(intToStr2, "%d", tree->var->offset);
			else
				sprintf(intToStr2, "%d------------3", 0); // debug

			return writeCode(NULL, FALSE, NULL, "PUSHG", intToStr2 , NULL);
			//return writeCode(code, FALSE, NULL, "LOAD", intToStr , NULL);
		case SELECT: // Exp2 '.' Id
			if(getChild(tree, 1)->var != NULL)
				sprintf(intToStr, "%d", getChild(tree, 1)->var->offset); // on suppose que pour les séléctions, l'offset de l'adresse (si besoin) est dans le membre, et celle du décalage dans le fils.
			else
				sprintf(intToStr, "%d ------------2", 0); // debug

			code = gencode(getChild(tree, 0)); // pas sur que ca marche
			return writeCode(code, FALSE, NULL, "LOAD", intToStr , NULL);
		case VAR: //VAR Id ':' Idcl AffectO	';'
			if(getChild(tree, 2)== NULL) // si pas d'affectation directement a la déclaration
				return writeCode(NULL, FALSE, NULL, "PUSHN", "1" , getChild(tree, 0)->u.str); //si pas d'affectation, on prépare un emlplacement pour la variable.
			else
				return gencode(getChild(tree, 2)); // sinon mets le code d'initialisation de la variable, qui laissera une valeur en tete de pile, qui équivant a l'espace reservé au cas précédent.		
		case MSGSNT: // Exp2 '.' Id '(' ListArgO ')'
			//if(tree->func==NULL || function_hasReturnType(tree->func)) // voir MSGSNT
				code = writeCode(code, FALSE, NULL, "PUSHN", "1" , "return value"); // pour la valeur de retour
	
			code = strcatwalloc(code, gencode(getChild(tree, 0))); // pour mettre l'appelant sur la pile
			code = strcatwalloc(code, gencode(getChild(tree, 2))); //push des n arguments

			if(strcmp(getChild(tree, 0)->type->IDClass, "String")!=0 && strcmp(getChild(tree, 0)->type->IDClass, "Integer")!=0) {
				//code = writeCode(code, FALSE, NULL, "DUPN", "1" , "pour garder l'appellant");
				if(strcmp(getChild(tree, 0)->u.str, "super")) // si différent de super
					code = strcatwalloc(code, gencode(getChild(tree, 0))); // pour remettre l'appelant sur la pile (possiblement a optimiser)
				else {
					sprintf(intToStr, "%d", getChild(tree, 0)->type->super->offsetTV);
					code = writeCode(code, FALSE, NULL, "PUSHG", intToStr, "TV du papa");
				}

				code = writeCode(code, FALSE, NULL, "LOAD", "0" , "load TV");
				sprintf(intToStr, "%d", tree->func->offset);
				code = writeCode(code, FALSE, NULL, "LOAD", intToStr, "index function");
			}
			else
				code = writeCode(code, FALSE, NULL, "PUSHA", getChild(tree, 1)->u.str , NULL);
			
			code = writeCode(code, TRUE, NULL, "CALL", NULL, NULL);
			
			if(tree->func!=NULL)
			{
				sprintf(intToStr, "%d", tree->func->nbParam+1); // pour l'appellant
				return writeCode(code, FALSE, NULL, "POPN", intToStr , NULL);
			}
			else
				return writeCode(code, FALSE, NULL, "POPN", "1" , NULL);
		case MSGSNTS: // Idcl '.' Id '(' ListArgO ')'
			//if(tree->func==NULL || function_hasReturnType(tree->func)) // on empile une element que la fonction retourne quelque chose ou pas, sinon  l'instruction dépile une valeur qui n'aurait pas du l'etre.
				code = writeCode(code, FALSE, NULL, "PUSHN", "1" , "return value"); // pour la valeur de retour
			code = strcatwalloc(code, gencode(getChild(tree, 2))); //push des n arguments
			
			sprintf(intToStr, "%s_%s", getChild(tree, 0)->u.str, getChild(tree, 1)->u.str); // pour eviter la multiplicité des noms
			code = writeCode(code, FALSE, NULL, "PUSHA", intToStr, NULL);
			code = writeCode(code, TRUE, NULL, "CALL", NULL , NULL);

			if(tree->func!=NULL)
			{
				sprintf(intToStr, "%d", tree->func->nbParam);
				return writeCode(code, FALSE, NULL, "POPN", intToStr , NULL);
			}
			else
				return writeCode(code, FALSE, NULL, "POPN", "1" , NULL);
		case ID: // seulement possible en partie droite d'affect, ou en partie gauche de select ?
			if(tree->var==NULL)
				return writeCode(NULL, FALSE, NULL, "PUSHL", "0", "-----------------------------------------------------------------1");
	
			sprintf(intToStr, "%d", tree->var->offset); // champ rempli a la verif du type de retour de l'exp2.
			switch(tree->var->nature)
			{
				case STATIC: // offset par rapport a GP
					return strcatwalloc(writeCode(NULL, FALSE, NULL, "PUSHG", intToStr, "static "), tree->var->ID);
				case NONSTATIC: // offset par rapport a adresse Classe
					if(tree->fContext != NULL) {
						sprintf(intToStr2, "%d", - tree->fContext->nbParam - 1); // empilage de l'adresse de l'appelant
						code = strcatwalloc(writeCode(NULL, FALSE, NULL, "PUSHL", intToStr2, "nonstatic 1/2 "), tree->var->ID);
						return strcatwalloc(writeCode(code, FALSE, NULL, "LOAD", intToStr, "nonstatic 2/2 "), tree->var->ID);
					}
				case PARAM: // offset par rapport a FP (negatif)
					return strcatwalloc(writeCode(NULL, FALSE, NULL, "PUSHL", intToStr, "param "), tree->var->ID);
				case LOCAL: // offset par rapport a FP (positif)
					return strcatwalloc(writeCode(NULL, FALSE, NULL, "PUSHL", intToStr, "local "), tree->var->ID);
			}
			return writeCode(code, TRUE, NULL, "NOP", NULL, "erreur d'adressage");
		case INSTA: // NEW Idcl '(' ListArgO ')'
			sprintf(intToStr, "%d", class_getClass(getChild(tree, 0)->u.str)->nbFields+1); // +1 pour la TV
			code = writeCode(code, FALSE, NULL, "ALLOC", intToStr, NULL); // allocation de l'objet avant d'appeller le const
			code = strcatwalloc(code, gencode(getChild(tree, 1)));
			code = writeCode(code, FALSE, NULL, "PUSHA", getChild(tree, 0)->u.str, NULL);
			code = writeCode(code, FALSE, NULL, "CALL", NULL , NULL); /* appel du constructeur */
			
			sprintf(intToStr, "%d", class_getClass(getChild(tree, 0)->u.str)->constructor->nbParam);
			return writeCode(code, FALSE, NULL, "POPN", intToStr , NULL);// pas nécéssaire a priori si on pop dans le constructeur.
		case BLCDECL:
			sprintf(intToStr, "%d", tree->nbVar);
			code = strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
			return writeCode(code, FALSE, NULL, "POPN", intToStr , "nb variable dans bloc");
		case INSTR: 
			return strcatwalloc(gencode(getChild(tree, 0)), writeCode(NULL, FALSE, NULL, "POPN", "1", NULL));
		case LSTARG: case DECL: case LSTINST:  
			return strcatwalloc(gencode(getChild(tree, 0)), gencode(getChild(tree, 1)));
		case CAST: // (seulement géré a la verif context, va modifier directement l'offset)
			return gencode(getChild(tree, 1));
		default: // case IDCL:
		fprintf(stderr, "Erreur! gencode : etiquette d'operator inconnue: %d\n", tree->op);
		break; 
	}
	return NULL;
}


string genCodeFunc(ClassP c, FunctionP func) 
{
	char intToStr[40] = "";
	string code = NULL;

	sprintf(intToStr, "%s_%s", c->IDClass, func->ID);
	code = writeCode(NULL, FALSE, intToStr, "NOP", NULL, NULL);
	code = strcatwalloc(code, gencode(func->code));

	return writeCode(code, FALSE, NULL, "RETURN", NULL, NULL);
}

string genCodeConst(ClassP c) // l'objet est alloué avant les paramètres
{
	string code = NULL;
	char intToStr[20] = "";

	code = writeCode(NULL, FALSE, c->IDClass, "NOP", NULL, "constructor");
	sprintf(intToStr, "%d", -c->constructor->nbParam-1);
	code = writeCode(code, FALSE, NULL, "PUSHL", intToStr, NULL); //on met l'adresse de l'objet en tete de pile

	if(c->superName != NULL) {
		code = strcatwalloc(code, gencode(c->superCallArgs)); //push des n arguments
		code = writeCode(code, FALSE, NULL, "PUSHA", c->superName , NULL);
		code = writeCode(code, FALSE, NULL, "CALL", NULL , NULL);
		
		//code = writeCode(code, FALSE, NULL, "STOREL", intToStr , NULL); // on stocke le résultat
		sprintf(intToStr, "%d", c->super->constructor->nbParam); // +1 pour la valeur de retour, deja sauvegardée
		code =  writeCode(code, FALSE, NULL, "POPN", intToStr, NULL); // et on retire la pile d'appel
	}
	
	// ici quel que soit le chemin on a l'adresse de l'objet en tete de pile
	sprintf(intToStr, "%d", c->offsetTV);
	code =  writeCode(code, FALSE, NULL, "PUSHG", intToStr, "@TV"); // chargement de la table des symboles de la classe
	code =  writeCode(code, FALSE, NULL, "STORE", "0", NULL); // puis on la stocke dans l'objet a l'offset reservé aux TV

	code = strcatwalloc(code, genFieldInitCode(c, c->cfl)); // initialisation des champs non statiques

	code = strcatwalloc(code, gencode(c->constructor->code)); // le constructeur

	//sprintf(intToStr, "%d", -1 - c->constructor->nbParam);
	//code = writeCode(code, FALSE, NULL, "STOREL", intToStr, NULL); // obsolette ?
	
	return writeCode(code, FALSE, NULL, "RETURN", NULL, NULL);
}

string genFieldInitCode(ClassP c, ClassFieldListP cfl) { // miam la recursion non terminale a cause des structures de données pourries d'Arnaud
	string code = NULL;
	char intToStr[40] = "", intToStr2[40] = "";

	if(cfl==NULL)
		return NULL;

	if(cfl->current->value==NULL)
		return genFieldInitCode(c, cfl->next);
	else {
		code = strcatwalloc(genFieldInitCode(c, cfl->next), gencode(cfl->current->value));
		sprintf(intToStr, "%d", cfl->current->offset);
		switch(cfl->current->nature)
		{
			case STATIC: // offset par rapport a GP
				return writeCode(code, FALSE, NULL, "STOREG", intToStr , "static");
			case NONSTATIC: // offset par rapport a adresse Classe
				sprintf(intToStr2, "%d", - c->constructor->nbParam - 1); // empilage de l'adresse de l'appelant
				code = writeCode(code, FALSE, NULL, "PUSHL", intToStr2, "instance 1/3");
				code = writeCode(code, FALSE, NULL, "SWAP", NULL, "instance 2/3"); // pour remettre les paramètres dans le bon sens
				return writeCode(code, FALSE, NULL, "STORE", intToStr, "instance 3/3");
			default: break;
		}

		return writeCode(code, TRUE, NULL, "NOP", NULL, "erreur d'adressage");
	}
}

string genStaticFieldInitCode(ClassListP cl) {
	if(cl==NULL)
		return NULL;

	return strcatwalloc(genStaticFieldInitCode(cl->next), genFieldInitCode(cl->current, cl->current->staticCfl));
}

string genBaseFuncCode()
{
	string code = NULL;

	code = strcatwalloc(code, "\n--code des fonctions de base");
	code = writeCode(code, FALSE, "toString", "PUSHL", "-1" , NULL);
	code = writeCode(code, FALSE, NULL, "STR", NULL , NULL);
	code = writeCode(code, FALSE, NULL, "STOREL", "-2" , NULL);
	code = writeCode(code, FALSE, NULL, "RETURN", NULL , "fin toString");

	code = writeCode(code, FALSE, "print", "PUSHL", "-1" , NULL);
	code = writeCode(code, FALSE, NULL, "WRITES", NULL , NULL);
	code = writeCode(code, FALSE, NULL, "SWAP", NULL, NULL);
	code = writeCode(code, FALSE, NULL, "RETURN", NULL , "fin print");

	code = writeCode(code, FALSE, "println", "PUSHL", "-1" , NULL);
	code = writeCode(code, FALSE, NULL, "PUSHS", "\"\\n\"" , NULL);
	code = writeCode(code, FALSE, NULL, "CONCAT", NULL , NULL);
	code = writeCode(code, FALSE, NULL, "WRITES", NULL , NULL);
	code = writeCode(code, FALSE, NULL, "SWAP", NULL, NULL);
	code = writeCode(code, FALSE, NULL, "RETURN", NULL , "fin println\n");

	return code;
}

string genBaseCode(ClassListP cl_par)
{
	string code = NULL;
	char intToStr[40] = "";
	ClassListP cl;

	code = strcatwalloc(code, "\n--champs statiques : (ne pas se fier a l'ordre)");
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
		sprintf(intToStr, "%s_TV", cl->current->IDClass);
		code = writeCode(code, FALSE, NULL, "PUSHN", "1" , intToStr);
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
			code = strcatwalloc(code, genCodeFunc(cl->current, scml->current));
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
			code = strcatwalloc(code, genCodeFunc(cl->current, cml->current));
			cml = cml->next;
		}
		cl = cl->next;
	}

	code = strcatwalloc(code, genBaseFuncCode());
	code = writeCode(code, TRUE, "start", "START", NULL , "main function");

	code = strcatwalloc(code, genStaticFieldInitCode(cl_par));

	return strcatwalloc(code, genTVCode(cl_par));
}

string genTVCode(ClassListP cl) {
	char intToStr[40] = "", intToStr2[40] = "";
	string code = NULL;

	code = strcatwalloc(code, "\n--generation des TV:");
	while(cl!=NULL) {
		ClassMethodListP cml = cl->current->instance->methods;


		sprintf(intToStr, "%d", cl->current->nbFunc);
		code = writeCode(code, FALSE, NULL, "ALLOC", intToStr, "allocation TV");
		while(cml!=NULL)
		{
			code = writeCode(code, FALSE, NULL, "DUPN", "1", "adresse TV");

			sprintf(intToStr2, "%s_%s", cml->current->mother->IDClass, cml->current->ID);
			code = writeCode(code, FALSE, NULL, "PUSHA", intToStr2, NULL);

			sprintf(intToStr2, "%d", cml->current->offset);
			code = writeCode(code, FALSE, NULL, "STORE", intToStr2, NULL);
			cml=cml->next;
		}
		sprintf(intToStr, "%d", cl->current->offsetTV);
		code = writeCode(code, FALSE, NULL, "STOREG", intToStr, "stockage TV");

		cl = cl->next;
	}
	return strcatwalloc(code, "\n--fin generation des TV:\n");
}