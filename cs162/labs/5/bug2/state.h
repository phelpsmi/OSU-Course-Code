/*
 * state.h
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */

#ifndef STATE_H_
#define STATE_H_
#include <string>
#include "nation.h"
using namespace std;


class state : public nation{
protected:
	string st_name;
public:
	void set_name(string n);
	void virtual display_pop();
	state();
	virtual ~state();
};

#endif /* STATE_H_ */
