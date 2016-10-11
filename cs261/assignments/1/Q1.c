/* CS261- Assignment 1 - Q.1*/
/* Name: Michael Phelps & Rahul Borkar
 * Date: 10/10/14, 4:20 PM
 * Solution description: Create an array of students and generate data for them
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
  /*Allocate memory for ten students*/
  struct student *temp = malloc(sizeof(struct student) * 10);
  /*return the pointer*/
  return temp;
}

void generate(struct student* students){
  /*Generate random ID and scores for 10 students, ID being between 1 and 10, scores between 0 and 100*/
  int i;
  for(i = 0; i < 10; i++){
    students[i].id = (rand() % 9 + 1);
    students[i].score = (rand() % 100);
  }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
  int i;
  for(i = 0; i < 10; i++){
    printf("%d %d \n", students[i].id, students[i].score);
  }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
  int min, max, current;
  float total;
  min = 100;
  max = 0;
  total = 0;
  int i;
  for(i = 0; i < 10; i++){
    current = students[i].score;
    if(min > current)
      min = current;
    if(max < current)
      max = current;
    total += current;
  }
  printf("Minimum: %d\nMaximum: %d\nAverage: %f\n", min, max, total/10);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
  free(stud);
}

int main(){
  struct student* stud = NULL;
    
    /*call allocate*/
  stud = allocate();
    /*call generate*/
  generate(stud);
    /*call output*/
  output(stud);
    /*call summary*/
  summary(stud);
    /*call deallocate*/
  deallocate(stud);
    return 0;
}
