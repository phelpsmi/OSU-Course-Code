struct node {
	int val;
	struct node *next;
};

int length(struct node *);
void push(struct node **, int);
void print(struct node *, int);

void append(struct node **, int);
void clear(struct node **);
void delete(struct node **, int);
void sort_ascending(struct node **); //Assign 5 stuff
void sort_descending(struct node **);