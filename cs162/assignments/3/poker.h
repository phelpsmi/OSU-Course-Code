#ifndef POKER
#define POKER

#include "card_game.h"

class poker: public card_game{
private:
	int* score;
	int rounds;
public:
	poker();
	~poker();
	bool runTurn(int player);
	void playGame();
	int findWinner();
	void deal();
	void setScore(int player);
	void printScores(int);
};

#endif
