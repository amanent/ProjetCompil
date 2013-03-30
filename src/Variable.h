/*
 * Variable.h
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>
#include "proj.h"
#include "Class.h"
class Class;

class Variable {
public:
	Variable(std::string classname, std::string id, TreeP code);
	virtual ~Variable();

	std::string typeName;
	Class* type;
	std::string ID;
	TreeP value;

};

#endif /* VARIABLE_H_ */
