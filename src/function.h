#ifndef _FUNCTION_H_
#define _FUNCTION_H_

	typedef struct _ParamsList ParamsList, *ParamsListP;
	typedef struct _Function Function, *FunctionP;

	#include "tree.h"
	#include "class.h"
	#include "proj.h"
	#include "variable.h"

	struct _ParamsList {
		string type;
		string name;
		struct _ParamsList* next;
	};

	struct _Function {
		bool override;
		string ID;
		ParamsListP paramsList;
		TreeP code;
		ClassP returnType;
		string returnName;
		int nbParam;
		int offset;
	};
	
/*
	void prmlst_addParam(ParamsListP list, string type, string name);
	ParamsListP prmlst_getLast (ParamsListP elem);
*/
	bool prmlst_sameTypes (ParamsListP l, ParamsListP ll);
	bool prmlst_goodCallArgs (FunctionP f, ArgListP args);
	ParamsListP function_makeParam(string name, string type);
	string function_printFunc(FunctionP func);
	bool function_hasReturnType(FunctionP func);
	int function_howManyArgs(FunctionP func);
#endif
