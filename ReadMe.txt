Hong Wi, Jongwhan Park lab3
===========================
Program name: lab3.exe
Author: Hong Wi (hwi@wustl.edu), Jongwhan Park (jongwhan@wustl.edu)
Included: lab3.cpp, Deck.h, Deck.cpp, FiveCardDraw.h, FiveCardDraw.cpp, Game.h, Game.cpp, Hand.h, Hand.cpp, Player.h, Player.cpp, verifyCard.h, verifyCard.cpp

----------------
File Description
----------------
lab3.cpp: Contains the main function that runs the functions developed in this lab. This file takes in the name of the game and the names of players on the command line, and makes a corresponding game. Then, it starts the game and proceeds with the game until it stops.

Deck.h: Header file that contains declarations of Deck class.

Deck.cpp: Source file that contains definitions of Deck class, along with its methods.

FiveCardDraw.h: Header file for a FiveCardDraw class that is derived through public inheritance from the Game abstract base class.

FiveCardDraw.cpp: Source file for a FiveCardDraw class that includes definitions of game, player, turn, and round methods that is specified to this class.

Game.h: Header file for a Game abstract base class.

Game.cpp: Source file for a Game abstract base class, that includes various game, player, turn, and round methods.

Hand.h: Header file that contains declarations of Hand class.

Hand.cpp: Source file that contains definitions of Hand class, along with its methods.

Player.h: Header file for the Player struct that contains member variables and its methods.

Player.cpp: Source file for the Player struct that includes its constructor and an overloaded insertion operator.

verifyCard.h: Header file that contains declarations of the Card struct, enum types of ReturnType depending on success or failure of the program, and parseFile, printVector, rankHands, and usage functions.

verifyCard.cpp: Source file that contains definitions of the Card struct.

ReadMe.txt: Documentation of details of the lab, different errors encountered, and results of trials.

---------------
Program Summary
---------------
Given the game name "FiveCardDraw" in addition to names of at least 2 players, this program instantiates a game with those players. The game starts, and each player is dealt 5 Cards from the main deck. Each player decides to discard some number of Cards, which are then put into the discarded deck. Each round, every player is determined their hand rank, and the player with the highest rank wins the round. A player can leave or join the game every round as well. If every player in the game leaves, the game terminates.

----------------
Design Decisions
----------------
1. To avoid hard coding, I made an ReturnType enum and HandRank enum to store possible return values, depending on success or type of error occurred. In addition, I declared as const int all constant values.

2. During the course of the program, usage message is printed only in the case when the number of arguments does not equal two. This is because when the user first tries to run the program, he would simply enter "lab2", in which case he would see the usage message and learn the correct method of running the program.

3. I used character arrays for identifying valid ranks and suits for a Card, because it appears much simpler than multiple if statements.

4. In fivecarddraw.cpp, when we were moving all cards from playeers' decks and discard deck to maindeck, we just cleared everything in main, discard, and players' decks. After then, we filled every availiable combination of card into maindeck just as we did in fivecarddarw constructor. We did this for efficienicy. 


--------------
Return Results
--------------
COMMAND LINE INPUT:
===================================================================
lab3 FiveCardDraw a b c 
===================================================================



COMMAND LINE OUTPUT:
====================================================================
START ROUND !
Player's name: b, Hand content:4D 6S 8H KC KD

If any, please type valid indices of Cards which you would like to discard.
1
Player's name: a, Hand content:3H 4C 7H 9H JS

If any, please type valid indices of Cards which you would like to discard.
1
Player's name: b, Hand content: 4D 4S 8H KC KD

Player's name: a, Hand content: 3H 3S 7H 9H JS


player name: a
number of wins: 1
number of losses: 0
player's hand: 3H 3S 7H 9H JS

player name: b
number of wins: 0
number of losses: 1
player's hand: 4D 4S 8H KC KD


Is ther any player whom you want to leave? If there is not, enter 'no'. 'No', 'N
O', 'nO' won't be accepted !
Player's name:
b
leave the person!!!

Is ther any player whom you want to leave? If there is not, enter 'no'. 'No', 'N
O', 'nO' won't be accepted !
Player's name:
no

Is there any player whom you want to join? Enter 'no' if you don't want. 'NO' 'N
o' 'nO' won't be accepted!
Player's name:
d

Is there any player whom you want to join? Enter 'no' if you don't want. 'NO' 'N
o' 'nO' won't be accepted!
Player's name:
no

START ROUND !
Player's name: a, Hand content:4S 7D JC JD KD

If any, please type valid indices of Cards which you would like to discard.
Player's name: d, Hand content:2S 3D 5S 6C JH

If any, please type valid indices of Cards which you would like to discard.
1
Player's name: a, Hand content: 4S 7D JC JD KD

Player's name: d, Hand content: 2S 5S 6C 6D JH


player name: d
number of wins: 1
number of losses: 0
player's hand: 2S 5S 6C 6D JH

player name: a
number of wins: 1
number of losses: 1
player's hand: 4S 7D JC JD KD


Is ther any player whom you want to leave? If there is not, enter 'no'. 'No', 'N
O', 'nO' won't be accepted !
Player's name:
no

Is there any player whom you want to join? Enter 'no' if you don't want. 'NO' 'N
o' 'nO' won't be accepted!
Player's name:
d
Error: already_playing
==========================================================================================



------------------
Errors Encountered
------------------
I did not encounter any errors in this lab.

