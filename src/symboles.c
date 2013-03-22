#include "symboles.h"

SymbolesTableP symTable_newTable(){
	return (SymbolesTableP)malloc(sizeof(SymbolesTable));
}

void symTable_addLineFromLine(SymbolesTableP theTable, LineP l){
	LineP current = theTable->current;
	theTable->current = l;
	l->next = current;
}

void symTable_addLineFromScratch(){

}
