#include "function.h"
#include <string.h>

void prmlst_addParam(ParamsListP list, string type, string name){
	prmlst_getLast(list).next = prmlst_newElem(type, name);
}

ParamsListP prmlst_getLast (ParamsListP elem){
	ParamsListP tmp = elem;
	while(tmp.next != NULL)
		tmp = tmp.next;
	return tmp;
}

bool prmlst_sameTypes (ParamsListP l, ParamsListP ll){
	if(l == ll)
		return TRUE;
	if(l == NULL || ll == NULL)
		return FALSE;
	while(l != NULL && ll != NULL){
		if(l.type != ll.type)
			return FALSE;
		l = l.next;
		ll = ll.next;
	}
	return TRUE;
}

ParamsListP function_makeParam(string name, string type){
	ParamsListP new = (ParamsListP)malloc(sizeof(ParamsList));
	new.name = name;
	new.type = type;
	new.next = NULL;
	return new;
}
