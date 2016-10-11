#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	char letter;

	int seed = time(NULL);
	srand(seed);

	if (argc < 2){
		printf("No string length provided\n");
		exit(1);
	}
	int len = atoi(argv[1]);
	int i;
	for(i = 0; i < len; i++){
		printf("%c", letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "[rand() % 27]);
	}
	printf("\n");

}