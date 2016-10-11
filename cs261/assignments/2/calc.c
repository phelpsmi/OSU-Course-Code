#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "dynamicArray.h"
#include "calc.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

int is_num(char* str){
	int i;
	return 1337;
}

int validDouble(char* s){
	int has_dot = 0;
	int x;

	if(strcmp(s, "pi"))
		return 1;
	else if(strcmp(s, "e"))
		return 1;

	for(x=0; x < strlen(s); ++x){
		if(s[x] > 47 && s[x] < 58){
		} 
		else if(s[x] == '.' && has_dot == 0){
			has_dot = 1;
		} 
		else if(x == 0 && s[x] == '-'){
		} 
		else{
			return 0;
		}
	}

	return 1;
}

int find_operator(char* str){
	if(strcmp(str, "+") == 0)
		return 1;
	if (strcmp(str, "-") == 0)
		return 2;
	if (strcmp(str, "/") == 0)
		return 3;
	if (strcmp(str, "x") == 0)
		return 4;
	if (strcmp(str, "^") == 0)
		return 5;
	if (strcmp(str, "^2") == 0)
		return 6;
	if (strcmp(str, "^3") == 0)
		return 7;
	if (strcmp(str, "abs") == 0)
		return 8;
	if (strcmp(str, "sqrt") == 0)
		return 9;
	if (strcmp(str, "exp") == 0)
		return 10;
	if (strcmp(str, "ln") == 0)
		return 11;
	if (strcmp(str, "log") == 0)
		return 12;
	return 0;
}

float operate(int op, float v1, float v2){
	switch(op){
		case 1:
			return v1 + v2;
		case 2:
			return v1 - v2;
		case 3:
			return v1/v2;
		case 4:
			return v1*v2;
		case 5:
			return pow(v1, v2);
		case 6:
			return pow(v1, 2);
		case 7:
			return pow(v1, 3);
		case 8:
			return fabs(v1);
		case 9:
			return sqrt(v1);
		case 10:
			return exp(v1);
		case 11:
			return log(v1);
		case 12:
			return log10(v1);
	}
	return 0;
}

int main(int argc, char* argv[]){
	DynArr* args;
	args = createDynArr(4);

	int i;
	for(i = 1; i < argc; i++){
		int op = find_operator(argv[i]);
		if(op > 0 && op < 6 && args->size < 2){
			printf("invalid arguments you dum cunt\n");
			return 1;
		} else if (op > 5 && op < 13 && args->size < 1){
			printf("Invalid number of operators\n");
			return 1;
		} else if (op == 0 && validDouble(argv[i]) == 0){
			printf("Invalid number of operators\n");
			return 1;
		}

		if(op > 0){
			double v1, v2;
			if(op < 6){
				v2 = topDynArr(args);
				popDynArr(args);
				v1 = topDynArr(args);
				popDynArr(args);
			} else {
				v1 = topDynArr(args);
				popDynArr(args);
			}
			pushDynArr(args, operate(op, v1, v2));

		} else {
			if(strcmp(argv[i], "pi") == 0)
				pushDynArr(args, M_PI);
			else if(strcmp(argv[i], "e") == 0)
				pushDynArr(args, M_E);
			else{
				pushDynArr(args, atof(argv[i]));
			}
		}
	}
	if(args->size != 1){
		printf("Invalid number of operators\n");
	} else {
		printf("Result: %f\n", topDynArr(args));
	}
	return 1;

}