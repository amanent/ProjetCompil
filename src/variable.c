
#include "variable.h"


bool var_areEquals(VarP v, string varName, string varClass){
	return (v->ID != varName || v->typeName != varClass);
}


ArgListP arglst_newList(){
	ArgListP list = NEW(1, ArgList);
	list->bottom 	= NULL;
	list->top 		= NULL;
	return list;
}

ArgListElemP arglm_newElem(ClassP c){
	ArgListElemP elem = NEW(1, ArgListElem);
	elem->next = NULL;
	elem->current = c;
	return elem;
}

void arglst_pushFront(ArgListP list, ClassP c){
	if(!list)
		return;
	ArgListElemP newElem = arglm_newElem(c);
	newElem->next = list->top;
	list->top = newElem;
	if(list->bottom == NULL)
		list->bottom = newElem;
}

void arglst_pushBack(ArgListP list, ClassP c){
	if(!list)
		return;
	ArgListElemP newElem = arglm_newElem(c);
	 list->bottom->next = newElem;
	list->bottom = newElem;
	if(list->top == NULL)
		list->top= newElem;
}

string var_natToString(e_nature n)
{
	switch(n)
	{
		case STATIC: return "static";
		case NONSTATIC: return "instance";
		case PARAM: return "parametre";
		case LOCAL: return "locale";
	}
	return "";
}