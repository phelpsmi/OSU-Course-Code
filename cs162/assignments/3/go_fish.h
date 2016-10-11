#ifndef GO_FISH
#define GO_FISH

#include "card_game.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

class go_fish: public card_game{
public:
	go_fish();
	~go_fish();
	bool runTurn(int player);
	void playSets(int player);
	bool queryPlayer(int cardNum, int taker, int giver);
	void finish(int player);
	void playGame();
};

#endif
