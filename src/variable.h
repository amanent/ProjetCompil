#ifndef _VARIABLES_H_
#define _VARIABLES_H_

	typedef struct _Var Var, *VarP;

	#include "proj.h"
	#include "class.h"

	typedef enum 
	{
		STATIC, NONSTATIC, PARAM, LOCAL
	} e_nature;

	struct _Var{
		string typeName;
		ClassP type;
		string ID;	
		TreeP value;
		int offset;
		e_nature nature;
	};

	typedef struct _ArgListElem{
		ClassP current;
		struct _ArgListElem* next;
	}ArgListElem, *ArgListElemP;

	typedef struct _ArgList{
		ArgListElemP top;
		ArgListElemP bottom;
	}ArgList, *ArgListP;



	bool var_areEquals(VarP v, string varName, string varClass);
	ArgListP arglst_newList();
	ArgListElemP arglm_newElem(ClassP c);
	void arglst_pushFront(ArgListP list, ClassP c);
	void arglst_pushBack(ArgListP list, ClassP c);



#endif
