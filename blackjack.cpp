/*terminal (console-based) game: Blackjack
Cynthia Zhang 9/05/2018

step 1: dealer shuffles the (6) decks of cards
step 1b: dealer reshuffles the decks when stack is empty
step 2a: each player bets an amount $2-$200
step 2b: dealer deals face up to player(s), up to himself, up to player(s), face down to self
step 3a: if dealer's face up card is a ten, face card (10) or ace, dealer checks for blackjack
step 3b: If any player has a blackjack and the dealer does not, the dealer immediately pays that player one and a half times the amount of his bet. If the dealer has a blackjack, he immediately collects the bets of all players who do not have blackjacks, (but no additional amount). If the dealer and another player both have blackjacks, the bet of that player is a stand-off (a tie), and the player takes back his chips.
step 4a: player decides whether to stand, hit, split or double down
step 4b: player can split if first two cards are of the same denomination
step 4c: if they hit, they keep choosing until they stand or bust (repeat step 4 for all players)
step 5: in the dealer's play, his face-down card is turned up. If the total is 17 or more, he must stand. If the total is 16 or under, he must take a card. He must continue to take cards until the soft total is 17 or more, at which point the dealer must stand. If the dealer has an ace, and counting it as 11 would bring his total to 17 or more (but not over 21), he must count the ace as 11 and stand.
step 6: If the dealer goes over 21, he pays each player who has stood the amount of that player's bet. If the dealer stands at 21 or less, he pays the bet of any player having a higher total (not exceeding 21) and collects the bet of any player having a lower total. If there is a stand-off (a player having the same total as the dealer), no chips are paid out or collected. 
step 7:repeat steps 1b-5 until player quits game or loses all money

Note: the player can count the ace as a 1 or 11
- Splitting Pairs: If a player's first two cards are of the same denomination, such as two jacks or two sixes, he may choose to treat them as two separate hands when his turn comes around. The amount of his original bet then goes on one of the cards, and an equal amount must be placed as a bet on the other card. The player first plays the hand to his left by standing or hitting one or more times; only then is the hand to the right played. The two hands are thus treated separately, and the dealer settles with each on its own merits. With a pair of aces, the player is given one card for each ace and may not draw again. Also, if a ten-card is dealt to one of these aces, the payoff is equal to the bet (not one and one-half to one, as with a blackjack at any other time).
- Doubling Down: Another option open to the player is doubling his bet when the original two cards dealt total 9, 10, or 11. When the player's turn comes, he places a bet equal to the original bet, and the dealer gives him just one card, which is placed face down and is not turned up until the bets are settled at the end of the hand. With two fives, the player may split a pair, double down, or just play the hand in the regular way. Note that the dealer does not have the option of splitting or doubling down.

Functions:
- shuffle decks
- deal cards (to players and dealer)
- stand (not ask for another card) 
- hit (ask for another card in an attempt to get closer to a count of 21, or even hit 21 exactly)

Classes:
- Card (Suit, Value)
- Deck

Variables:
- constant list of all cards (vector<Card>)
- deck of unplayed cards (queue<Card> or stack<Card>)
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
		
		
		//below only meant for one player
		if (players[0]->getTotalAmount() <= 0) {
			cout << "You've lost all your money. The game is over.\n";
			keepPlaying = false;
		} else {
			if (numberOfPlayers == 1) {
				cout << "You currently have $" << players[0]->getTotalAmount() << endl;
			} else {
				for (int i = 0; i < numberOfPlayers; i++) {
					cout << "Player " << i+1 << " currently has $" << players[i]->getTotalAmount() << endl;
				}
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

int main() {
	startGame(); //automatically start with one player
	return 0;
}
