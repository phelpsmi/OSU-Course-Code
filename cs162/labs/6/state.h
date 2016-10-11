#include "nation.h"

class state: public nation {
protected:
	char *name;
public:
	virtual void set_name(const char *);
	virtual void display_name();
	virtual void display_pop();
	state();
	virtual ~state();
};
