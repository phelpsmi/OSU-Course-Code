/*
 * nation.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */

#include "nation.h"
#include <iostream>
using namespace std;

nation::nation() {
	// TODO Auto-generated constructor stub
    this->pop=0;
}
void nation::set_pop(int n){
    this->pop=n;
}

void nation::display_pop(){
    cout << "Nation pop: " << pop << endl;
}

nation::~nation() {
	// TODO Auto-generated destructor stub
}

