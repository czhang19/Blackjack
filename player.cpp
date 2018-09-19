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

int Player::getTotalPoints() {
	int sum = 0;
	int aces = 0;
	for (int i = 0; i < currentCards.size(); i++) {
		if (currentCards[i]->getPointValue() == 1) {
			aces++;
			sum += 11;
		} else {
			sum += currentCards[i]->getPointValue();
		}
		while (sum > 21 && aces > 0) {
			sum -= 10;
			aces--;
		}
	}
	return sum;
}

Card* Player::getCard(int x) {
	return currentCards[x];
}

void Player::setBet(int x) {
	currentBet = x;
}

void Player::loseBet() {
	totalAmount -= currentBet;
}

void Player::winBet() {
	totalAmount += currentBet;
}

void Player::changeTotalAmount(int x) {
	totalAmount += x;
}

void Player::addCard(Card* c) {
	currentCards.push_back(c);
}

void Player::printAllCards() {
	for (int i = 0; i < currentCards.size(); i++) {
		if (i != 0) cout << ",";
		cout << currentCards[i]->print();
	}
	cout << endl;
}

void Player::clearCards() {
	currentCards.clear();
}
	
void Player::bet() {
	bool validBet = false;
	turnIsOver = false;
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
	