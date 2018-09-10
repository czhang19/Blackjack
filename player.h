#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include <vector>

class Player {
public:
	Player(int x);
	
	int getTotalAmount();
	int getBet();
	Card* getCard(int x);
	
	void stand();
	void hit();
	void setBet(int x);
	void bet();
	void setCards(Card* c);
	void clearCards();
	
	
private:
	int totalAmount;
	int currentBet;
	std::vector<Card*> currentCards;
};

#endif