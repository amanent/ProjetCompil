/*
 * Function.h
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include "Param.h"
#include <deque>
#include "tree.h"
#include <iostream>
#include "Class.h"

class Class;

class Function {
public:
	Function(std::string, TreeP, std::string);
	virtual ~Function();

	bool override;
	std::string ID;
	std::deque<Param> paramList;
	TreeP code;
	Class* returnType;
	std::string returnName;

	void addParamFront(Param);
	void addParamBack(Param);

};

bool sameArgs(std::deque<Param> const & l, std::deque<Param>const & ll);
std::ostream& operator<<(std::ostream& os, Function const & f);

#endif /* FUNCTION_H_ */
