/*
 * Param.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#include "Param.h"

Param::Param(std::string ttype, std::string nname) :
	type(ttype), name(nname)
{
	// TODO Auto-generated constructor stub

}

Param::~Param() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& os, Param const & p){
	os << p.type << " " << p.name;
	return os;
}
