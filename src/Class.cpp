/*
 * Class.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#include "Class.h"

std::map<std::string, Class*> Class::Classes;

Class::Class(std::string name) :
	IDClass(name), constructor(nullptr), super(nullptr), superCallArgs(nullptr)
{
	registerClass(IDClass);

}

Class::~Class() {
	// TODO Auto-generated destructor stub
}

void Class::addField(Class* c, bool isStatic, TreeP decl) {
	Variable v(decl->u.children[1]->u.str, decl->u.children[0]->u.str, decl->u.children[2]);

}

bool Class::registerClass(std::string name) {
	if(Class::Classes[name] != nullptr)
		return false;
	Class::Classes[name] = this;
	return true;
}
