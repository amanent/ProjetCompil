#include <string.h>

#include "class.h"

ClassListP classList = NULL;

void classList_init() {
	classList = NEW(1, ClassList); /*(ClassListP)malloc(sizeof(ClassList)); */
}

void classList_addClass(string name){
	ClassP newClass = NEW(1, Class); /*(ClassP)malloc(sizeof(Class)); */
	newClass->IDClass = NEW(strlen(name), char); /*(string)malloc(strlen(name)*sizeof(char));*/
	strcpy(newClass->IDClass,name);
	ClassListP newTop = NEW(1, ClassList); /*(ClassListP)malloc(sizeof(ClassList));*/
	newTop->current = newClass;
	newTop->next = classList;
	classList = newTop;
}

void class_addField(ClassP c, int isStaticp, TreeP decl ) {
	string type = decl->u.children[1]->u.str;
	string name = decl->u.children[0]->u.str;
	ClassFieldP newClassField = NEW(1, ClassField);
	newClassField->v.typeName = NEW(strlen(type)+ 1, char);
	newClassField->v.ID = NEW(strlen(name)+1,char);
	strcpy(newClassField->v.typeName,type);
	strcpy(newClassField->v.ID,name);
	newClassField->v.value = decl->u.children[2];
	ClassFieldListP newCFL = NEW(1, ClassFieldList);
	newCFL->current = newClassField;
	newCFL->next = c->cfl;
	c->cfl = newCFL;
}

ClassMethodP class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code) {
	ClassMethodP newMeth = NEW(1, ClassMethod); /*(ClassMethodP)malloc(sizeof(ClassMethod));*/
	newMeth->function.ID = NEW(strlen(methodName), char); /*(string)malloc(strlen(methodName)*sizeof(char));*/
	newMeth->function.returnName = NEW(strlen(returnType), char); /*(string)malloc(strlen(type)*sizeof(char));*/
	strcpy(newMeth->function.ID,methodName);
	strcpy(newMeth->function.returnName,returnType);

	newMeth->visibility = visi;
	newMeth->function.paramsList = paramList;
	newMeth->function.code = code;

	ClassMethodListP newCML = NEW(1, ClassMethodList); /*(ClassMethodListP)malloc(sizeof(ClassMethodList));*/
	newCML->current = newMeth;
	newCML->next = c->cml; /* surement un problème a ce niveau la */
	c->cml = newCML;
	return NULL;
}

void class_setConstructor(ClassP c, ParamsListP pl, TreeP code) {
	c->constructor = NEW(1, ClassMethod);
	c->constructor->function.paramsList = pl;
	c->constructor->function.code = code;
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
	c->superName = NEW(strlen(super), char);
	c->superCallArgs = args;
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
	function_printFunc(&(class->constructor->function));

	//Static Fields
	strcat(str, "\n\tStatic Fields:");
	ClassFieldListP stfl = class->staticCfl;
	while(stfl != NULL){
		strcat(str, "\n\t\t");
		strcat(str, "static ");
		strcat(str, stfl->current->v.typeName);
		strcat(str, " ");
		strcat(str, stfl->current->v.ID);
		stfl = stfl->next;
	}

	//Static Methods
	strcat(str, "\n\tStatic Methods:");
	ClassMethodListP stml = class->staticCml;
	while(stml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, "static ");
		strcat(str, function_printFunc(&(stml->current->function)));
		stml = stml->next;
	}


	//Instance Fields
	strcat(str, "\n\tFields:");
	ClassFieldListP fl = class->cfl;
	while(stfl != NULL){
		strcat(str, "\n\t\t");
		strcat(str, fl->current->v.typeName);
		strcat(str, " ");
		strcat(str, fl->current->v.ID);
		fl = fl->next;
	}

	//Methods
	strcat(str, "\n\tMethods:");
	ClassMethodListP ml = class->cml;
	while(stml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, (char*)function_printFunc(&(ml->current->function)));
		ml = ml->next;
	}


	return str;
}
