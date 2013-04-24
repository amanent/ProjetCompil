/*
 * verifContext.h
 */

#ifndef VERIFCONTEXT_H_
#define VERIFCONTEXT_H_

#include "proj.h"
#include "class.h"
#include <string.h>
#include "symboles.h"

bool verif_contextuelle();
bool verif_paramList(FunctionP func);
bool verif_classCode(ClassP c);
bool verif_nameResolution();

void verif_contructJumpTable();

void fillSymTableClassVar(ClassFieldListP cfl, SymbolesTableP st);
void fillSymTableClassFunc(ClassMethodListP cml, SymbolesTableP st);
bool verif_paramList(FunctionP func);
bool verif_func(SymbolesTableP st, FunctionP func);
bool verif_var(SymbolesTableP st, VarP var);
bool verif_tree(SymbolesTableP st, TreeP tree);

#endif /* VERIFCONTEXT_H_ */
