#include "list.h"
#include <stdio.h>

int main(){
	char ans;
	int num;
	struct node *head = NULL;
	printf("%i \n", head);
	do {
		do {
			printf("Enter a number: ");
			scanf("%d", &num);
			append(&head, num); //Can change to append for back

			printf("Do you want another num (y or n): ");
			scanf("%1s",&ans);
		} while(ans == 'y');

		/*printf("Sort ascending or descending (a or d)? ");
		scanf("%1s",&ans);

		if(ans == 'a') sort_ascending(&head);
		else if(ans == 'd') sort_descending(&head);*/

		printf("The length is %d \n",length(head));

		print(head, length(head));

		printf("Enter an index to delete ");
		scanf("%d", &num);
		delete(&head, num);

		printf("The length is %d \n",length(head));

		print(head, length(head));


		printf("Do you want to do this again (y or n)? ");
		scanf("%1s",&ans);
		if(ans == 'y') clear(&head);

	} while(ans == 'y');

	return 0;
}