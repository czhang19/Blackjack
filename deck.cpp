#include "deck.h"
#include <iostream>
using namespace std;

Deck::Deck(int x) {
	vector<char> suits = {'c','d','s','h'};
	for (int i = 1; i <= 13; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < x; k++) {
				availableCards.push_back(new Card(i, suits[j]));
			}	
		}
	}
	shuffle();
}

void Deck::shuffle() {
	cout << "The dealer is shuffling the deck.\n";
	vector<Card*> temp = availableCards;
	for (int i = 0; i < availableCards.size(); i++) {
		int x = rand()%(temp.size()-i);
		deck.push(temp[x]);
		temp.erase(temp.begin()+x);
	}
}

Card* Deck::draw() {
	if (empty()) shuffle();
	Card* temp = deck.front();
	deck.pop();
	return temp;
}

bool Deck::empty() {
	return deck.empty();
}