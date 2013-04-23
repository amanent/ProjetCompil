/*
 * verifContext.c
 *
 *  Created on: Apr 5, 2013
 *      Author: Matthieu
 */
#include "verifContext.h"
#include "proj.h"
#include "proj_y.h"
#include "tree.h"
#include "stdlib.h"
#include "stdio.h"
#include "variable.h"
#include "class.h"
#include "symboles.h"

extern ClassListP classList;
//extern TreeP mainCode;

bool verif_nameResolution(){
	ClassListP currentCL = classList;

	while(currentCL != NULL){

		/* CHECK NON-STATIC CLASS FIELD TYPE*/
		ClassFieldListP currentCFL =currentCL->current->cfl;
		while(currentCFL != NULL){
			VarP currentVar = currentCFL->current;
			if(currentVar->type == NULL){
				currentVar->type = class_getClass(currentVar->typeName);
				if(currentVar->type == NULL) // si on a pas trouvé la classe.
					return FALSE;
			}
			currentCFL = currentCFL->next;
		}

		/* CHECK STATIC CLASS FIELD TYPE*/
		ClassFieldListP currentSCFL = currentCL->current->staticCfl;
		while(currentSCFL != NULL){
			VarP currentVar = currentSCFL->current;
			if(currentVar->type == NULL){
				currentVar->type = class_getClass(currentVar->typeName);
				if(currentVar->type == NULL) // si on a pas trouvé la classe.
					return FALSE;
			}
			currentSCFL = currentSCFL->next;
		}

		/* CHECK NON-STATIC CLASS METHOD */

		ClassMethodListP currentCML = currentCL->current->cml;
		while(currentCML != NULL){
			FunctionP currentFunc = currentCML->current;
			if(currentFunc->returnType == NULL && currentFunc->returnName != NULL) {
				currentFunc->returnType = class_getClass(currentFunc->returnName);
				if(currentFunc->returnType == NULL || verif_paramList(currentFunc) == FALSE) // si on a pas trouvé la classe.
					return FALSE;
			}
			currentCML = currentCML->next;
		}

		/* CHECK STATIC CLASS METHOD */

		ClassMethodListP currentSCML = currentCL->current->cml;
		while(currentSCML != NULL){
			FunctionP currentSFunc = currentCML->current;
			if(currentSFunc->returnType == NULL && currentSFunc->returnName != NULL) {
				currentSFunc->returnType = class_getClass(currentSFunc->returnName);
				if(currentSFunc->returnType == NULL || verif_paramList(currentSFunc) == FALSE) // si on a pas trouvé la classe.
					return FALSE;
			}
			currentCML = currentCML->next;
		}

		/* CHECK CURRENT CLASS SUPER */

		if(currentCL->current->super == NULL && currentCL->current->superName != NULL) {
			currentCL->current->super = class_getClass(currentCL->current->superName);
			if(currentCL->current->super == NULL) // si on a pas trouvé la classe.
				return FALSE;
		}

		currentCL = currentCL->next;
	}

	return FALSE;

}

bool verif_contextuelle(){ // need verif arg.
	if(!verif_nameResolution())
		return FALSE;

	return TRUE;
}

bool verif_classCode(ClassP c){
	SymbolesTableP table = symTable_newTable();
	SymbolesTableP statictable = symTable_newTable();
	
	fillSymTableClassVar(c->cfl, table);
	fillSymTableClassVar(c->staticCfl, statictable);

	fillSymTableClassFunc(c->cml, table);
	fillSymTableClassFunc(c->staticCml, table);



	return TRUE;
}

void fillSymTableClassVar(ClassFieldListP cfl, SymbolesTableP st){
	if(cfl->next)
		fillSymTableClassVar(cfl->next, st);
	symTable_addLine(st, cfl->current, variable);
}

void fillSymTableClassFunc(ClassMethodListP cml, SymbolesTableP st){
	if(cml->next)
		fillSymTableClassFunc(cml->next, st);
//	symTable_addLine(st, cml->current, function);
}

bool verif_paramList(FunctionP func){
	if(func == NULL)
		return FALSE;
	ParamsListP param = func->paramsList;
	while(param){
		if(!class_getClass(param->type))
			return FALSE;
		param = param->next;
	}
	return TRUE;
}


bool verif_func(SymbolesTableP st, FunctionP func){
	return TRUE;
}

bool verif_var(SymbolesTableP st, VarP var){
	return TRUE;
}



typedef struct _context{
	FunctionP func;
	int prevOP;
}Context;

Context context = {NULL, 0};

