#include <stdio.h>
#include <string.h>

//Count the number of times the letter appears in the string
int count_letter(char str[], char ch) {
   int i, num = 0;
   
   for(i=0; i < strlen(str); i++)
      if(str[i] == ch)
         num++;

   return num;
}

//Get the sentence and character to search for from the user
char * get_info(char *ch) {
   char *str = malloc( sizeof(char)*100);
   char temp;
   int i=0;

   printf("Enter a sentence to seach: ");
   while((temp=getchar())!='\n')
      str[i++] = temp;
   str[i]='\0'; 
   printf("Enter a character to search for: ");
   *ch = getchar();

   return str;
}

//Get a sentence and character from the user and count the number
//of times the character is found in the sentence.
int main() {
   char *sentence, ch;
   int num_letters;

   sentence = get_info(&ch);
   num_letters = count_letter(sentence, ch);

   printf("%c is found %d times.\n", ch, num_letters);
   
   return 0;
}