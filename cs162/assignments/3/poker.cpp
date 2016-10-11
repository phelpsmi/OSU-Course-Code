#include <iostream>

#include "poker.h"
#include "resources.h"

using namespace std;

poker::poker(){
	score = new int[pCount];
	for(int x = 0; x < pCount; x++)
		score[x] = 0;
	rounds = 0;
	while(rounds < 1){
		cout << "Enter number of rounds: ";
		rounds = getInt();
	}
}

poker::~poker(){
	delete [] score;
}

/********************************************************************* 
 ** Function: poker#runTurn
 ** Description: plays through a single turn for one player
 ** Parameters: int player
 ** Pre-Conditions: player has a hand
 ** Post-Conditions: none
 *********************************************************************/
bool poker::runTurn(int player){
	int replace;

	system("clear");

	hand[player].printCards();
	cout << "Player " << player+1 << ", how many cards would you like to replace: ";
	replace = getInt();
	while(hand[player].getSize() > (5 - replace)){
		hand[player].removeCard(choose_swap());
		hand[player].printCards();
	}
	hand[player].goFish(deck, replace);
	hand[player].printCards();
	setScore(player);
}

/********************************************************************* 
 ** Function: poker#deal
 ** Description: deals a new hand to alll players
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: all players have 5 cards
 *********************************************************************/
void poker::deal(){
	deck.fillDeck();
	hand = new card_set[pCount];
	for (int i = 0; i < pCount; ++i){
		hand[i].goFish(deck, 5);
	}
}

/********************************************************************* 
 ** Function: poker#playGame
 ** Description: plays out a full game
 ** Parameters: rounds is set
 ** Pre-Conditions: 
 ** Post-Conditions: 
 *********************************************************************/
void poker::playGame(){
	for (int i = 0; i < rounds; ++i){
		deal();
		for(int x = 0; x < pCount; ++x){
			runTurn(x);
		}
		system("clear");
		printScores(i);
	}
	findWinner();
}

/********************************************************************* 
 ** Function: poker#setScore
 ** Description: determines the player's score for current hand
 ** Parameters: int player
 ** Pre-Conditions: player has a hand and score is initialized
 ** Post-Conditions: none
 *********************************************************************/
void poker::setScore(int player){
	cout << "Player " << player + 1 << ", got ";
	if(hand[player].hasFlush() && hand[player].hasStraight()){
		cout << "a straight flush. +50 points" << endl;
		score[player] += 50;
	} else if(hand[player].hasSet(4)){
		cout << "a four of a kind. +30 points" << endl;
		score[player] += 30;
	} else if(hand[player].hasSet(3) && hand[player].hasSet(2)){
		cout << "a full house. +25 points" << endl;
		score[player] += 25;
	} else if(hand[player].hasFlush()){
		cout << "a flush. +20 points" << endl;
		score[player] += 20;
	} else if(hand[player].hasStraight()){
		cout << "a straight. +15 points" << endl;
		score[player] += 15;
	} else if(hand[player].hasSet(3)){
		cout << "three of a kind. +10 points" << endl;
		score[player] += 10;
	} else {
		cout << "nothing. no points :(" << endl;
	}
	pauseIt();

}

/********************************************************************* 
 ** Function: poker#printScores
 ** Description: print the scores and round for all players
 ** Parameters: int r
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void poker::printScores(int r){
	cout << "Round " << r+1 << " scores:" << endl;
	for(int x = 0; x < pCount; ++x){
		cout << "   Player " << x+1 << ": " << score[x] << endl;
	}
	pauseIt();
}

/********************************************************************* 
 ** Function: poker#findWinner
 ** Description: determines who is the winner and announces it
 ** Parameters: none
 ** Pre-Conditions: scores have been intialized
 ** Post-Conditions: none 
 *********************************************************************/
int poker::findWinner(){
	
	int winScore = 0, winCount = 0;
	for(int x = 0; x < pCount; ++x){
		if(score[x] > winScore)
			winScore = score[x];
	}
	cout << "Player ";
	for(int x = 0; x < pCount; ++x){
		if(score[x] == winScore)
			cout << x+1 << ", ";
	}
	cout << "WIN with " << winScore << " points." << endl;
}