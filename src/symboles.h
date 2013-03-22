#ifndef _SYMBOLES_H_
#define _SYMBOLES_H_

	#include "variable.h"

	typedef enum{
		variable,function,parameter
	}Nature;

	typedef struct _Line
	{
		VarP v;
		unsigned int depth;
		Nature n;
		unsigned int rang;
		struct _Line * next;
	}Line, *LineP;

	typedef struct _SymbolesTable{
		LineP current;
	}SymbolesTable, *SymbolesTableP;

	SymbolesTableP symTable_newTable();
	void symTable_addLineFromLine(SymbolesTableP theTable, LineP l);
	void symTable_addLineFromScratch();

#endif
