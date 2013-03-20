#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "proj.h"
typedef struct _Function{
	string ID;
	ParamsList * paramsList;
	TreeP code;
}Function, *FunctionP;

typedef struct _ParamsList{
	string type;
	string name;
	struct _ParamsList* next;
}ParamsList, *ParamsListP;

ParamsListP prmlst_newElem(string type, string name);
bool prmlst_sameTypes (ParamsListP, ParamsListP);


#endif
