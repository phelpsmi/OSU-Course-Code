class nation {
protected:
	int pop;
public:
	nation();
	virtual ~nation();
	void set_pop(int);
	virtual void display_pop();
	virtual void set_name(const char *);
	virtual void set_name(const char *n, const char *s);
};

class state: public nation {
protected:
	char *name;
public:
	void set_name(const char *);
	virtual void set_name(const char *n, const char *s);
	void display_name();
	void display_pop();
	state();
	virtual ~state();
};


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