#include "nation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

string getlinebetter(string filename, int);

int main() {

  string filename;

  cout << "What is the name of your file" << endl;
  cin >> filename;

  try {
    fstream fs;
    fs.exceptions(ifstream::failbit);
    fs.open (filename.c_str(), fstream::in | fstream::out | fstream::app);
    string test;
    getline(fs, test);
    fs.close();
  }
  catch(ifstream::failure e){
    cout << "the open for the filename provided wasn't successful!!!" << endl;
    return 0;
  }


  nation* n;
  char select;

  cout << "Would you like to see the population stats for the nation, a state, or a city?" << endl;
  cout << "Enter n - nation, s - state, c - city: ";

  cin >> select;

  if(select == 'n'){
    n = new nation;
    n->set_pop(atoi(getlinebetter(filename,2).c_str()));
  }
  else if(select == 's'){
    n = new state;
    n->set_name(getlinebetter(filename,3).c_str());
    n->set_pop(atoi(getlinebetter(filename,4).c_str()));
  }
  else if(select == 'c'){
    n = new city;
    n->set_name(getlinebetter(filename,5).c_str(), getlinebetter(filename,3).c_str());
    n->set_pop(atoi(getlinebetter(filename,6).c_str()));
  }

  n->display_pop();

}

string getlinebetter(string filename, int x){
  fstream fs;
  fs.open (filename.c_str(), fstream::in | fstream::out | fstream::app);
  string s;
  for (int i = 0; i<x; ++i){
    getline(fs, s);
  }
  fs.close();
  cout << s << endl;
  return s;
}