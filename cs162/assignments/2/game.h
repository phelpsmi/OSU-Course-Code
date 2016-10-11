#include "cardSet.h"

class game{
private:
	int pCount;
	cardSet deck;
	cardSet* hand;
public:
	game();
	~game();
	bool runTurn(int player);
	void playSets(int player);
	bool queryPlayer(int cardNum, int taker, int giver);
	void finish(int player);
	void playGame();
};

