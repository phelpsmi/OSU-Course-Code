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

#include "card_set.h"
#include "resources.h"

using namespace std;

/********************************************************************* 
 ** Function: cardSet#cardSet
 ** Description: initializes the cardSet
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: cardset is initialized with values
 *********************************************************************/
card_set::card_set(){
	bool cards[52] = { false };
	size = 0;
}

void card_set::goFish(card_set &from, int count = 1){
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
void card_set::printCards(){
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
void card_set::removeCard(int index){
	if(cards[index]){
		cards[index] = false;
		size--;
	}
}

/********************************************************************* 
 ** Function: cardSet#addCard
 ** Description: adds a card to the set
 ** Parameters: int index
 ** Pre-Conditions: index range is 0-51
 ** Post-Conditions: none
 *********************************************************************/
void card_set::addCard(int index){
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
int card_set::getSize(){
	return size;
}

/********************************************************************* 
 ** Function: cardSet#hasCard
 ** Description: returns whether or not set has specified card
 ** Parameters: int index
 ** Pre-Conditions: index range is 0-52
 ** Post-Conditions: none
 *********************************************************************/
bool card_set::hasCard(int index){
	return cards[index];
}

/********************************************************************* 
 ** Function: cardSet#filDeck
 ** Description: fills the set with all true
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void card_set::fillDeck(){
	for (int x = 0; x < 52; x++){
		cards[x] = true;
	}
	size = 52;
}

/********************************************************************* 
 ** Function: cardSet#
 ** Description: 
 ** Parameters: 
 ** Pre-Conditions: 
 ** Post-Conditions: 
 *********************************************************************/
bool card_set::hasNum(int num){
	for(int x = 0; x < 40; x += 13){
		if(cards[num+x])
			return true;
	}
	return false;
}

/********************************************************************* 
 ** Function: cardSet#hasSet
 ** Description: determines if the hand has a pair of a certain size
 ** Parameters: int size
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
bool card_set::hasSet(int size){
	int count;
	for(int x = 0; x < 13; x++){
		count = 0;
		for(int y = 0; y < 40; y += 13){
			if(cards[x+y])
				count++;
		}
		if(count == size)
			return true;
	}
	return false;
}

/********************************************************************* 
 ** Function: cardSet#hasStraight
 ** Description: determines if the hand has a straight
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
bool card_set::hasStraight(){
	for(int x = 0; x < 13; x++){
		if (hasNum(x)){
			if(hasNum(x+1) && hasNum(x+2) && hasNum(x+3) && hasNum(x+4)){
				return true;
			}
			return false;
		}
	}
	return false;
}

/********************************************************************* 
 ** Function: cardSet#hasFlush
 ** Description: determines if hand contains a flush
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
bool card_set::hasFlush(){
	int count = 0;
	for(int x = 0; x < 40; x += 13){
		count = 0;
		for(int y = 0; y < 13; y++){
			if(cards[x+y])
				count++;
		}
		if(count >= 5){
			return true;
		} else if(count != 0){
			return false;
		}
	}
	return false;

}

card_set::~card_set(){
	delete [] cards;
}
