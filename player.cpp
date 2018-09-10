#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int x) {
	totalAmount = x;
}
	
int Player::getTotalAmount() {
	return totalAmount;
}

int Player::getBet() {
	return currentBet;
}

Card* Player::getCard(int x) {
	return currentCards[x];
}
	
void Player::setBet(int x) {
	currentBet = x;
}

void Player::setCards(Card* c) {
	currentCards.push_back(c);
}

void Player::clearCards() {
	currentCards.clear();
}
	
void Player::bet() {
	bool validBet = false;
	cout << "You have $" << totalAmount << ". How much do you bet? ($2-$500)\n";
	while (!validBet) {
		int x;
		cin >> x;
		if (x < 2 || x > 500) {
			cout << "Please make a bet between $2 and $500.\n";
		} else {
			validBet = true;
			currentBet = x;
		}
	}
}
	