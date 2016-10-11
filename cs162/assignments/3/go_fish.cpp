#include "go_fish.h"
#include "resources.h"

go_fish::go_fish(){
	
}

/********************************************************************* 
 ** Function: game#runTurn
 ** Description: plays out a single turn
 ** Parameters: int player
 ** Pre-Conditions: game is initialized
 ** Post-Conditions: none
 *********************************************************************/
bool go_fish::runTurn(int player){
	int pOut = player + 1, pTarget = -1;
	string query;

	cout << "deck size: " << deck.getSize() << endl << endl;
	for (int i = 0; i < pCount; ++i){
		cout << "Player " << i+1 << ": " << hand[i].getSize() << endl;
		hand[i].printCards();
	}
	

	while(pTarget < 0 || pTarget >= pCount || pTarget == player){
	cout << "Player " << pOut << ", which player would you like to ask? ";
	pTarget = getInt();
	pTarget--;
	}

	cout << "Which card would you like to ask for? ";
	query = getCard();

	system("clear");

	if (!queryPlayer(char_to_int(query), player, pTarget)){
		cout << "Go Fish!!!" << endl;
		hand[player].goFish(deck, 1);
	}
	playSets(player);
	return (hand[player].getSize() == 0);

}

/********************************************************************* 
 ** Function: game#queryPlayer
 ** Description: plays out events of asking player for a card number
 ** Parameters: int cardNum, int taker, int giver
 ** Pre-Conditions: taker/giver are ints refering to initialized player
 ** Post-Conditions: none
 *********************************************************************/
bool go_fish::queryPlayer(int cardNum, int taker, int giver){
	bool hadCard = false;
	for (int x = 0; x < 4; ++x){
		int index = (x * 13) + cardNum;
		if (hand[giver].hasCard(cardNum + (x * 13))){
			hand[taker].addCard(index);
			hand[giver].removeCard(index);
			hand[giver].goFish(deck, 1);
			cout << "SUCCESS!!!" << endl;
			hadCard = true;
		}
	}
	return hadCard;
}

/********************************************************************* 
 ** Function: game#playSets
 ** Description: gets rid of all full card sets in a player's hand
 ** Parameters: int player
 ** Pre-Conditions: player refers to an initialized player
 ** Post-Conditions: all sets of 4 cards numbers are gone from hand
 *********************************************************************/
void go_fish::playSets(int player){
	bool hasSet;
	for (int x = 0; x < 13; ++x){
		hasSet = true;
		for (int y = 0; y < 4; ++y){
			if (!hand[player].hasCard(x + (13 * y))){
				hasSet = false;
			}
		}
		if (hasSet){
			for (int y = 0; y < 4; ++y){
				hand[player].removeCard(x + (13 * y));
			}
		}
	}
}

/********************************************************************* 
 ** Function: game#playGame
 ** Description: plays out the entire game
 ** Parameters: none
 ** Pre-Conditions: game is initialized
 ** Post-Conditions: game is finished
 *********************************************************************/
void go_fish::playGame(){
	int player = 0;
	while (!runTurn(player)){
		player++;
		if (player == pCount)
			player = 0;
	}
	finish(player);
	cout << "Finishing game now" << endl;
	return;
}

/********************************************************************* 
 ** Function: game#finish
 ** Description: prints out the message declaying the winner of the game
 ** Parameters: int player
 ** Pre-Conditions: none
 ** Post-Conditions: none
 *********************************************************************/
void go_fish::finish(int player){
	cout << "Player " << player+1 << " Wins!!" << endl;
	cout << "Congratulations" << endl;
}
