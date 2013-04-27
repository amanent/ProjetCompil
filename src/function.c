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
	if(func->override)
		strcat(str, "[override]");
		
	return str;
}

bool function_hasReturnType(FunctionP func){
	return !(func->returnType == NULL || func->returnName == NULL || !strcmp(func->returnName, ""));
}

int function_howManyArgs(FunctionP func){
	int nArgs = 0;
	ParamsListP tmp = func->paramsList;
	while(tmp){
		++nArgs;
		tmp = tmp->next;
	}
	func->nbParam = nArgs;
	return nArgs;
}

bool prmlst_goodCallArgs (FunctionP f, ArgListP args){
	ParamsListP params;
	ArgListElemP arg;
//printf("entering : %x, %x\n", f, args);
	if(args==NULL) {
		if(f==NULL) return FALSE;
//		printf("%s %x \n", f->ID, f->paramsList);
		return f==NULL || f->paramsList==NULL;
	}
//printf("arg not null \n");
	if(f==NULL)
		return args->top==NULL;
//printf("the params are not null\n");
	params = f->paramsList;
	arg = args->top;
	while(params != NULL && arg != NULL){
//		printf("comparing %s != %s\n", arg->current->IDClass, params->type);
		if(arg->current != class_getClass(params->type)) {
//			printf("nop\n");
			return FALSE;
		}
		arg = arg->next;
		params = params->next;
	}
//	printf("the params are the same, but maybe there is more of one of them\n");
	return (params==NULL && arg==NULL); // faux si pas le meme nombre de paramètres
}
