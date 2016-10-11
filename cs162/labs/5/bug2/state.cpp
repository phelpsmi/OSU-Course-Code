/*
 * state.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */
#include <iostream>
#include "state.h"

void state::set_name(string n) {
	st_name=n;
}
void state::display_pop() {
	cout << "state, " << st_name << ", pop: " << pop << endl;

}

state::state() {
	// TODO Auto-generated constructor stub

}

state::~state() {
	// TODO Auto-generated destructor stub
}

