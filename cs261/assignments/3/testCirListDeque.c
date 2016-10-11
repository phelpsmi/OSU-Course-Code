#include "cirListDeque.h"
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
	struct cirListDeque *dq;
	dq = createCirListDeque();
	assertTrue(EQ(isEmptyCirListDeque(dq), 1), "\nisEmpty test: ");
	printf("\nTesting addFront, addBack, front, and back...\n");
	addFrontCirListDeque(dq, 1);
	assertTrue(EQ(frontCirListDeque(dq), 1), "Test 1st element == 1: ");
	addFrontCirListDeque(dq, 2);
	addBackCirListDeque(dq, 3);
	assertTrue(EQ(backCirListDeque(dq), 3), "Test 3rd element == 3: ");
	addBackCirListDeque(dq, 4);
	assertTrue(EQ(frontCirListDeque(dq), 2), "Test 1st element == 2: ");
	assertTrue(EQ(backCirListDeque(dq), 2), "Test 4th element == 4: ");
	assertTrue(EQ(isEmptyCirListDeque(dq), 0), "isEmpty test 2: ");

	printf("\nTesting addFront and addBack\n");
	addFrontCirListDeque(dq, 8);
	addBackCirListDeque(dq, 9);
	assertTrue(EQ(frontCirListDeque(dq), 8), "Test first element == 8: ");
	assertTrue(EQ(backCirListDeque(dq), 9), "Test last element == 9: ");
	printf("\nTesting removeFront and removeBack\n");
	removeFrontCirListDeque(dq);
	removeBackCirListDeque(dq);
	assertTrue(EQ(frontCirListDeque(dq), 2), "Test first element == 2: ");
	assertTrue(EQ(backCirListDeque(dq), 4), "Test last element == 4: ");
	

	printf("\nTesting print and reverse, the following lines should be reverses of each other...\n");
	printCirListDeque(dq);

	printf("\nShould now be reverse...\n");
	reverseCirListDeque(dq);
	printCirListDeque(dq);

	printf("\nTesting delete and free...\n");
	deleteCirListDeque(dq);
	printf("Testing complete.\n");
	return 0;
}


