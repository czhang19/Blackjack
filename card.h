#ifndef CARD_H
#define CARD_H
#include <unordered_map>
#include <string>

class Card {
public: 
	Card(int v, char s);
	Card(const Card& c);
	int getValue();
	int getPointValue();
	char getSuit();
	std::string print();
	
private:
	int value;
	int pointValue;
	char suit;
	std::unordered_map<int, std::string> cards;
};

#endif