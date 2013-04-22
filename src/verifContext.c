/*
 * verifContext.c
 *
 *  Created on: Apr 5, 2013
 *      Author: Matthieu
 */
#include "verifContext.h"


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
	symTable_addLine(st, cml->current, function);
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

bool verif_tree(SymbolesTableP st, TreeP tree) {
	return TRUE;
}
