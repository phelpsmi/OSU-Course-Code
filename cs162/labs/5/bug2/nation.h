/*
 * nation.h
 *
 *  Created on: Apr 25, 2014
 *      Author: eecs162
 */

#ifndef NATION_H_
#define NATION_H_

class nation {
private:
protected:
	int pop;  //This was going to be inherited
public:
	nation();
	virtual ~nation();
	void set_pop(int);
	void virtual display_pop();
};

#endif /* NATION_H_ */
