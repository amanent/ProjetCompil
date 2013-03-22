#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "proj.h"

typedef struct _ParamsList {
	string type;
	string name;
	struct _ParamsList* next;
}ParamsList, *ParamsListP;

typedef struct _Function {
	string ID;
	ParamsList * paramsList;
	TreeP code;
	ClassP returnType;
	string returnName;
}Function, *FunctionP;

void prmlst_addParam(ParamsListP list, string type, string name);
ParamsListP prmlst_getLast (ParamsListP elem);
bool prmlst_sameTypes (ParamsListP l, ParamsListP ll);
ParamsListP function_makeParam(string name, string type);

#endif
