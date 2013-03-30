/*
 * Param.h
 *
 *  Created on: Mar 30, 2013
 *      Author: arnaud
 */

#ifndef PARAM_H_
#define PARAM_H_

#include <string>
#include <iostream>

class Param {
public:
	Param(std::string, std::string);
	virtual ~Param();

	std::string type;
	std::string name;

};

std::ostream& operator<<(std::ostream& os, Param const & p);


#endif /* PARAM_H_ */
