#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void assertTrue(int predicate, char *message) 
{
	printf("%s: ", message);
	if (predicate)
		printf("PASSED\n");
	else
		printf("FAILED\n");
}

int main(int argc, char* argv[]) {
        
	/* Test your linked list in here! */
	struct linkedList *lnk;
	lnk = createLinkedList();
	printf("\n\nTesting isEmptyList...\n");
	assertTrue(EQ(isEmptyList(lnk), 1), "List empty: ");
	printf("\n\nTesting addList and isEmptyList...\n");
	addList(lnk, 1);
	assertTrue(EQ(isEmptyList(lnk), 0), "List not empty: ");
	printf("\nTesting addfrontList and frontList...\n");
	addFrontList(lnk, 2);
	assertTrue(EQ(frontList(lnk), 2), "Test 1st element == 2: ");
	printf("\nTesting addbackList and backList...\n");
	addBackList(lnk, 3);
	assertTrue(EQ(backList(lnk), 3), "Test 3rd element == 3: ");
	printf("\nTesting containsList...");
	assertTrue(EQ(containsList(lnk, 1), 1), "Test 2nd element == 1: ");
	printf("\nTesting removefrontList and removebackList...");
	addFrontList(lnk, 4);
	addBackList(lnk, 5);
	removeFrontList(lnk);
	removeBackList(lnk);
	assertTrue(EQ(frontList(lnk), 2), "Test 1st element == 2: ");
	assertTrue(EQ(backList(lnk), 3), "Test 3rd element == 3: ");
	printf("\nTesting printList...\nIf the list printed below does not match the following, it has FAILED: 2, 1, 3\n");
	isEmptyList(lnk);
	printf("\nTesting removeList...");
	removeList(lnk, 3);
	assertTrue(EQ(containsList(lnk, 3), 0), "Test value 3 removed: ");
	printf("\nChecking deleteLinkedList...\n");
	deleteLinkedList(lnk);
	printf("PASSED\n");
	return 0;
}


