#include <string.h>
#include <stdio.h>

#include "class.h"

ClassListP classList = NULL;
TreeP mainCode = NULL;

void classList_addClass(ClassP c) {
	ClassListP newTop = NEW(1, ClassList);
	newTop->current = c;
	newTop->next = classList;
	if(classList == NULL)
		newTop->n = 0;
	else
		newTop->n = classList->n+1;
	classList = newTop;
}

void class_setName(ClassP c, string name) {
	c->IDClass = NEW(strlen(name)+1, char);
	strcpy(c->IDClass,name);
}

int class_getNb(ClassP c){
	ClassListP tmp = classList;
	while(tmp){
		if(tmp->current == c)
			return tmp->n;
		tmp = tmp->next;
	}
	return -1;
}

int class_getNbFromName(string className){
	ClassListP tmp = classList;
	while(tmp){
		if(tmp->current->IDClass == className)
			return tmp->n;
		tmp = tmp->next;
	}
	return -1;
}

void class_addField(ClassP c, bool isStatic, TreeP decl ) {
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

	if(isStatic){
		newClassField->nature = STATIC;
		newCFL->next = c->staticCfl;
		c->staticCfl = newCFL;
	}
	else
	{
		newClassField->nature = NONSTATIC;
		newCFL->next = c->cfl;
		c->cfl = newCFL;
	}
}

void class_addMethod(ClassP c, int visi, string methodName, string returnType, ParamsListP paramList, TreeP code) {
	FunctionP newMeth = NEW(1, Function);

	newMeth->ID = NEW(strlen(methodName)+1, char);
	strcpy(newMeth->ID,methodName);

	newMeth->returnName = NEW(strlen(returnType)+1, char);
	strcpy(newMeth->returnName,returnType);

	newMeth->override = (visi==1);
	newMeth->paramsList = paramList;
	newMeth->code = code;
	newMeth->mother = c;

	ClassMethodListP newCML = NEW(1, ClassMethodList);
	newCML->current = newMeth;

	if(visi==2)
	{
		newCML->next = c->staticCml;
		c->staticCml = newCML;
	}
	else {
		newCML->next = c->cml;
		c->cml = newCML;
	}
}

void class_setConstructor(ClassP c, ParamsListP pl, TreeP code) {
	c->constructor = NEW(1, Function);
	c->constructor->ID = "constructor";
	c->constructor->paramsList = pl;
	c->constructor->code = code;
	c->constructor->returnName = c->IDClass;
	c->constructor->returnType = c;
}

