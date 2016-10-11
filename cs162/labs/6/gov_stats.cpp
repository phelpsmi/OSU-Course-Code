#include "nation.h"
#include <iostream>
using namespace std;

int main() {
  nation* n;
  char select;

  cout << "Would you like to see the population stats for the nation, a state, or a city?" << endl;
  cout << "Enter n - nation, s - state, c - city: ";

  cin >> select;

  if(select == 'n'){
    n = new nation;
    n->set_pop(316395932);
  }
  else if(select == 's'){
    n = new state;
    n->set_name("Oregon");
    n->set_pop(3930065);
  }
  else if(select == 'c'){
    n = new city;
    n->set_name("Corvallis", "Oregon");
    n->set_pop(54998);
  }

  n->display_pop();

}
