#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "deck.h"
#include <vector>

class Player {
public:
	Player(int x);
	
	int getTotalAmount();
	int getBet();
	int getTotalPoints();
	Card* getCard(int x);
	
	void bet();
	void setBet(int x);
	void loseBet();
	void winBet();
	void changeTotalAmount(int x); //changes player's total amount by x
	void addCard(Card* c);
	void printAllCards();
	void clearCards();
	
	bool turnIsOver;
private:
	int totalAmount;
	int currentBet;
	std::vector<Card*> currentCards;
};

#endif