#ifndef CARD_SET
#define CARD_SET

class card_set{
private:
	bool cards[52];
	int size;
public:
	card_set();
	~card_set();

	void goFish(card_set &from, int count);
	void printCards();
	void removeCard(int index);
	void addCard(int index);
	int getSize();
	bool hasCard(int index);
	void fillDeck();
	bool hasNum(int num);
	bool hasSet(int size);
	bool hasStraight();
	bool hasFlush();

};

#endif

