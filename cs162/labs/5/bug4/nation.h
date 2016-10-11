/*
 * nation.h
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */

#ifndef NATION_H_
#define NATION_H_
#include "state.h"

class nation {
private:
	state s[50];
	int pop;
public:
	nation();
	virtual ~nation();
	void set_pop(int);
	void display_pop();
	state getstate(int);
	void set_state(state, int);
	void display_states_info(state *);
};

#endif /* NATION_H_ */
