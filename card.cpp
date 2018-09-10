#include "card.h"
#include <iostream>
using namespace std;

Card::Card(int v, char s) {
	value = v;
	pointValue = (v == 11 || v == 12 || v == 13) ? 10 : v;
	suit = s;
	cards = {{1,"Ace"},{2,"Two"},{3,"Three"},{4,"Four"},{5,"Five"},{6,"Six"},{7,"Seven"},{8,"Eight"},{9,"Nine"},{10,"Ten"},{11,"Jack"},{12,"Queen"},{13,"King"}};
}

Card::Card(const Card& c) {
	Card(c.value, c.suit);
}

int Card::getValue() {
	return value;
}

int Card::getPointValue() {
	return pointValue;
}

char Card::getSuit() {
	return suit;
}

string Card::print() {
	string s = " " + cards[value] + " of ";
	if (suit == 'c') s += "Clubs";
	if (suit == 'd') s += "Diamonds";
	if (suit == 's') s += "Spades";
	if (suit == 'h') s += "Hearts";
	return s;
}