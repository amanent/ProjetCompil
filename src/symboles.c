#include "symboles.h"

SymbolesTableP symTable_newTable(){
	SymbolesTableP table = NEW(1, SymbolesTable);
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

SymbolesTableP symTable_enterFunction(SymbolesTableP t, FunctionP func){
	//SymbolesTableP nt = symTable_duplicate(t, 0); FUCK YOU BENJAMIN ARTHUR PATRICK BLOIS
	//Section 0 = Global
	SymbolesTableP nt = symTable_newTable();
	//Section 1 = Params -> sec0
	symTable_enterNewScope(nt);
	ParamsListP prm = func->paramsList;
	while(prm != NULL){
		VarP v = NEW(1, Var);
		v->ID = prm->name;
		v->typeName = prm->type;
		v->type = class_getClass(v->typeName);
		symTable_addLine(nt, v, parameter);
	}

	//Section 2 = Entering function code -> sec 1
	symTable_enterNewScope(nt);

	return nt;
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

SymbolesTableP symTable_duplicate(SymbolesTableP t, unsigned int depth) {
	SymbolesTableP nt = symTable_newTable();
	symTable_dupLine(t->sections[depth], nt);

	nt->max_rank = depth;
	int i, j; LineP cur = nt->current;
	for(i = 0; i <= depth; ++i){
		nt->nbVarAtRank[i] = t->nbVarAtRank[i];
		for(j = 0; j < nt->nbVarAtRank[i]; ++j){
			cur = cur->next;
		}
		nt->sections[i] = cur;
	}
	return nt;
}

LineP symTable_dupLine(LineP origin,SymbolesTableP receiver){
	LineP next = NULL;
	if(origin->next != NULL)
		next = symTable_dupLine(origin->next, receiver);
	LineP cur = symLine_dupLine(origin);
	cur->next = next;
	symTable_addLineFromLine(receiver, cur);
	return cur;
}

LineP symLine_dupLine(LineP origin) {
	LineP ll = symbLine_newLine(origin->v, origin->n);
	ll->depth = origin->depth;
	ll->rang = origin->rang;
	ll->next = NULL;
	return ll;
}
