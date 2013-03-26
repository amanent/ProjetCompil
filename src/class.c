#include <string.h>

#include "class.h"

ClassListP classList = NULL;

void classList_init() {
	classList = (ClassListP)malloc(sizeof(ClassList));
}

void classList_addClass(string name){
	ClassP newClass = (ClassP)malloc(sizeof(Class));
	newClass->IDClass = (string)malloc(strlen(name)*sizeof(char));
	strcpy(newClass->IDClass,name);
	ClassListP newTop = (ClassListP)malloc(sizeof(ClassList));
	newTop->current = newClass;
	newTop->next = classList;
	classList = newTop;
}
/*
void class_addField(ClassP c, string type, string name, TreeP var ){
	ClassFieldP newClassField = (ClassFieldP)malloc(sizeof(ClassField));
	newClassField->v->typeName = (string)malloc(strlen(type)*sizeof(char) + 1);
	newClassField->v->ID = (string)malloc(strlen(name)*sizeof(char) + 1);
	strcpy(newClassField->v->typeName,type);
	strcpy(newClassField->v->ID,name);
	newClassField->v->value = var;
	ClassFieldListP newCFL = (ClassFieldListP)malloc(sizeof(ClassFieldList));
	newCFL->current = newClassField;
	newCFL->next = c->cfl;
	c->cfl = newCFL;
}*/
void class_addField(ClassP c, int static, TreeP decl ) {
	/* todo to add a variable to the class */
}

ClassMethodP class_addMethodByClass(ClassP c, string methodName, string type){
	ClassMethodP newMeth = (ClassMethodP)malloc(sizeof(ClassMethod));
	newMeth->function.ID = (string)malloc(strlen(methodName)*sizeof(char));
	newMeth->function.returnName = (string)malloc(strlen(type)*sizeof(char));
	strcpy(newMeth->function.ID,methodName);
	strcpy(newMeth->function.returnName,type);
	ClassMethodListP newCML = (ClassMethodListP)malloc(sizeof(ClassMethodList));
	newCML->current = newMeth;
	newCML->next = c->cml; /* surement un problème a ce niveau la */
	c->cml = newCML;
	return newMeth;
}

/*ClassMethodP class_addMethod(string type, string c, string methodName, string returnType, ParamsListP paramList, TreeP code){
	ClassListP currentCL = classList;
	ClassP theClass = classList->current;
	while(theClass != NULL && strcmp(theClass->IDClass,c)){
		currentCL = currentCL->next;
		theClass = currentCL->current;
	}

	if(theClass != NULL){
		ClassMethodP meth = class_addMethodByClass(theClass, methodName, returnType);
		meth->function->code = code;
		meth->function->paramsList = paramList;
		meth->type = type;
		return meth;
	}
	return NULL;
} */
ClassMethodP class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code) {
	/* to do to create a right method */
	return NULL;
}

void class_setConstructorParam(ClassMethodP constructor, ParamsListP pl){
	constructor->function.paramsList = pl;
}

void class_setConstructor(ClassP c, ParamsListP pl, TreeP code);
/*
	TODO : adapter le code !
	void class_setConstructor(ClassP c, ParamsListP pl){
		*/
	class_setConstructorParam(c->constructor, pl);
}

bool class_setSuperClass(ClassP c, string super){
	ClassListP currentCL = classList;
	ClassP theSuper = classList->current;
	while(theSuper != NULL && strcmp(theSuper->IDClass,super) != 0){
		currentCL = currentCL->next;
		theSuper = currentCL->current;
	}

	if(theSuper != NULL){
		c->super = theSuper;
		return TRUE;
	}
	return FALSE;
}

void class_setSuperName(ClassP c, string super){
	c->superName = (string)malloc(strlen(super)*sizeof(char));
}

void class_setParam(ClassMethodP meth, ParamsListP pl){
	meth->function.paramsList = pl;
}

void class_addParent(ClassP c, string super, TreeP args){
	if(!class_setSuperClass(c,super))
		class_setSuperName(c,super);
	c->superCallArgs = args;
}
