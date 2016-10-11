#include "nation.h"
#include "state.h"
#include <iostream>
using namespace std;

int main() {
   nation n;
   char name[100];
   state s;

   for(int i=0; i<5; i++) {
	   cout << "Enter the state name: ";
       cin.getline(name,100);
       s.set_name(name);
       n.set_state(s,i);
   }

   for(int i=0; i<5; i++)
       n.getstate(i).display_name();

   return 0;
}
