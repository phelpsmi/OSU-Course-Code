#include <iostream>

#include "resources.h"

using namespace std;

int char_to_int(string card){
	if (card == "K" || card == "k")
		return 0;
	if (card == "Q" || card == "q")
		return 12;
	if (card == "J" || card == "j")
		return 11;
	if (card == "A" || card == "a")
		return 1;
	if (card == "10")
		return 10;
	return atoi(card.c_str());
}

string int_to_char(int card){
	int num = card % 13;
	if (num == 0)
		return " K";
	if (num == 1)
		return " A";
	if (num == 11)
		return " J";
	if (num == 12)
		return " Q";
	if (num == 10)
		return "10";
	string sCard = " ";
	char dig = (char)(48+num);
	sCard += dig;
	return sCard;
}

string suit(int card){
	int suit = card / 13;
	if (suit == 0)
		return "H ";
	if (suit == 1)
		return "D ";
	if (suit == 2)
		return "C ";
	if (suit == 3)
		return "S ";
	return "Z";
}

/*********************************************************************
** Function: validInt
** Description: returns true if the string can be converted to an int
** Parameters: string s
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
bool validInt(string s){
	for (int x = 0; x < (int)s.size(); ++x){
		if (!isdigit(s.at(x))){
			if (!(x == 0) && !s.at(x) == '-')
				return false;
		}
	}
	return true;
}

int getInt(){
	string s;
	cin >> s;
	while(!validInt(s)){
		cout << "Please input a valid integer: ";
		cin >> s;
	}
	return atoi(s.c_str());
}

string getCard(){
	string c;
	cin >> c;
	if(c == "2" || c == "3" || c == "4" || c == "5" || c == "6" || c == "7" || c == "8")
		return c;
	if(c == "9" || c == "10" || c == "A" || c == "J" || c == "Q" || c == "K" || c == "a")
		return c;
	if(c == "j" || c == "q" || c == "k")
		return c;
	cout << "Please enter a valid card: ";
	return getCard();
}