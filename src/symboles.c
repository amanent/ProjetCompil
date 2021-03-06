#include "symboles.h"
#include "stdio.h"

SymbolesTableP symTable_newTable(){
	SymbolesTableP table = NEW(1, SymbolesTable);
	table->nbVarAtRank = NEW(50, int);
	table->sections = NEW(50, LineP);
	table->max_rank = 0;
	return table;
}

void symTable_addLineFromLine(SymbolesTableP theTable, LineP l){
	LineP current = theTable->current;
	theTable->current = l;
	l->next = current;
	l->depth = theTable->max_rank;
	l->rang = ++(theTable->nbVarAtRank[theTable->max_rank - 1]);
}

void symTable_addLine(SymbolesTableP theTable, VarP var, e_nature n){
	LineP current = theTable->current;
	LineP l = symbLine_newLine(var, n);
	theTable->current = l;
	l->next = current;
	l->depth = theTable->max_rank;
	l->rang = ++(theTable->nbVarAtRank[theTable->max_rank - 1]);
}


void symTable_enterNewScope(SymbolesTableP table){
	table->sections[table->max_rank - 1] = table->current;
	++table->max_rank;

}


bool func_isStatic(FunctionP f, ClassP c){
	ClassMethodListP tmp = c->staticCml;
	while(tmp){
		if(f == tmp->current)
			return TRUE;
		tmp = tmp->next;
	}
	return FALSE;
}

SymbolesTableP symTable_enterFunction(SymbolesTableP t, FunctionP func, ClassP c){
	//SymbolesTableP nt = symTable_duplicate(t, 0);
	//Section 0 = Global
	//SymbolesTableP nt = symTable_newTable();
	SymbolesTableP nt = t;
	//Section 1 = Params -> sec0
	symTable_enterNewScope(nt);
	ParamsListP prm = func->paramsList;
	int nbParams = function_howManyArgs(func);
	int i = 0;
	while(prm != NULL){
		VarP v = NEW(1, Var);
		v->ID = prm->name;
		v->typeName = prm->type;
		v->type = class_getClass(v->typeName);
		v->offset = -nbParams + (i++);
		v->nature = PARAM;
		symTable_addLine(nt, v, PARAM);
		prm = prm->next;
	}

	bool isStatic = func_isStatic(func, c);
	if(!isStatic)
	{
		VarP this = NEW(1, Var);
		this->ID = "this";
		this->type = c;
		this->typeName = c->IDClass;
		this->offset = -nbParams - 1;
		this->nature = PARAM;
		symTable_addLine(nt, this, PARAM);
	}

	if(func->returnType && c->constructor != func) {
		VarP res = NEW(1, Var);
		res->ID = "result";
		res->type = func->returnType;
		res->typeName = res->type->IDClass;
		res->offset = -nbParams - 2 + isStatic;
		res->nature = PARAM;
		symTable_addLine(nt, res, PARAM);
	}

	//Section 2 = Entering function code -> sec 1
	symTable_enterNewScope(nt);

	return nt;
}

void symTable_printTable(SymbolesTableP t)
{
	LineP tmp = t->current;
	while(tmp != NULL) {
		fprintf(stderr, "%s : %s (%s) @ %d\n", tmp->v->ID, tmp->v->typeName, var_natToString(tmp->n), tmp->v->offset);
		tmp = tmp->next;
	}
}


void symTable_exitScope(SymbolesTableP table){
	table->nbVarAtRank[table->max_rank - 1] = 0;
	--table->max_rank;
	table->current = table->sections[table->max_rank - 1];
}

/*TODO si on veut cleaner la memoire*/
void symTable_eraseSection(SymbolesTableP t, int sect){
	t->current = t->sections[t->max_rank-1];
}

LineP symbLine_newLine(VarP var, e_nature n){
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

VarP symTable_getVarFromName(SymbolesTableP t, string varName){
	LineP tmp = t->current;
	while(tmp != NULL) {
		//printf("%s, %s\n", tmp->v->ID, tmp->v->typeName);
		if(!strcmp(varName, tmp->v->ID))
			return tmp->v;
		tmp = tmp->next;
	}
	return NULL;
}

bool symTable_isNameInUse(SymbolesTableP t, string varName){
	LineP tmp = t->current;
	int nbVarInScope = t->nbVarAtRank[t->max_rank-1];
	while(tmp != NULL && nbVarInScope > 0) {
		if(!strcmp(varName, tmp->v->ID))
			return TRUE;
		tmp = tmp->next;
		nbVarInScope--;
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
	if(origin == NULL)
		return NULL;
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
