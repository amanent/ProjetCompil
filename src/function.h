#ifndef _FUNCTION_H_
#define _FUNCTION_H_

	typedef struct _ParamsList ParamsList, *ParamsListP;
	typedef struct _ClassMethod ClassMethod, *ClassMethodP;

	#include "tree.h"
	#include "class.h"
	#include "proj.h"

	struct _ParamsList {
		string type;
		string name;
		struct _ParamsList* next;
	};

	typedef struct _Function {
		string ID;
		ParamsList * paramsList;
		TreeP code;
		ClassP returnType;
		string returnName;
	}Function, *FunctionP;
	
	struct _ClassMethod{
	  int visibility;
	  string type;
	  Function function;
	};
	

	void prmlst_addParam(ParamsListP list, string type, string name);
	ParamsListP prmlst_getLast (ParamsListP elem);
	bool prmlst_sameTypes (ParamsListP l, ParamsListP ll);
	ParamsListP function_makeParam(string name, string type);
	ParamsListP prmlst_newElem(string type, string name);
#endif
