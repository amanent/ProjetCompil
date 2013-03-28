#include <string.h>
#include <stdio.h>

#include "class.h"

ClassListP classList = NULL;


void classList_addClass(ClassP c) {
	ClassListP newTop = NEW(1, ClassList); /*(ClassListP)malloc(sizeof(ClassList));*/
	newTop->current = c;
	newTop->next = classList;
	classList = newTop;
}

void class_setName(ClassP c, string name) {
	c->IDClass = NEW(strlen(name)+1, char); /*(string)malloc(strlen(name)*sizeof(char));*/
	strcpy(c->IDClass,name);
}

void class_addField(ClassP c, int isStaticp, TreeP decl ) {
	string type = decl->u.children[1]->u.str;
	string name = decl->u.children[0]->u.str;
	VarP newClassField = NEW(1, Var);
	newClassField->typeName = NEW(strlen(type)+ 1, char);
	newClassField->ID = NEW(strlen(name)+1,char);
	strcpy(newClassField->typeName,type);
	strcpy(newClassField->ID,name);
	newClassField->value = decl->u.children[2];
	ClassFieldListP newCFL = NEW(1, ClassFieldList);
	newCFL->current = newClassField;
	newCFL->next = c->cfl;
	c->cfl = newCFL;
}

FunctionP class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code) {
	FunctionP newMeth = NEW(1, Function); /*(ClassMethodP)malloc(sizeof(ClassMethod));*/
	newMeth->ID = NEW(strlen(methodName)+1, char); /*(string)malloc(strlen(methodName)*sizeof(char));*/
	newMeth->returnName = NEW(strlen(returnType)+1, char); /*(string)malloc(strlen(type)*sizeof(char));*/
	strcpy(newMeth->ID,methodName);
	strcpy(newMeth->returnName,returnType);

	newMeth->override = visi==1;
	newMeth->paramsList = paramList;
	newMeth->code = code;

	ClassMethodListP newCML = NEW(1, ClassMethodList); /*(ClassMethodListP)malloc(sizeof(ClassMethodList));*/
	newCML->current = newMeth;
	newCML->next = c->cml; /* surement un problème a ce niveau la */
	c->cml = newCML;
	return NULL;
}

void class_setConstructor(ClassP c, ParamsListP pl, TreeP code) {
	c->constructor = NEW(1, Function);
	c->constructor->paramsList = pl;
	c->constructor->code = code;
}

ClassP class_getClass(string super){
	ClassListP currentCL = classList;
	ClassP theSuper = classList->current;
	while(theSuper != NULL && strcmp(theSuper->IDClass,super) != 0){
		currentCL = currentCL->next;
		theSuper = currentCL->current;
	}

	return theSuper;
}

void class_setSuper(ClassP c, string super, TreeP args){ /* Si on trouve la classe, on ajoute directement la référence, sinon on ajoute juste son nom */
	c->super = class_getClass(super);
	c->superName = NEW(strlen(super)+1, char);
	strcpy(c->superName, super);
	c->superCallArgs = args;
}

string classList_print() {
	string str = NEW(20000, char);
	ClassP curr = classList->current;
	while(curr!=NULL) {
		printf("%s", class_print(curr));
		strcat(str, class_print(curr));
		strcat(str, "\n\n");
	}
	return str;
}

string class_print(ClassP class){
	string str = NEW(2000, char);
	strcat(str, class->IDClass);

	//Heritage ?
	if(class->superName != NULL){
		strcat(str, " : ");
		strcat(str, class->superName);
		strcat(str, "(");
		if(class->super != NULL)
			strcat(str, class->super->IDClass);
		else
			strcat(str, "class not yet parsed");
		strcat(str, ")");
	}

	//Constructeur
	strcat(str, "\n\t");
	strcat(str, "Constructeur : ");
	function_printFunc(class->constructor);

	//Static Fields
	strcat(str, "\n\tStatic Fields:");
	ClassFieldListP stfl = class->staticCfl;
	while(stfl != NULL){
		strcat(str, "\n\t\t");
		strcat(str, "static ");
		strcat(str, stfl->current->typeName);
		strcat(str, " ");
		strcat(str, stfl->current->ID);
		stfl = stfl->next;
	}

	//Static Methods
	strcat(str, "\n\tStatic Methods:");
	ClassMethodListP stml = class->staticCml;
	while(stml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, "static ");
		strcat(str, function_printFunc(stml->current));
		stml = stml->next;
	}


	//Instance Fields
	strcat(str, "\n\tFields:");
	ClassFieldListP fl = class->cfl;
	while(stfl != NULL){
		strcat(str, "\n\t\t");
		strcat(str, fl->current->typeName);
		strcat(str, " ");
		strcat(str, fl->current->ID);
		fl = fl->next;
	}

	//Methods
	strcat(str, "\n\tMethods:");
	ClassMethodListP ml = class->cml;
	while(stml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, (char*)function_printFunc(ml->current));
		ml = ml->next;
	}


	return str;
}
