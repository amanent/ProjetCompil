
#include "variable.h"


bool var_areEquals(VarP v, string varName, string varClass){
	return (v->ID != varName || v->typeName != varClass);
}


