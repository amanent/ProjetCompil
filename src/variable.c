
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

ArgListElemP arglm_newElem(VarP v){
	ArgListElemP elem = NEW(1, ArgListElem);
	elem->next = NULL;
	elem->current = v;
	return elem;
}

void arglst_pushFront(ArgListP list, VarP v){
	if(!list)
		return;
	ArgListElemP newElem = arglm_newElem(v);
	newElem->next = list->top;
	list->top = newElem;
	if(list->bottom == NULL)
		list->bottom = newElem;
}

void arglst_pushBack(ArgListP list, VarP v){
	if(!list)
		return;
	ArgListElemP newElem = arglm_newElem(v);
	 list->bottom->next = newElem;
	list->bottom = newElem;
	if(list->top == NULL)
		list->top= newElem;
}

