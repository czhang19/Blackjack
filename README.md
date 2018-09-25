# Blackjack
by Jinghua (Cynthia) Zhang
09/24/2018

Instructions to run the code:
1. Compile all files in the terminal by typing "make game" in the Blackjack directory
2. Run the game by typing "./game" in the terminal

Notes on the game:
1. The players have a choice of hitting, standing or doubling down. In this game, they can not split pairs.
2. The game ends when the player loses all of their money. In multiplayer mode, the game ends when any of the players loses their money. 
3. The game can handle when the user inputs values of the expected data type, but the user should not input a different data type than expected. For example, do not enter a character when an integer is expected. The game can handle when the user inputs 800 for example, when the expected range is 2 to 500.

Design Choices/Data Structures/Algorithms:
- Used unordered map, queues and vectors from STL to store information on the deck, cards and players
- created my own algorithm for shuffling the deck of cards
- made separate classes for the player, deck and card
- stored players in a vector to allow for multiplayer game play

Choice of Language:
- Used C++ as an object-oriented language to create separate classes
- C++ has a large function library, used unordered map, queue and vector from the Standard Template Library (STL)
- C++ is a powerful language and allows for possibly modifying this project from a terminal-based application into a GUI application