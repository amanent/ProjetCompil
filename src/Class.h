/*
 * Class.h
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#ifndef CLASS_H_
#define CLASS_H_
#include <string>
#include "Function.h"
#include <list>
#include <stack>
#include <map>
#include "ClassField.h"
#include "ClassMethod.h"
#include "tree.h"
#include "Variable.h"


class Function;
class Variable;

class Class {
public:
	Class(std::string);
	virtual ~Class();

	std::string IDClass;
	Function* constructor;
	std::list<Variable> staticFields;
	std::list<Function> staticMethods;
	std::list<Variable> fields;
	std::list<Function> methods;

	Class* super;
	std::string superName;
	TreeP superCallArgs;

	static std::map<std::string, Class*> Classes;
	void addField(Class*, bool, TreeP);


private:
	bool registerClass(std::string);

};

#endif /* CLASS_H_ */
