#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "proj.h"

typedef struct _Var{
	string typeName;
	ClassP type;
	string ID;	
	TreeP value;
}Var, *VarP;

#endif
