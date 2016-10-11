#include <iostream>

#define PROMPT "Please enter a whole number: "
#define NOT_PRIME "The number is not a prime number. "
#define PRIME "The number is a prime number. "        
#define DONE 0          /* ends successful program */                           
#define FIRST_FACTOR 2  /* initial value in for loop */                         

using std::cout;
using std::cin;
using std::endl;

int main(){
    int i, number;       /* loop counter */ /* number provided by user */

    cout << PROMPT;  /* promt user */
    cin >> number;  /* wait for user input */

    /* Prime numbers are defined as any number 
     * greater than one that is only divisible
     * by one and itself. Dividing the number
     * by two shortens the time it takes to
     * complete. */

    for(i = FIRST_FACTOR; i <= number/2; ++i)
       if( number%i == 0 ){    /* if divisible */
          cout << NOT_PRIME << number << endl; /* not prime */
          return DONE;        /* exit program */
       }
    
    /* if number is not divisible by anything
     * than it must be prime */
    cout << PRIME << number << endl;
    return 0;     /* exit program */
}