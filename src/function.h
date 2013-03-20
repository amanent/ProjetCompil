#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "proj.h"
typedef struct _Function{
	string ID;
	ParamsList * paramsList;
	TreeP code;
	ClassP returnType;
	string returnName;
}Function, *FunctionP;

typedef struct _ParamsList{
	string type;
	string name;
	struct _ParamsList* next;
}ParamsList, *ParamsListP;

#endif
