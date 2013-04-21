#ifndef _FUNCTION_H_
#define _FUNCTION_H_

	typedef struct _ParamsList ParamsList, *ParamsListP;
	typedef struct _Function Function, *FunctionP;

	#include "tree.h"
	#include "class.h"
	#include "proj.h"

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
	};
	
/*
	void prmlst_addParam(ParamsListP list, string type, string name);
	ParamsListP prmlst_getLast (ParamsListP elem);
*/
	bool prmlst_sameTypes (ParamsListP l, ParamsListP ll);
	ParamsListP function_makeParam(string name, string type);
	string function_printFunc(FunctionP func);
#endif
