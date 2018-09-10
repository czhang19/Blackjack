#ifndef DECK_H
#define DECK_H
#include <queue>
#include <vector>
#include "player.h"

class Deck {
public:
	Deck(int x);
	void shuffle();
	Card* draw();
	bool empty();
	
private:
	std::queue<Card*> deck;
	std::vector<Card*> availableCards;
};

#endif