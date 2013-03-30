#include <string.h>
#include <stdio.h>

#include "class.h"


ClassListP classList = NULL;
TreeP mainCode = NULL;

void classList_addClass(ClassP c) {
	ClassListP newTop = NEW(1, ClassList);
	newTop->current = c;
	newTop->next = classList;
	classList = newTop;
}

void class_setName(ClassP c, string name) {
	c->IDClass = NEW(strlen(name)+1, char);
	strcpy(c->IDClass,name);
}

void class_addField(ClassP c, boolean isStatic, TreeP decl ) {
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
	
	if(isStatic)
		c->staticCfl = newCFL;
	else
		c->cfl = newCFL;
}

void class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code) {
	FunctionP newMeth = NEW(1, Functionn);
	
	newMeth->ID = NEW(strlen(methodName)+1, char);
	newMeth->returnName = NEW(strlen(returnType)+1, char);
	strcpy(newMeth->ID,methodName);
	strcpy(newMeth->returnName,returnType);

	newMeth->override = visi==1;
	newMeth->paramsList = paramList;
	newMeth->code = code;

	ClassMethodListP newCML = NEW(1, ClassMethodList);
	newCML->current = newMeth;
	newCML->next = c->cml;
	if(visi==2)
		c->staticCml = newCML;
	else
		c->cml = newCML;
}

void class_setConstructor(ClassP c, ParamsListP pl, TreeP code) {
	c->constructor = NEW(1, Functionn);
	c->constructor->ID = "constructor";
	c->constructor->paramsList = pl;
	c->constructor->code = code;
	c->constructor->returnName = c->IDClass;
	c->constructor->returnType = c;
}

ClassP class_getClass(string super){
	ClassListP currentCL = classList;
	
	while(currentCL != NULL) {
		if(strcmp(currentCL->current->IDClass,super))
			return currentCL->current;
		currentCL = currentCL->next;
	}

	return NULL;
}

void class_setSuper(ClassP c, string super, TreeP args){ /* Si on trouve la classe, on ajoute directement la référence, sinon on ajoute juste son nom */
	c->super = class_getClass(super);
	c->superName = NEW(strlen(super)+1, char);
	strcpy(c->superName, super);
	c->superCallArgs = args;
}



string class_print(ClassP cls){
	string str = NEW(2000, char);
	
	strcat(str, cls->IDClass);

	//Heritage ?
	if(cls->superName != NULL){
		strcat(str, " : ");
		strcat(str, cls->superName);
		strcat(str, "(");
		if(cls->super != NULL)
			strcat(str, cls->super->IDClass);
		else
			strcat(str, "class not yet parsed");
		strcat(str, ")");
	}

	//Constructeur
	strcat(str, "\n\t");
	strcat(str, "Constructeur : ");
	strcat(str, function_printFunc(cls->constructor));
	
	//Static Fields
	strcat(str, "\n\tStatic Fields:");
	ClassFieldListP stfl = cls->staticCfl;
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
	ClassMethodListP stml = cls->staticCml;
	while(stml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, "static ");
		strcat(str, function_printFunc(stml->current));
		stml = stml->next;
	}

	//Instance Fields
	strcat(str, "\n\tFields:");
	ClassFieldListP fl = cls->cfl;
	while(fl != NULL){
		strcat(str, "\n\t\t");
		strcat(str, fl->current->typeName);
		strcat(str, " ");
		strcat(str, fl->current->ID);
		fl = fl->next;
	}

	//Methods
	strcat(str, "\n\tMethods:");
	ClassMethodListP ml = cls->cml;
	while(ml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, (char*)function_printFunc(ml->current));
		ml = ml->next;
	}

	return str;
}
string classList_print() {
	string str = NEW(20000, char);
	ClassListP curr = classList;
	while(curr!=NULL) {
		strcat(str, class_print(curr->current));
		strcat(str, "\n\n");
		curr=curr->next;
	}
	return str;
}
