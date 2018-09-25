/*
terminal (console-based) game: Blackjack
Cynthia Zhang 9/05/2018
*/

#include <iostream>
#include "card.h"
#include "deck.h"
#include "player.h"
using namespace std;


int getPlayers() {
	bool valid = false;
	char choice;
	int players;
	cout << "Would you like to play single player(s) or multiplayer(m)? ";
	while (!valid) {
		cin >> choice;
		switch(choice) {
			case('s'): return 1;
			case('m'): valid = true;
				break;
			default: cout << "Please enter 's' for single player or 'm' for multiplayer.\n";
		}
	}
	valid = false;
	cout << "How many players do you have? (2-5) ";
	while (!valid) {
		cin >> players;
		if (players > 5 || players < 2) {
			cout << "Please enter either 2, 3, 4 or 5.\n";
		} else {
			valid = true;
		}
	}
	return players;
}

void startGame() {
	int initialAmount = 1000, numberOfPlayers; //total amount of money player starts with
	cout << "Let's play Blackjack! ";
	numberOfPlayers = getPlayers();
	cout << "Players start with $" << initialAmount << ".\n";
	vector<Player*> players; //dealer is the last player in this vector
	for (int i = 0; i < numberOfPlayers+1; i++) {
		players.push_back(new Player(initialAmount));
	}
	
	srand(time(NULL)); //randomizes shuffling of cards
	Deck d = Deck(1); //one deck of cards
	bool keepPlaying = true; 
	while (keepPlaying) { //simulates every turn
		for (int i = 0; i < numberOfPlayers; i++) { //each player makes a bet
			cout << "Player " << i+1 << ". ";
			players[i]->bet();
		}
		for (int j = 0; j < 2; j++) { //dealer and each player is dealt two cards
			for (int i = 0; i < numberOfPlayers+1; i++) {
				if (j == 0) players[i]->clearCards();
				players[i]->addCard(d.draw());
			}
		}
		for (int i = 0; i < numberOfPlayers; i++) { //all players' cards are displayed
			cout << "Player " << i+1 << "'s cards are the" << players[i]->getCard(0)->print() << " and the" << players[i]->getCard(1)->print() << "." << endl;
		}
		cout << "The dealer's cards are the" << players[numberOfPlayers]->getCard(0)->print() << " and a face down card.\n"; 
		
		if (players[numberOfPlayers]->getTotalPoints() == 21) { //if dealer has a blackjack
			cout << "The dealer has a blackjack. The dealer's cards are the" << players[numberOfPlayers]->getCard(0)->print() << " and " << players[numberOfPlayers]->getCard(1)->print() << endl; 
			for (int i = 0; i < numberOfPlayers; i++) {
				if (players[i]->getTotalPoints() != 21) players[i]->loseBet();
			}
		} else {
			bool stand;
			bool originalCards;
			for (int i = 0; i < numberOfPlayers; i++) { //each player has their turn
				int totalPoints = players[i]->getTotalPoints();
				if (totalPoints == 21) {
					cout << "Player " << i+1 << " has a blackjack.\n";
					players[i]->changeTotalAmount(1.5*players[i]->getBet());
					players[i]->turnIsOver = true;
					continue;
				}
				char play;
				stand = false;
				originalCards = true;
				while (!stand) {
					totalPoints = players[i]->getTotalPoints();
					if (originalCards && (totalPoints == 9 || totalPoints == 10 || totalPoints == 11)) {
						cout << "Player " << i+1 << ", do you stand(s), hit(h) or double down(d)? ";
					} else {
						cout << "Player " << i+1 << ", do you stand(s) or hit(h)? ";
					}
					cin >> play;
					if (play == 's') { //if player stands
						stand = true;
					}
					if (play == 'h') { //if player hits
						players[i]->addCard(d.draw());
						totalPoints = players[i]->getTotalPoints();
						cout << "Your cards are:";
						players[i]->printAllCards();
						if (totalPoints > 21) {
							players[i]->loseBet();
							stand = true;
							players[i]->turnIsOver = true;
						}
					}
					if (play == 'd') { //if player doubles down
						players[i]->addCard(d.draw());
						players[i]->setBet(players[i]->getBet()*2);
						stand = true;
					}
					originalCards = false;
				}
			}
			
			//dealer's play
			cout << "The dealer's cards are:";
			players[numberOfPlayers]->printAllCards();
			stand = false;
			while (!stand) {
				if (players[numberOfPlayers]->getTotalPoints() >= 17) {
					stand = true;
				} else {
					players[numberOfPlayers]->addCard(d.draw());
					cout << "The dealer's cards are:";
					players[numberOfPlayers]->printAllCards();
					if (players[numberOfPlayers]->getTotalPoints() > 21) {
						stand = true;
					}
				}
			}
			
			if (numberOfPlayers == 1) {
				cout << "Your cards are:";
				players[0]->printAllCards();
			} else {
				for (int i = 0; i < numberOfPlayers; i++) {
					cout << "Player " << i+1 << "'s cards are:";
					players[i]->printAllCards();
				}
			}
			
			int dealerTotal = players[numberOfPlayers]->getTotalPoints();
			for (int i = 0; i < numberOfPlayers; i++) { //players still left either win or lose
				if (!players[i]->turnIsOver) {
					if (dealerTotal > 21 || players[i]->getTotalPoints() > dealerTotal) {
						players[i]->winBet();
					} else if (players[i]->getTotalPoints() < dealerTotal) {
						players[i]->loseBet();
					}
				}
			}
		}
		
		if (numberOfPlayers == 1) {
			if (players[0]->getTotalAmount() <= 0) {
				cout << "You've lost all your money.\n";
				keepPlaying = false;
			}
		} else { 
			for (int i = 0; i < numberOfPlayers; i++) { //players still left either win or lose
				if (players[i]->getTotalAmount() <= 0) {
					keepPlaying = false;
					cout << "Player " << i+1 << " lost all their money.\n";
				}
			}
		}
		
		if (!keepPlaying) {
			cout << "The game is over.\n";
		} else {
			if (numberOfPlayers == 1) {
				cout << "You currently have $" << players[0]->getTotalAmount() << endl;
			} else {
				for (int i = 0; i < numberOfPlayers; i++) {
					cout << "Player " << i+1 << " currently has $" << players[i]->getTotalAmount() << endl;
				}
			}
			bool validAnswer = false;
			while (!validAnswer) {
				cout << "Would you like to keep playing? (y/n)\n";
				char response;
				cin >> response; //check that answer is a char
				if (response == 'y' || response == 'n') {
					validAnswer = true;
					if (response == 'n') keepPlaying = false;
				} else {
					cout << "Please enter 'y' to keep playing, or 'n' to quit the game.\n";
				}
			}
		}
	}
}

int main() {
	startGame();
	return 0;
}
