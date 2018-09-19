#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "deck.h"
#include <vector>

class Player {
public:
	Player(int x);
	
	int getTotalAmount(); //gets total amount of money player current has 
	int getBet(); //gets current bet on the table
	int getTotalPoints(); //gets current point total of players cards
	Card* getCard(int x); //gets card from player's hand with specified index x
	
	void bet(); //prompts player to make a bet
	void setBet(int x); //sets current bet
	void loseBet(); //player's total amount changes respectively to bet placed
	void winBet(); //player's total amount changes respectively to bet placed
	void changeTotalAmount(int x); //changes player's total amount by x
	void addCard(Card* c); //adds card to players cards
	void printAllCards(); //prints all of player's current cards
	void clearCards(); //removes all of player's current cards
	
	bool turnIsOver; //true if player's current turn is finished
private:
	int totalAmount; //total amount of money player current has 
	int currentBet;  //player's current bet on the table
	std::vector<Card*> currentCards; //player's current cards on the table
};

#endif