ClassP class_getClass(string className){
	ClassListP currentCL = classList;

	while(currentCL != NULL) {
		if(!strcmp(currentCL->current->IDClass, className))
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
	strcat(str, function_printFunc(class->constructor));

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
	while(fl != NULL){
		strcat(str, "\n\t\t");
		strcat(str, fl->current->typeName);
		strcat(str, " ");
		strcat(str, fl->current->ID);
		fl = fl->next;
	}

	//Methods
	strcat(str, "\n\tMethods:");
	ClassMethodListP ml = class->cml;
	while(ml != NULL){
		strcat(str, "\n\t\t");
		strcat(str, (char*)function_printFunc(ml->current));
		ml = ml->next;
	}

	return str;
}

bool class_isinheritedFrom(ClassP c, ClassP cc){
	if(c->super == NULL)
		return FALSE;
	return (c->super == cc || class_isinheritedFrom(c->super, cc));

}

bool class_canAffect(ClassP c, ClassP cc){
	return (c == cc || class_isinheritedFrom(cc, c));
}


int class_getNbFields(ClassP c){
	int sum = 0;
	ClassFieldListP tmp = c->cfl;
	while(tmp){
		sum++;
		tmp = tmp->next;
	}
	return sum;
}

bool class_generateJumpTable(ClassP c){

	if(c->instance)
		return TRUE;


	//fprintf(stderr, "%s------------------------\n", c->IDClass);

	if(c->super != NULL){
		if(c->super->instance == NULL){
			class_generateJumpTable(c->super);
		}
		c->instance = jtable_duplicate(c->super->instance);
		c->statics = NEW(1, JumpTable);
		c->nbFields = c->super->nbFields;
		c->nbFunc = c->super->nbFunc;
	}
	else{
		c->instance = NEW(1, JumpTable);
		c->statics = NEW(1, JumpTable);
	}


	ClassMethodListP cmltmp = c->cml;
	while(cmltmp){
		ClassMethodListP over = override(c->instance->methods, cmltmp->current);

		if(over){
			if(cmltmp->current->override == FALSE || ! prmlst_sameTypes(over->current->paramsList, cmltmp->current->paramsList))
				return FALSE;
			cmltmp->current->offset = over->current->offset;
			over->current = cmltmp->current;
			//			fprintf(stderr, "--%s - %s - %d\n", c->IDClass, over->current->ID,over->current->offset);
		}
		else{
			ClassMethodListP newMethod = NEW(1, ClassMethodList);
			newMethod->next = NULL;
			newMethod->current  = cmltmp->current;
			newMethod->current->offset = c->nbFunc++;
			if(c->instance->methods)
				ml_getLast(c->instance->methods)->next = newMethod;
			else
				c->instance->methods = newMethod;
			//			fprintf(stderr, "--%s - %s - %d\n", c->IDClass, newMethod->current->ID,newMethod->current->offset  );
		}
		cmltmp = cmltmp->next;
	}



	cmltmp = c->staticCml;
	while(cmltmp){
		ClassMethodListP newMethod = NEW(1, ClassMethodList);
		newMethod->next = NULL;
		newMethod->current  = cmltmp->current;
		if(c->statics->methods)
			ml_getLast(c->statics->methods)->next = newMethod;
		else
			c->statics->methods = newMethod;
		cmltmp = cmltmp->next;
	}

	ClassFieldListP cfltmp = c->cfl;
	while(cfltmp){
		c->nbFields++;
		ClassFieldListP newField = NEW(1, ClassFieldList);
		newField->next = NULL;
		newField->current = cfltmp->current;
		newField->current->offset = c->nbFields;
		if(c->instance->fields)
			fl_getLast(c->instance->fields)->next = newField;
		else
			c->instance->fields = newField;
		cfltmp = cfltmp->next;
	}

	cfltmp = c->staticCfl;
	while(cfltmp){
		ClassFieldListP newField = NEW(1, ClassFieldList);
		newField->next = NULL;
		newField->current = cfltmp->current;
		if(c->statics->fields)
			fl_getLast(c->statics->fields)->next = newField;
		else
			c->statics->fields = newField;
		cfltmp = cfltmp->next;
	}

/*
	ClassMethodListP ccc = c->instance->methods;
	while(ccc){
		fprintf(stderr, "--%s - %s - %s - %d\n", c->IDClass, ccc->current->ID,
			ccc->current->mother->IDClass, ccc->current->offset);
		ccc = ccc->next;
	}
	fprintf(stderr, "-------------------\n");

	ClassMethodListP cml = c->instance->methods;
		while(cml!=NULL)
		{
			fprintf(stderr, "%s : %s, %d\n", c->IDClass, cml->current->ID, cml->current->offset);
			cml = cml->next;
		}*/

	return TRUE;

}

ClassMethodListP override(ClassMethodListP orig, FunctionP func){
	ClassMethodListP tmp = orig;

	while(tmp){
		if(!strcmp(func->ID, tmp->current->ID))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

ClassMethodListP ml_getLast(ClassMethodListP ml){
	ClassMethodListP tmp = ml;
	while(tmp->next != NULL)
		tmp = tmp->next;
	return tmp;
}

ClassFieldListP fl_getLast(ClassFieldListP fl){
	ClassFieldListP tmp = fl;
	while(tmp->next != NULL)
		tmp = tmp->next;
	return tmp;
}

JumpTableP jtable_duplicate(JumpTableP j){
	JumpTableP jump = NEW(1, JumpTable);

	ClassFieldListP  jcfl = j->fields;
	ClassMethodListP jcml = j->methods;

	ClassFieldListP  ff = NULL;
	ClassMethodListP mm = NULL;

	while(jcfl){
		ClassFieldListP  fff = NEW(1, ClassFieldList);
		fff->current = jcfl->current;
		if(ff)
			ff->next = fff;
		else
			jump->fields = fff;
		ff = fff;
		jcfl = jcfl->next;
	}

	while(jcml){
		ClassMethodListP mmm = NEW(1, ClassMethodList);
		mmm->current = jcml->current;
		if(mm)
			mm->next = mmm;
		else
			jump->methods = mmm;
		mm = mmm;
		jcml = jcml->next;
	}

	return jump;
}

int jtable_getOffsetInst(ClassP c, string argName){
	int off = 1;
	int last = 0;
	ClassFieldListP cfltmp = c->instance->fields;
	while(cfltmp){
		if(!strcmp(cfltmp->current->ID, argName))
			last = off;
		++off;
		cfltmp = cfltmp->next;
	}
	if(last)
		return last;
	off = 0;
	ClassMethodListP cmltmp = c->instance->methods;
	while(cmltmp){
		if(!strcmp(cmltmp->current->ID, argName))
			return off;
		++off;
		cmltmp = cmltmp->next;
	}
	return -1;
}

int jtable_getOffsetStatic(ClassP c, string argName){
	int off = 1;
	ClassFieldListP cfltmp = c->statics->fields;
	while(cfltmp){
		if(!strcmp(cfltmp->current->ID, argName))
			return off;
		++off;
		cfltmp = cfltmp->next;
	}

	off = 0;
	ClassMethodListP cmltmp = c->statics->methods;
	while(cmltmp){
		if(!strcmp(cmltmp->current->ID, argName))
			return off;
		++off;
		cmltmp = cmltmp->next;
	}
	return -1;
}

VarP class_getInstanceFieldFromName(ClassP c, string varName){
/*	ClassFieldListP tmp = c->instance->fields;
	while(tmp){
		if(!strcmp(varName, tmp->current->ID))
			return tmp->current;
		tmp = tmp->next;
	}
	return NULL;

*/
	VarP last = NULL;
	ClassFieldListP cfltmp = c->instance->fields;
	while(cfltmp){
		if(!strcmp(cfltmp->current->ID, varName))
			last = cfltmp->current;
		cfltmp = cfltmp->next;
	}
	return last;
}

VarP class_getStaticFieldFromName(ClassP c, string varName){
	ClassFieldListP tmp = c->staticCfl;
	while(tmp){
		if(!strcmp(varName, tmp->current->ID))
			return tmp->current;
		tmp = tmp->next;
	}
	return NULL;
}

FunctionP class_getInstanceMethFromName(ClassP c, string funcName){
	ClassMethodListP tmp = c->instance->methods;
	while(tmp){
	//fprintf(stderr, "treating : %s\n", tmp->current->ID);
		if(!strcmp(funcName, tmp->current->ID))
			return tmp->current;
		tmp = tmp->next;
	}
	return NULL;

}
FunctionP class_getStaticMethFromName(ClassP c, string funcName){
	ClassMethodListP tmp = c->staticCml;
	while(tmp){
		if(!strcmp(funcName, tmp->current->ID))
			return tmp->current;
		tmp = tmp->next;
	}
	return NULL;
}
