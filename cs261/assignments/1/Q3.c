/* CS261- Assignment 1 - Q.1*/
/* Name: Michael Phelps & Rahul Borkar
 * Date: 10/10/14, 4:20 PM
 * Solution description: Sorting an array of integers
 */
 
#include <stdio.h>
#include <stdlib.h>

void sort(int* number, int n){
    /*Sort the given array number , of length n*/
    int x, y, temp;
    for(x=0; x<n; x++){
    	for(y=0; y<n-1; y++){
    		if(number[y] > number[y+1]){
    			temp = number[y];
    			number[y] = number[y+1];
    			number[y+1] = temp;
    		}
    	}
    }

}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int* number = malloc(sizeof(int)*n);
    
    /*Fill this array with random numbers between 0 and n, using rand().*/
    srand(time(NULL));
    int i;
    for(i = 0; i<n; i++){
    	number[i] = rand()%n;
    }
    
    /*Print the contents of the array.*/
    for(i=0; i<n; i++){
    	printf("%d ", number[i]);
    }
    printf(" \n");

    /*Pass this array along with n to the sort() function.*/
    sort(number, n);
    
    /*Print the contents of the array.*/    
    for(i=0; i<n; i++){
    	printf("%d ", number[i]);
    }
    printf("\n");
    
    return 0;
}
