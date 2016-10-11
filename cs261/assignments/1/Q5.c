/* CS261- Assignment 1 - Q.1*/
/* Name: Michael Phelps & Rahul Borkar
 * Date: 10/10/14, 4:20 PM
 * Solution description: Changing word to studly case
 */
 
#include <stdio.h>
#include <stdlib.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void studly(char* word){
     /*Convert to studly caps*/
	int i;
	for(i = 0; word[i] != '\0'; i++){
		if(i % 2 == 0)
			word[i] = toupper(word[i]);
		else
			word[i] = tolower(word[i]);
	}

}

int main(){
    /*Read word from the keyboard using scanf*/
    char *str = malloc(sizeof(char)*50);
    printf ("Enter a word: ");
    scanf ("%49s", str);
    
    /*Call studly*/
    studly(str);
    
    /*Print the new word*/
    printf("%s\n", str);
    
    return 0;
}
