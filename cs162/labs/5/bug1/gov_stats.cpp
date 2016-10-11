
#include "state.h"
#include <iostream>
using namespace std;

int main() {
   state s[50];
   int which_state;
   
   cout << "Which state do you want? (1-50)";
   cin >> which_state;

   s[which_state-1].set_pop(300000);
   s[which_state-1].set_name("oregon");

   s[which_state-1].display_pop();

   return 0;
}
