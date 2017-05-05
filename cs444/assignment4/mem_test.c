#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define SIZE 100000

int main(){
	char *data[SIZE];
	int i = 0;
	int looped = 0;
	srand(0);
	syscall(353);
	while(1){
		if(looped)
			free(data[i]);

		data[i] = malloc(rand() % 1500);

		i++;
		if(i >= SIZE){
			i = 0;
			looped = 1;
			syscall(353);
		}
	}
}