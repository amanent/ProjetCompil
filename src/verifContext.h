/*
 * verifContext.h
 */

#ifndef VERIFCONTEXT_H_
#define VERIFCONTEXT_H_

#include "proj.h"
#include "class.h"
#include <string.h>
#include "symboles.h"

int verif_contextuelle();
bool verif_paramList(FunctionP func);
bool verif_classCode(ClassP c);
bool verif_nameResolution();

void verif_contructJumpTable();

int fillSymTableClassVar(ClassFieldListP cfl, SymbolesTableP st);
int fillSymTableClassFunc(ClassMethodListP cml, SymbolesTableP st);
void fillSymTableStaticVar(ClassFieldListP cfl, SymbolesTableP st);
bool verif_paramList(FunctionP func);
bool verif_classCode(ClassP c);
bool verif_class(ClassP c);
bool verif_allClassesCode();
bool verif_func(SymbolesTableP st, FunctionP func, ClassP c);
bool verif_types(SymbolesTableP st, TreeP tree, ClassP c, FunctionP f);

#endif /* VERIFCONTEXT_H_ */
