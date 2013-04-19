#ifndef _VARIABLES_H_
#define _VARIABLES_H_

	typedef struct _Var Var, *VarP;

	#include "proj.h"
	#include "class.h"

	struct _Var{
		string typeName;
		ClassP type;
		string ID;	
		TreeP value;
		int local_offset, nature;
	};

	bool var_areEquals(VarP v, string varName, string varClass);

#endif
