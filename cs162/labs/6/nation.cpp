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
    cout << "USA pop: " << pop << endl;
}

nation::~nation() {

}
void nation::set_name(const char *n, const char *s){}

void nation::set_name(const char* c){}
