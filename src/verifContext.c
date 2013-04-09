/*
 * verifContext.c
 *
 *  Created on: Apr 5, 2013
 *      Author: Matthieu
 */
#include "proj.h"
#include <string.h>

ClassP getClass(string name){
	ClassListP currentCL = classList;
	ClassP result = NULL;
	while(currentCL != NULL){
		if(strcmp(currentCL->current->IDClass, name) == 0){
			result = currentCL->current;
			break;
		}
		currentCL = currentCL->next;
	}
	return result;
}

bool verif_contextuelle(){
	/*foreach(class dans classlist){
		foreach(var in static var && pas static var){
			check type (if type = null && typeName == une des class de la class list alors maj pointeur vers cette classe);
		}
		foreach(func in static func && pas static func{
		}
	}*/
	ClassListP currentCL = classList;

	while(currentCL != NULL){

		/* CHECK NON-STATIC CLASS FIELD TYPE*/
		ClassFieldListP currentCFL =currentCL->current->cfl;
		while(currentCFL != NULL){
			VarP currentVar = currentCFL->current;
			if(currentVar->type == NULL){
				currentVar->type = getClass(currentVar->typeName);
			}
			currentCFL = currentCFL->next;
		}

		/* CHECK STATIC CLASS FIELD TYPE*/
		ClassFieldListP currentSCFL = currentCL->current->staticCfl;
		while(currentSCFL != NULL){
			VarP currentVar = currentSCFL->current;
			if(currentVar->type == NULL){
				currentVar->type = getClass(currentVar->typeName);
			}
			currentSCFL = currentSCFL->next;
		}

		/* CHECK NON-STATIC CLASS METHOD */

		ClassMethodListP currentCML = currentCL->current->cml;
		while(currentCML != NULL){
			FunctionP currentFunc = currentCML->current;
			if(currentFunc->returnType == NULL && strcmp(currentFunc->returnName,"VOID") != 0)
				currentFunc->returnType = getClass(currentFunc->returnName);
			currentCML = currentCML->next;
		}

		/* CHECK STATIC CLASS METHOD */

		ClassMethodListP currentSCML = currentCL->current->cml;
		while(currentSCML != NULL){
			FunctionP currentSFunc = currentCML->current;
			if(currentSFunc->returnType == NULL && strcmp(currentSFunc->returnName,"VOID") != 0)
				currentSFunc->returnType = getClass(currentSFunc->returnName);
			currentCML = currentCML->next;
		}

		/* CHECK CURRENT CLASS SUPER */

		if(currentCL->current->super == NULL && currentCL->current->superName != NULL)
			currentCL->current->super = getClass(currentCL->current->superName);

		currentCL = currentCL->next;
	}

	return FALSE;
}
