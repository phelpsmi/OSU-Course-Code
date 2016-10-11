/********************************************************************* 
 ** Program Filename: cardSet.cpp
 ** Author: Michael Phelps
 ** Date: 4/25/2014
 ** Description: A set of cards which functions as player hands or the deck
 ** Input: none
 ** Output: prints all cards in hand
 *********************************************************************/ 
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "cardSet.h"
#include "resources.h"

using namespace std;

/********************************************************************* 
 ** Function: cardSet#cardSet
 ** Description: initializes the cardSet
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: cardset is initialized with values
 *********************************************************************/
cardSet::cardSet(){
	bool cards[52] = { false };
	size = 0;
}

void cardSet::goFish(cardSet &from, int count = 1){
	if( from.getSize() == 0)
		return;
	for (int x = 0; x < count; x++){
		int i = (rand() % 52);
		if (from.hasCard(i)){
			addCard(i);
			from.removeCard(i);
		}
		else{
			goFish(from);
		}
	}

}

/********************************************************************* 
 ** Function: cardSet#printCards
 ** Description: prints out all the cards in the set
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void cardSet::printCards(){
	for (int x = 0; x < size; ++x)
		cout << "**** ";

	cout << endl;
	for (int x = 0; x < 13; x++){
		for(int y = 0; y < 40; y=y+13){
			if (cards[x+y])
				cout << "*" << int_to_char(x+y) << "* ";
		}
	}

	cout << endl;
	for (int x = 0; x < 13; x++){
		for(int y = 0; y < 40; y=y+13){
			if (cards[x+y])
				cout << "*" << suit(x+y) << "* ";
		}
	}

	cout << endl;
	for (int x = 0; x < size; ++x)
		cout << "**** ";
	cout << endl;
}

/********************************************************************* 
 ** Function: cardSet#removeCard
 ** Description: removes card from set
 ** Parameters: int index
 ** Pre-Conditions: index range is 0-51
 ** Post-Conditions: none
 *********************************************************************/
void cardSet::removeCard(int index){
	cards[index] = false;
	size--;
}

/********************************************************************* 
 ** Function: cardSet#addCard
 ** Description: adds a card to the set
 ** Parameters: int index
 ** Pre-Conditions: index range is 0-51
 ** Post-Conditions: none
 *********************************************************************/
void cardSet::addCard(int index){
	cards[index] = true;
	size++;
}

/********************************************************************* 
 ** Function: cardSet#getSize
 ** Description: returns size of set
 ** Parameters: none
 ** Pre-Conditions: size is initialized
 ** Post-Conditions: none
 *********************************************************************/
int cardSet::getSize(){
	return size;
}

/********************************************************************* 
 ** Function: cardSet#hasCard
 ** Description: returns whether or not set has specified card
 ** Parameters: int index
 ** Pre-Conditions: index range is 0-52
 ** Post-Conditions: none
 *********************************************************************/
bool cardSet::hasCard(int index){
	return cards[index];
}

/********************************************************************* 
 ** Function: cardSet#filDeck
 ** Description: fills the set with all true
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void cardSet::fillDeck(){
	for (int x = 0; x < 52; x++){
		cards[x] = true;
	}
	size = 52;
}

cardSet::~cardSet(){
}
