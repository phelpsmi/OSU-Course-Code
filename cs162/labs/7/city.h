#ifndef CITY_H_
#define CITY_H_
#include "state.h"

class city: public state {
private:
	char *cname;
public:
	void set_name(const char *n, const char *s);
	void display_name();
	void display_pop();
	city();
	virtual ~city();
};

#endif /* CITY_H_ */
