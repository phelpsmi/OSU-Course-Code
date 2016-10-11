class cardSet{
private:
	bool cards[52];
	int size;
public:
	cardSet();
	~cardSet();

	void goFish(cardSet &from, int count);
	void printCards();
	void removeCard(int index);
	void addCard(int index);
	int getSize();
	bool hasCard(int index);
	void fillDeck();
};


