/***********************************************************
** Program: lic.c
** Author: Michael Phelps
** Date: 6/6/2014
** Description: Functions to handling a linked list
***********************************************************/

#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/********************************************************************* 
 ** Function: length
 ** Description: returns the length of the linked list
 ** Parameters: node
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/ 
int length(struct node *start){
	int i = 0;
	struct node *other;
	other = start;

	while(1){
		if(other == NULL)
			return i;
		i++;
		other = other->next;
	}
}

/********************************************************************* 
 ** Function: print
 ** Description: prints out the values of the linked list up to the desired amount
 ** Parameters: node, int
 ** Pre-Conditions: i is less than or equal to the length of head
 ** Post-Conditions: none
 *********************************************************************/ 
void print(struct node * head, int i){
	if(i > 1){
		printf("%d %s", head->val, ", ");
		print(head->next, i-1);
	} else if(i == 1){
		printf("%d \n", head->val);
	}
}

/********************************************************************* 
 ** Function: push
 ** Description: placed a new node at the front of the list
 ** Parameters: node**, int
 ** Pre-Conditions: head is the front of the linked list
 ** Post-Conditions: head points to the new front of the list
 *********************************************************************/ 
void push(struct node **head, int newVal){
	struct node *newNode = (struct node *) malloc( sizeof(struct node) );
	newNode->next = *head;
	newNode->val = newVal;
	*head = newNode;
}

/********************************************************************* 
 ** Function: append
 ** Description: ads a new node to the end of the list
 ** Parameters: node**, int
 ** Pre-Conditions: none
 ** Post-Conditions: new node is placed at the back of the list
 *********************************************************************/ 
void append(struct node ** head, int newVal){
	struct node *newNode = (struct node *) malloc( sizeof(struct node) );
	newNode->val = newVal;

	if(*head == NULL){
		newNode->next = *head;
		*head = newNode;
		return;
	}
	struct node *current = *head;
	int i;
	for (i = 0; i < length(*head)-1; ++i){
		current = current->next;
	}
	newNode->next = current->next;
	current->next = newNode;
}

/********************************************************************* 
 ** Function: clear
 ** Description: clears every node in the list
 ** Parameters: node**
 ** Pre-Conditions: head points to the start of the list
 ** Post-Conditions: all memory is freed and head points to NULL
 *********************************************************************/ 
void clear(struct node **head){
	// O(n^2)
	if(length(*head) > 0){
		clear(&(*head)->next);
	}
	free(*head);
	
}

/********************************************************************* 
 ** Function: delete
 ** Description: removes a specific node in the list
 ** Parameters: node**, int
 ** Pre-Conditions: head is the start of the list and the length of the list is greater than x
 ** Post-Conditions: the specified node is freed from memory
 *********************************************************************/ 
void delete(struct node **head, int x){
	//delete a certain certain index in the list
	//zero based index
	struct node *temp;
	if(x == 0){
		temp = (*head)->next;
		free(*head);
		*head = temp;
	} else if(x == 1){
		temp = (*head)->next;
		(*head)->next = temp->next;
		free(temp);
	}
	else{
		delete(&(*head)->next, x-1);
	}

}

/********************************************************************* 
 ** Function: sort_ascending
 ** Description: sorts the nodes from smallest val to highest val
 ** Parameters: node**
 ** Pre-Conditions: head is the start of the list
 ** Post-Conditions: all values are sorted in order
 *********************************************************************/ 
void sort_ascending(struct node **head){
	bool swap = true;
	int i;
	while(swap){
		swap = false;
		struct node *current = *head;
		struct node *after = current->next;
		struct node *previous = NULL;
		for (i = 0; i < length(*head)-1; ++i){
			if(current->val > after->val){
				current->next = after->next;
				after->next = current;
				if(previous != NULL){
					previous->next = after;
				} else {
					*head = after;
				}
				swap = true;
			}
			previous = current;
			current = after;
			after = after->next;
		}
	}
}

/********************************************************************* 
 ** Function: sort_descending
 ** Description: sorts the nodes from highest val to smallest val
 ** Parameters: node**
 ** Pre-Conditions: head is the start of the list
 ** Post-Conditions: all values are sortet in order
 *********************************************************************/ 
void sort_descending(struct node **head){
	// Decided it would be better to swap the addresses rather than swap the values
	// Because just swapping the values seemed too easy.
		bool swap = true;
	int i;
	while(swap){
		swap = false;
		struct node *current = *head;
		struct node *after = current->next;
		struct node *previous = NULL;
		for (i = 0; i < length(*head)-1; ++i){
			if(current->val < after->val){
				current->next = after->next;
				after->next = current;
				if(previous != NULL){
					previous->next = after;
				} else {
					*head = after;
				}
				swap = true;
			}
			previous = current;
			current = after;
			after = after->next;
		}
	}
}