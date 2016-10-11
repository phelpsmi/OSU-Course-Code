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
    this->pop=0;
}

void nation::set_pop(int n){
    this->pop=n;
}

void nation::display_pop(){
    cout << "Nation pop: " << pop << endl;
}
state nation::getstate(int n){
    return s[n];
}
void nation::set_state(state st, int i){
    s[i]= state(st);
}

nation::~nation() {

}

