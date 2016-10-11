/* CS261- Assignment 1 - Q.1*/
/* Name: Michael Phelps & Rahul Borkar
 * Date: 10/10/14, 4:20 PM
 * Solution description: Passing variables by reference or value
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a *= 2;
    printf("%d\n", *a);
    /*Set b to half its original value*/
    *b /= 2;
    printf("%d\n", *b);
    /*Assign a+b to c*/
    c = *a + *b;
    printf("%d\n", c);
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 7, 8, 9 respectively*/
    int x = 7, y = 8, z = 9, q;
    /*Print the values of x, y and z*/
    printf("x: %d\ny: %d\nz: %d\n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    q = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("%d\n", q);
    /*Print the values of x, y and z again*/
    printf("x: %d\ny: %d\nz: %d\n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/
    return 0;
}
    
    
