#ifndef RESOURCES
#define RESOURCES

#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int char_to_int(string card);
string int_to_char(int card);
string suit(int card);
bool validInt(string s);
int getInt();
string getCard();
char choose_game();
int choose_swap();
void pauseIt();

#endif