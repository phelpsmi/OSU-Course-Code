int length(struct node *start){
	int i = 1;
	bool new = true;
	struct node *other;
	while(new){
		other = start.next;
		if(*other = *start)
			new = false;
	}
}
void push(struct node **head, int newVal){
	struct node *newNode;
	newNode.next = head.next;
	newNode.val = newVal;
	head.next = newNode;
}
void print(struct node * other, int){
	if(i > 1){
		printf("%d", val, ", ");
		print(other, i-1);
	} else if(i == 0){
		printf("%d", val);
	}
}

void append(struct node ** list, int newVal){}
void clear(struct node **list){}
void delete(struct node **list, int i){}
void sort_ascending(struct node **){} //Assign 5 stuff
void sort_descending(struct node **){}