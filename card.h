#ifndef CARD_H
#define CARD_H
#include <unordered_map>
#include <string>

class Card {
public: 
	Card(int v, char s); //card is initialized with value and suit
	Card(const Card& c); //copy constructor
	int getValue(); //returns card's value
	int getPointValue(); //returns card's point value (J/Q/K is 10)
	char getSuit(); //returns card's suit
	std::string print(); //returns Card's written representation
	
private:
	int value; 
	int pointValue;
	char suit;
	std::unordered_map<int, std::string> cards;
};

#endif