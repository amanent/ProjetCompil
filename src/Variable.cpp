/*
 * Variable.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#include "Variable.h"

Variable::Variable(std::string className, std::string id, TreeP code) :
	typeName(className), ID(id), value(code)
{
	type = Class::Classes[typeName];
}

Variable::~Variable() {
	// TODO Auto-generated destructor stub
}

