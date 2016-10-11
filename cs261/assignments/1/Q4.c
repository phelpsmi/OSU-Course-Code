/* CS261- Assignment 1 - Q.1*/
/* Name: Michael Phelps & Rahul Borkar
 * Date: 10/10/14, 4:20 PM
 * Solution description: Initializing and sorting an array of students
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
    int x, y, temp;
    for(x=0; x<n; x++){
        for(y=0; y<n-1; y++){
            if(students[y].score > students[y+1].score){
                temp = students[y].score;
                students[y].score = students[y+1].score;
                students[y+1].score = temp;

                temp = students[y].id;
                students[y].id = students[y+1].id;
                students[y+1].id = temp;
            }
        }
    }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 20;
    
    /*Allocate memory for n students using malloc.*/
    struct student* s = malloc(sizeof(struct student)*n);
    
    /*Generate random IDs and scores for the n students, using rand().*/
    int i;
    srand(time(NULL));
    for(i = 0; i < n; i++){
        s[i].id = rand() % 10 + 1;
        s[i].score = rand() % 101;
    }
    
    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; i++){
        printf("%d %d \n", s[i].id, s[i].score);
    }
    printf("\n");

    /*Pass this array along with n to the sort() function*/
    sort(s, n);
    
    /*Print the contents of the array of n students.*/
    for(i = 0; i < n; i++){
        printf("%d %d \n", s[i].id, s[i].score);
    }

    
    return 0;
}
