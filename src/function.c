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

ParamsListP prmlst_newElem(string type, string name){
	ParamsListP newElem = malloc(sizeof(ParamsList));
	newElem.name = name;
	newElem.type = type;
	newElem.next = NULL;
	return newElem;
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







