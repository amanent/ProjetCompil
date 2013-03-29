#include "function.h"
#include <string.h>
#include <stdio.h>
/*
void prmlst_addParam(ParamsListP list, string type, string name){
	prmlst_getLast(list->next = prmlst_newElem(type, name));
}

ParamsListP prmlst_getLast (ParamsListP elem){
	ParamsListP tmp = elem;
	while(tmp->next != NULL)
		tmp = tmp->next;
	return tmp;
}
*/

bool prmlst_sameTypes (ParamsListP l, ParamsListP ll){
	if(l == ll)
		return TRUE;
	if(l == NULL || ll == NULL)
		return FALSE;
	while(l != NULL && ll != NULL){
		if(l->type != ll->type)
			return FALSE;
		l = l->next;
		ll = ll->next;
	}
	return TRUE;
}

ParamsListP function_makeParam(string name, string type){
	ParamsListP new = NEW(1, ParamsList);
	new->name = NEW(strlen(name)+1, char);
	new->type = NEW(strlen(type)+1, char);
	strcpy(new->name, name);
	strcpy(new->type, type);
	
	new->next = NULL;
	return new;
}

string function_printFunc(FunctionP func){
	string str = NEW(2000, char);
	//printf("toto %x\n", func);
	if(func==NULL)
		return "";
//printf("toto 11%s\n", str);
	strcat(str, func->returnName);
	strcat(str, "(");
//printf("toto 22 %s\n", str);	
	if(func->returnType != NULL)
		strcat(str, func->returnType->IDClass);
	else
		strcat(str, "CLASS NOT YET PARSED");
	strcat(str, ")  ");
	strcat(str, func->ID);
	strcat(str, "( ");
	ParamsListP tmp = func->paramsList;
//printf("toto 33%s\n", str);
	while(tmp != NULL){
		strcat(str, tmp->type);
		strcat(str, " ");
		strcat(str, tmp->name);

		tmp = tmp->next;
		if(tmp != NULL)
			strcat(str, ", ");
	}
//printf("toto 44%s\n", str);
	strcat(str, ")");
	return str;
}
