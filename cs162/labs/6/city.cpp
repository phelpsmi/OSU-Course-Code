#include <iostream>
#include <cstring>
#include "nation.h"

using namespace std;

void city::set_name(const char *n, const char *s) {
	delete [] name;
	delete [] cname;
	cname=new char[strlen(n)+1];
	strcpy(cname, n);
	
	name = new char[strlen(s)+1];
	strcpy(name, s);
}

void city::display_name() {
	cout << "City is: " << name << endl;
}

void city::display_pop() {
	cout << "City of, " << cname << ", " << name << ", USA, pop: " << pop << endl;
}

city::city() {
	pop=0;
	cname=NULL;
	name=NULL;
}

city::~city() {

}
