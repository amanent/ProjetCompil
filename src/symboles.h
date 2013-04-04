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
		LineP 	current;
		int 	max_rank;
		int* 	nbVarAtRank;
		LineP*	sections;
	}SymbolesTable, *SymbolesTableP;

	SymbolesTableP symTable_newTable();
	void symTable_addLineFromLine(SymbolesTableP theTable, LineP l);
	void symTable_addLine(SymbolesTableP theTable, VarP var, Nature n);
	void symTable_addLineFromScratch();


	void symTable_enterNewScope(SymbolesTableP table);
	void symTable_exitScope(SymbolesTableP table);
	void symTable_eraseSection(SymbolesTableP t, int sect);
	LineP symbLine_newLine(VarP var, Nature n);

#endif
