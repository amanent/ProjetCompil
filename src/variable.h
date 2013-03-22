#ifndef _VARIABLES_H_
#define _VARIABLES_H_

	typedef struct _ClassField ClassField, *ClassFieldP;

	#include "proj.h"

	typedef struct _Var{
		string typeName;
		ClassP type;
		string ID;	
		TreeP value;
	}Var, *VarP;
	
	struct _ClassField{
	  int visibility;
	  Var v;
	};

#endif
