#ifndef _VARIABLES_H_
#define _VARIABLES_H_

	typedef struct _Var Var, *VarP;

	#include "proj.h"

	struct _Var{
		string typeName;
		ClassP type;
		string ID;	
		TreeP value;
	};

	bool var_areEquals(VarP v, string varName, string varClass){
		return (v->ID != varName || v->typeName != varClass);
	}

#endif
