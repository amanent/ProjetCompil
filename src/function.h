#IFNDEF _FUNCTION_H_
#DEFINE _FUNCTION_H_

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

#ENDIF