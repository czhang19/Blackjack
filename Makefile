all: game

game: blackjack.o card.o deck.o player.o 
	g++ -std=c++11 -g -o game blackjack.o card.o deck.o player.o 
	
blackjack.o: blackjack.cpp
	g++ -c -std=c++11 -g blackjack.cpp

card.o: card.cpp card.h 
	g++ -c -std=c++11 -g card.cpp

deck.o: deck.cpp deck.h card.h player.h
	g++ -c -std=c++11 -g deck.cpp
	
player.o: player.cpp player.h
	g++ -c -std=c++11 -g player.cpp

clean:
	rm -f game *.o