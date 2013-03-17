#IFNDEF _SYMBOLES_H_
#DEFINE _SYMBOLES_H_

typedef enum{
	variable,function,parameter;
}Nature;

typedef struct _Line
{
	union{
		ClassP c;
		VarP v;
	} id;
	unsigned int depth;
	Nature n;
	unsigned int rang;
}Line, *LineP;

typedef struct _SymbolesTable{
	LineP current;
	LineP next;
}SymbolesTable, *SymbolesTableP;

#ENDIF