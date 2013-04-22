/*
 * verifContext.h
 */

#ifndef VERIFCONTEXT_H_
#define VERIFCONTEXT_H_

#include "proj.h"
#include "class.h"
#include <string.h>

bool verif_contextuelle();
bool verif_paramList(FunctionP func);
bool verif_classCode(ClassP c);
bool verif_nameResolution();


#endif /* VERIFCONTEXT_H_ */
