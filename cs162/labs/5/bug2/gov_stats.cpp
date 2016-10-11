#include "nation.h"
#include "state.h"
#include <iostream>
using namespace std;

int main() {
   int which_state;
   state s[50];
   
   cout << "Which state do you want to set the pop? (1-50):";
   cin >> which_state;
   s[which_state-1].set_pop(300000);
   s[which_state-1].set_name("Oregon");

   s[which_state-1].display_pop();

   return 0;
}