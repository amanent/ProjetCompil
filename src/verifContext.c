/*
 * verifContext.c
 *
 *  Created on: Apr 5, 2013
 *      Author: Matthieu
 */
#include "proj.h"
 #include "class.h"
#include <string.h>

extern ClassListP classList;
//extern TreeP mainCode;

bool verif_contextuelle(){ // need verif arg.

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
			if(currentFunc->returnType == NULL && currentSFunc->returnName != NULL) {
				currentFunc->returnType = class_getClass(currentFunc->returnName);
				if(currentFunc->returnType == NULL) // si on a pas trouvé la classe.
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
				if(currentSFunc->returnType == NULL) // si on a pas trouvé la classe.
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
