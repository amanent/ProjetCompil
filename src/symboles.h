#ifndef _SYMBOLES_H_
#define _SYMBOLES_H_

	#include "variable.h"
	#include <string.h>

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
		LineP 	current;
		int 	max_rank;
		int* 	nbVarAtRank;
		LineP*	sections;
	}SymbolesTable, *SymbolesTableP;

	SymbolesTableP symTable_newTable();
	void symTable_addLineFromLine(SymbolesTableP theTable, LineP l);
	void symTable_addLine(SymbolesTableP theTable, VarP var, Nature n);
	void symTable_addLineFromScratch();

	bool symTable_isVarDefined(SymbolesTableP t, string varName, string className);
	bool symTable_isNameInUse(SymbolesTableP t, string varName);
	VarP symTable_getVarFromName(SymbolesTableP t, string varName);


	void symTable_enterNewScope(SymbolesTableP table);
	void symTable_exitScope(SymbolesTableP table);
	void symTable_eraseSection(SymbolesTableP t, int sect);
	SymbolesTableP symTable_enterFunction(SymbolesTableP t, FunctionP func);
	LineP symbLine_newLine(VarP var, Nature n);

	SymbolesTableP symTable_duplicate(SymbolesTableP t, unsigned int depth);
	LineP symTable_dupLine(LineP origin,SymbolesTableP receiver);
	LineP symLine_dupLine(LineP origin);

#endif
