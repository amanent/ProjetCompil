/*
 * Function.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#include "Function.h"
#include <sstream>

Function::Function(std::string id, TreeP functCode, std::string returnClassName) :
override(false), ID(id), code(functCode), returnName(returnClassName)
{
	returnType = Class::Classes[returnName];
}

Function::~Function() {
	// TODO Auto-generated destructor stub
}


bool sameArgs(std::deque<Param> const & l, std::deque<Param>const & ll){
	if(l.size() != l.size())
		return false;
	for(int i(0); i < l.size(); ++i)
		if(l[i].type != ll[i].type)
			return false;
	return true;
}

void Function::addParamFront(Param param) {
	paramList.push_front(param);
}

void Function::addParamBack(Param param) {
	paramList.push_back(param);
}


std::ostream& operator<<(std::ostream& os, Function const & f){
	std::stringstream ss;
	ss << f.returnName << " (";
	if(f.returnType == NULL)
		ss << "CLASS NOT YET PARSED";
	else
		ss << f.returnType->IDClass;

	ss << " )  ";
	ss << f.ID << "( ";
//	for(int i(0), s = f.paramList.size(); i < s; ++i)
	for(auto &p : f.paramList)
	{
//		ss << f.paramList[i];
//		if(i != s-1)
//			ss << ", ";
		ss << p << ", ";
	}
	ss << ")";
	if(f.override)
			ss << "[override]";
	os << ss.str();

	return os;
}








