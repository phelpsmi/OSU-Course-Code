#ifndef CARD_GAME
#define CARD_GAME

#include "card_set.h"

class card_game{
protected:
	int pCount;
	card_set deck;
	card_set* hand;
public:
	card_game();
	~card_game();
	void finish(int player);
	virtual void playGame(){}
};

#endif
