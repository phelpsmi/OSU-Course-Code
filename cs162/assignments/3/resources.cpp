#include <iostream>
#include <limits>
#include <stdio.h>

#include "resources.h"

using namespace std;

/*********************************************************************
** Function: char_to_int
** Description: converts character to integer
** Parameters: string card
** Pre-Conditions: card is a valid int
** Post-Conditions: none
*********************************************************************/
int char_to_int(string card){
	if (card == "K" || card == "k")
		return 12;
	if (card == "Q" || card == "q")
		return 11;
	if (card == "J" || card == "j")
		return 10;
	if (card == "A" || card == "a")
		return 0;
	if (card == "10")
		return 9;
	return atoi(card.c_str())-1;
}

/*********************************************************************
** Function: int_to_char
** Description: converts integer to displayable string
** Parameters: int card
** Pre-Conditions: card is 1-13
** Post-Conditions: none
*********************************************************************/
string int_to_char(int card){
	int num = card % 13;
	if (num == 12)
		return " K";
	if (num == 0)
		return " A";
	if (num == 10)
		return " J";
	if (num == 11)
		return " Q";
	if (num == 9)
		return "10";
	string sCard = " ";
	char dig = (char)(49+num);
	sCard += dig;
	return sCard;
}

/*********************************************************************
** Function: suit
** Description: gets suit of card
** Parameters: int card
** Pre-Conditions: card is less than 52
** Post-Conditions: none
*********************************************************************/
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

/*********************************************************************
** Function: getInt
** Description: gets an int for the user
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
int getInt(){
	string s;
	cin >> s;
	while(!validInt(s)){
		cout << "Please input a valid integer: ";
		cin >> s;
	}
	return atoi(s.c_str());
}

/*********************************************************************
** Function: getCard
** Description: asks user for a card number
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: card is valid
*********************************************************************/
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

/*********************************************************************
** Function: chooses the game type
** Description: queries player for which game to play
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: return p or g
*********************************************************************/
char choose_game(){
	string choice;
	cout << "Pick a game to play (p - poker, g - go fish): ";
	cin >> choice;

	if(choice == "p")
		return 'p';
	else if(choice == "g")
		return 'g';
	return choose_game();
}

/*********************************************************************
** Function: choose_swap
** Description: chooses an exact card to swap
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
int choose_swap(){
	string c, suit;
	int space, card = 0;

	cout << "Pick a card to swap ie (8 C): ";
	cin >> c >> suit;
	cout << c << suit << endl;

	if(suit == "H" || suit == "h")
		card = 0;
	else if(suit == "D" || suit == "d")
		card += 13;
	else if(suit == "C" || suit == "c")
		card += 26;
	else if(suit == "S" || suit == "s")
		card += 39;
	else
		return choose_swap();
	card += char_to_int(c);
	return card;

}

/*********************************************************************
** Function: pauseIt
** Description: asks player to press enter to continue
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/
void pauseIt(){
	cout << "press ENTER to continues";
	string temp;
	cin.ignore();
	temp = cin.get();
}