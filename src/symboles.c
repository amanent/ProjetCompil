#include "symboles.h"

SymbolesTableP symTable_newTable(){
	SymbolesTableP table = (SymbolesTableP)malloc(sizeof(SymbolesTable));
	table->nbVarAtRank = NEW(20, int);
	table->sections = NEW(20, LineP);
	table->max_rank = 0;
	return table;
}

void symTable_addLineFromLine(SymbolesTableP theTable, LineP l){
	LineP current = theTable->current;
	theTable->current = l;
	l->next = current;
	l->depth = theTable->max_rank;
	l->rang = ++(theTable->nbVarAtRank[theTable->max_rank]);
}

void symTable_addLine(SymbolesTableP theTable, VarP var, Nature n){
	LineP current = theTable->current;
	LineP l = symbLine_newLine(var, n);
	theTable->current = l;
	l->next = current;
	l->depth = theTable->max_rank;
	l->rang = ++(theTable->nbVarAtRank[theTable->max_rank]);
}


void symTable_addLineFromScratch(){

}

void symTable_enterNewScope(SymbolesTableP table){
	table->sections[table->max_rank] = table->current;
	++table->max_rank;

}

void symTable_exitScope(SymbolesTableP table){
	table->nbVarAtRank[table->max_rank] = 0;
	--table->max_rank;
	table->current = table->sections[table->max_rank];
}

/*TODO si on veut cleaner la memoire*/
void symTable_eraseSection(SymbolesTableP t, int sect){
	t->current = t->sections[t->max_rank-1];
}

LineP symbLine_newLine(VarP var, Nature n){
	LineP line =  NEW(1, Line);
	line->n = n;
	line->v = var;
	return line;
}

bool symTable_isVarDefined(SymbolesTableP t, string varName, string className){
	LineP tmp = t->current;
	while(tmp != NULL) {
		if(var_areEquals(tmp->v, varName, className))
			return TRUE;
		tmp = tmp->next;
	}
	return FALSE;
}

