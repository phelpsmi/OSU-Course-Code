/********************************************************************* 
 ** Program Filename: game.cpp
 ** Author: Michael Phelps
 ** Date: 4/25/2014
 ** Description: holds information for and plays out a game of go fish
 ** Input: player count, card request
 ** Output: turn information
 *********************************************************************/ 
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "card_game.h"
#include "resources.h"


using namespace std;

/********************************************************************* 
 ** Function: game
 ** Description: constructs a game
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: all game variables are initialized
 *********************************************************************/ 
card_game::card_game(){
	pCount = 0;
	while(pCount < 2 || pCount > 6){
		cout << "Enter number of players: ";
		pCount = getInt();
	}

	hand = new card_set[pCount];

	deck.fillDeck();
	srand(time(NULL));

	for (int x = 0; x < pCount; ++x){
		hand[x].goFish(deck, 7);
	}
}

card_game::~card_game(){
	delete [] hand;
}
