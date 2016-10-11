#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
  char cmd = ' ';
  char file[128], desc[TASK_DESC_SIZE];
  int priority;
  FILE *fp;
  DynArr* mainList;
  mainList = createDynArr(10);
  TaskP task, firstTask;

  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do {
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n"
             );
      /* get input command (from the keyboard) */
      cmd = getchar();
      /* clear the trailing newline character */
      while (getchar() != '\n');
      switch(cmd){
        case 'l':
          printf("Enter filename: ");
          scanf("%s", file);
          fp = fopen(file, "r");
          loadList(mainList, fp);
          break;
        case 's':
          printf("Enter filename: ");
          scanf("%s", file);
          fp = fopen(file, "w");
          saveList(mainList, fp);
          fclose(fp);
          break;
        case 'a':
          printf("Enter task description: ");
          scanf("%s", desc);

          printf("Enter priority: ");
          scanf("%d", &priority);
          task = createTask(priority, desc);
          addHeap(mainList, task, compare);

          break;
        case 'g':
          if(sizeDynArr(mainList) > 0){
            firstTask = getMinHeap(mainList);
            printf("Your first task is: %s\n\n", firstTask->description);
          }
          else
            printf("Your to-do list is empty! You need to add something to it first!\n\n");
          break;
        case 'r':
          if(sizeDynArr(mainList) > 0){
            firstTask = getMinHeap(mainList);
            removeMinHeap(mainList, compare);
            printf("Your first task '%s' has been removed from your to-do list.\n\n", firstTask->description);
            free(firstTask);
          }
          else
            printf("Your to-do list is empty! You need to add something to it first!\n\n");
          break;
        case 'p':
          printList(mainList);
          break;
        case 'e':
          printf("LATA!\n\n");
          break;
        default:
          printf("You didn't input something valid!!!!\n");
          break;
      }

      /* Fixme:  Your logic goes here! */

      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    } while(cmd != 'e');
  /* delete the list */
  deleteDynArr(mainList);

  return 0;
}
