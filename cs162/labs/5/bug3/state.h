/*
 * state.h
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */

#ifndef STATE_H_
#define STATE_H_

class state {
private:
	char *name;
	int pop;
public:
	state operator=(state);
	void set_name(const char *);
	void display_name();
	void display_pop();
	void set_pop(int);
	state();
	state(const state&);
	virtual ~state();
};

#endif /* STATE_H_ */
