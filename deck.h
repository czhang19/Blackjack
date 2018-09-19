#ifndef DECK_H
#define DECK_H
#include <queue>
#include <vector>
#include "player.h"

class Deck {
public:
	Deck(int x); //constructor for deck of cards with x number of 52-card decks
	void shuffle(); //shuffles entire deck
	Card* draw(); //draws a card from the top of the deck
	bool empty(); //checks if deck is empty
	
private:
	std::queue<Card*> deck; //stores all cards currently in the deck
	std::vector<Card*> availableCards; //stores all possible cards in the deck
};

#endif