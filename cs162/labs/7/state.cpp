/*
 * state.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */
#include <iostream>
#include <cstring>
#include "nation.h"

using namespace std;

void state::set_name(const char *n) {
	delete [] name;
	name=new char[strlen(n)+1];
	strcpy(name, n);
}

void state::display_name() {
	cout << "State is: " << name << endl;
}

void state::display_pop() {
	cout << "State of, " << name << ", USA, pop: " << pop << endl;
}

state::state() {
	pop=0;
	name=NULL;
}

state::~state() {

}

void state::set_name(const char *n, const char *s){}