bool verif_types(SymbolesTableP st, TreeP tree) {
	int i = 0;
	
	if (tree == NULL){
		printf("Verif d'un arbre vide\n");
		return TRUE;
	}
	    
	
	

	switch (tree->op) {
		case STR: //return true, tree->type = String
			tree->type = class_getClass("String"); 
			return TRUE;
			
		case CST: //return true, tree->type = Integer
			tree->type = class_getClass("Integer"); 
			return TRUE;

/**/	case ID: //ajout dans la table
/*			//aff ? dans inst ?
			if(aff){
				//add to symtable + tree->var->ID = u.str
			}
			else{
				//verif presence dans symtable
				//tree->type = symTable_getVar(tree->u.str)->type
			}
*/			
		case EQ: //integer
		case NE:
		case GT:
		case GE:
		case LT:
		case LE:
		case ADD: // verif integer , type integer
		case SUB:
		case MUL:
		case DIV:
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			if(		getChild(tree, 0)->type == class_getClass("Integer")
				&&	getChild(tree, 1)->type == class_getClass("Integer"))			
			{	
				tree->type = class_getClass("Integer");
				return TRUE;
			}
			return FALSE;


		case CONCAT: // string
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			if(		getChild(tree, 0)->type == class_getClass("String")
				&&	getChild(tree, 1)->type == class_getClass("String"))			
			{	
				tree->type = class_getClass("String");
				return TRUE;
			}
			return FALSE;

		case UNARYSUB: //integer
		case UNARYADD: 
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			if(		getChild(tree, 0)->type == class_getClass("Integer"))		
			{	
				tree->type = class_getClass("Integer");
				return TRUE;
			}
			return FALSE;

		case IF: /*IF Exp THEN Inst ELSE Inst*/
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			return (getChild(tree, 0)->type == class_getClass("Integer"));

/**/	case CMPAFF: // Exp2 '.' Id AFF Exp ';' //verif types
/**/	case DIRAFF: // Id AFF Exp ';'
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			return (	(getChild(tree, 1)->type == getChild(tree, 0)->type)||(class_isinheritedFrom(getChild(tree, 1)->type, getChild(tree, 0)->type)));
				

/**/	case SELECT: // Exp2 '.' Id //verif id est dans exp2
		{	

			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;				
			ClassP c = tree->type;
			VarP v = tree->var;
			VarP vv = NULL;
			if(v)
			{
				vv = class_getInstanceFieldFromName(c, getChild(tree, 1)->u.str);
			}
			else 
			{
				vv = class_getStaticFieldFromName(c, getChild(tree, 1)->u.str);
			}
			if(vv){
				tree->var = vv;
				tree->type = vv->type;
				return TRUE;
			}
			return FALSE;
		}
/**/	case RET: //verif type de retour de la func

		case VAR: //VAR Id ':' Idcl AffectO	';' // add dans la table
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;			
			return(	   getChild(tree, 1)->type == getChild(tree, 2)->type
					|| getChild(tree, 2)->type == NULL
					|| class_isinheritedFrom(getChild(tree, 2)->type, getChild(tree, 1)->type));
	
		case MSGSNTS: // voir a factoriser avec MSGSNT
/**/	case MSGSNT: // Exp2 '.' Id '(' ListArgO ')' //verif params && id dans les func de exp2
		{
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			ClassP c = tree->type;
			if(!c) return FALSE;
			FunctionP ff = NULL;
			if(tree->var){
				ff = class_getInstanceMethFromName(c, getChild(tree, 1)->u.str);
			}
			else{
				ff = class_getStaticMethFromName(c, getChild(tree, 1)->u.str);
			}


		}
		

		case CAST: //verification heritage, type = type du cast
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;			
			tree->type = getChild(tree, 0)->type;
			return (class_canAffect(tree->type, getChild(tree, 1)->type));

		case IDCL: // verif tabledesclasses
		{
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;
			ClassP c = class_getClass(tree->u.str);
			tree->type = c;
			return (c != NULL);
		}
/**/	case INSTA: // NEW Idcl '(' ListArgO ')' // verif de la liste d'args du const de idcl
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;			
			tree->type = class_getClass(getChild(tree, 0)->u.str);
			ParamsListP pl = NULL;//Construction de la liste
			return (prmlst_sameTypes (tree->type->constructor->paramsList, pl));

		case INSTR: //gogo child0
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;		
			tree->type = getChild(tree, 0)->type;
			tree->var = getChild(tree, 0)->var;
			tree->func = getChild(tree, 0)->func;
			return TRUE;
		case LSTARG: //a faire apres

		case BLCDECL:
			symTable_enterNewScope(st);
			for(i = 0; i < tree->nbChildren; ++i)
				if(!verif_types(st, getChild(tree, i)))
					return FALSE;

			symTable_exitScope(st);

		case DECL: 

		case LSTINST:


		default: //   (seulement géré a la verif context, va modifier directement l'offset)
		fprintf(stderr, "Erreur! pprint : etiquette d'operator inconnue: %d\n", tree->op);
		break; 
	}
	return FALSE;
}