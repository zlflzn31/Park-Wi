# Park-Wi

Hong Wi, Jongwhan Park lab4(Card game project)
===========================
Program name: lab4.exe
Author: Hong Wi (hwi@wustl.edu), Jongwhan Park (jongwhan@wustl.edu)
Included: lab4.cpp, Deck.h, Deck.cpp, FiveCardDraw.h, FiveCardDraw.cpp, Game.h, Game.cpp, GameExceptions.h, Hand.h, Hand.cpp, Player.h, Player.cpp, PokerGame.h, PokerGame.cpp, SevenCardStud.h, SevenCardStud.cpp, TexasHoldEm.h, TexasHoldEm.cpp, verifyCard.h, verifyCard.cpp

----------------
File Description
----------------
lab4.cpp: Contains the main function that runs the functions developed in this lab. This file takes in the name of the game and the names of players on the command line, and makes a corresponding game. Then, it starts the game and proceeds with the game until it stops. You can choose from FiveCardDraw, SevenCardStud, and TexasHoldEm.

Deck.h: Header file that contains declarations of Deck class.

Deck.cpp: Source file that contains definitions of Deck class, along with its methods.

FiveCardDraw.h: Header file for a FiveCardDraw class that is derived through public inheritance from the Game abstract base class. This header file enables the player to play the FiveCardDraw game.

FiveCardDraw.cpp: Source file for a FiveCardDraw class that includes definitions of game, player, turn, and round methods that is specified to this class. This source file enables the player to play the FiveCardDraw game.

Game.h: Header file for a Game abstract base class.

Game.cpp: Source file for a Game abstract base class, that includes various game, player, turn, and round methods.

GameExceptions.h: Header file that contains exceptions that are thrown in specific circumstances.

Hand.h: Header file that contains declarations of Hand class.

Hand.cpp: Source file that contains definitions of Hand class, along with its methods.

Player.h: Header file for the Player struct that contains member variables and its methods.

Player.cpp: Source file for the Player struct that includes its constructor and an overloaded insertion operator.

PokerGame.h: Header file that contains declarations of PokerGame class, which is an intermedate class derived from Game class.

PokerGame.cpp: Source file for the PokerGame class that includes its functions.

SevenCardStud.h: Header file for a SevenCardStud class that is derived through public inheritance from the PokerGame base class. This header file enables the player to play the SevenCardStud game.

SevenCardStud.cpp: Source file for a SevenCardStud class that includes definitions of round, after_round method. It also includes a definition for the bestFive function that determines the best rank that can be obtained by choosing 5 out of 7 cards. This source file enables the player to play the SevenCardStud game.

TexasHoldEm.h: Header file for a TexasHoldEm class that is derived through public inheritance from the PokerGame base class. This header file enables the player to play the TexasHoldEm game.

TexasHoldEm.cpp: Source file for a TexasHoldEm class that includes definitions of round, after_round method. It also includes a definition for the bestFive function that determine the best rank that can be obtained by choosing 5 out of 7 cards, which compose of 2 of player's cards and 5 of shared cards. This source file enables the player to play the TexasHoldEm game.

verifyCard.h: Header file that contains declarations of the Card struct, enum types of ReturnType depending on success or failure of the program, and parseFile, printVector, rankHands, and usage functions.

verifyCard.cpp: Source file that contains definitions of the Card struct.

ReadMe.txt: Documentation of details of the lab, different errors encountered, and results of trials.

---------------
Program Summary
---------------
Given the game name "FiveCardDraw", "SevenCardStud", or "TexasHoldEm" in addition to names of at least 2 players, this program instantiates a game with those players. 
For FiveCardDraw, when the game starts, each player is dealt 5 cards from the main deck. Each player decides to discard some number of cards, which are then put into the discarded deck. Each round, every player is determined their hand rank, and the player with the highest rank wins the round.
For SevenCardStud, each turn, the players are dealt some number of face up and face down cards. At the end, each player will have 7 cards, from which he can choose best 5 to determine his rank. Then, the player with the highest rank wins the round.
For TexasHoldEm, each player gets 2 cards, and there are 5 shared cards. From a combined total of 7 cards, each player chooses best 5 to determine his rank. Then, the player with the highest rank wins the round.
For each game, a player can leave or join the game every round as well. If every player leaves the game or only one player remains, the game terminates. 
After each game is over, you can choose to start a new game. 


----------------
Design Decisions
----------------
1. Suppose a player plays in a game, which terminates later. When we start a new game and try to add the player with the exact same name, the player's previous information (win count, loss count) are retained. This is because he is actually the same person. 

2. In before_turn method of FiverCardDraw.cpp, We implemented cin.ignore(numeric_limits<streamsize>::max(), '\n') logic to deal with input strings easily. However, this logic led us to "PRESS ENTER ONCE" before typing the indices of the player's hand, which is following one after the first player's hand. 


--------------
Return Results (TESTING THE PROGREM)
--------------

IT STARTS FROM HERE: 

Microsoft Windows [Version 6.1.7601]
Copyright (c) 2009 Microsoft Corporation.  All rights reserved.

H:\>cd my documents

H:\My Documents>cd visual studio 2015

H:\My Documents\Visual Studio 2015>cd projects

H:\My Documents\Visual Studio 2015\Projects>cd lab4!

H:\My Documents\Visual Studio 2015\Projects\lab4!>cd debug

H:\My Documents\Visual Studio 2015\Projects\lab4!\Debug>lab4! FiveCardDraw ab ba

Start Round!
ab: 5S 7H 8D 10C AC
ba: 3H 4H 5H 8H KD
(================================================================================)

ab: Which action will you take ? Enter :  bet_one_chip, bet_two_chips, or check.

check

ab's current chips before his bet: 19
ab's current betCount before his bet.0
current bet value: 0.

ab's current chips after his bet: 19
ab's current betCount after his bet.0

(================================================================================)


ba: Which action will you take ? Enter :  bet_one_chip, bet_two_chips, or check.

check

ba's current chips before his bet: 19
ba's current betCount before his bet.0
current bet value: 0.

ba's current chips after his bet: 19
ba's current betCount after his bet.0

(================================================================================)

ab's current bet count = 0 and total chips == 19
ba's current bet count = 0 and total chips == 19
(================================================================================)

Player's name: ba, Hand content:3H 4H 5H 8H KD
Enter the positions of the card that you want to discard. From 0 ~ 4.
You can discard multiple cards. Seperate the indices in between with 'space'.
For any player after the 'first' one, you have to PRESS ENTER ONCE!! and then ty
pe the indices you want to discard.
0 1
Player's name: ab, Hand content:5S 7H 8D 10C AC
Enter the positions of the card that you want to discard. From 0 ~ 4.
You can discard multiple cards. Seperate the indices in between with 'space'.
For any player after the 'first' one, you have to PRESS ENTER ONCE!! and then ty
pe the indices you want to discard.
1 0
1 0
Player's name: ba, Hand content: 5H 8H 8S JS KD
, folded: False
Player's name: ab, Hand content: 2D 6C 8D 10C AC
, folded: False
(================================================================================)


ab: Which action will you take ? Enter :  bet_one_chip, bet_two_chips, or check.

bet_one_chip

ab's current chips before his bet: 19
ab's current betCount before his bet.0
current bet value: 1.

ab's current chips after his bet: 18
ab's current betCount after his bet.1

(================================================================================)


ba: Which action will you take ? Enter :  raise_one_chip, raise_two_chips, call,
 or fold.
raise_one_chip

ba's current chips before his bet: 19
ba's current betCount before his bet.0
current bet value: 2.

ba's current chips after his bet: 17
ba's current betCount after his bet.2

(================================================================================)

ab's current bet count = 1 and total chips == 18
ba's current bet count = 2 and total chips == 17
(================================================================================)

ab: raise_one_chip, raise_two_chips, call, or fold.
call

ab's current chips before his bet: 18
ab's current betCount before his bet.1
current bet value: 2.

ab's current chips after his bet: 17
ab's current betCount after his bet.2
(================================================================================)

ba

player name: ba
number of wins: 7
number of losses: 5
number of chips: 23
player's hand: 5H 8H 8S JS KD

player name: ab
number of wins: 5
number of losses: 7
number of chips: 17
player's hand: 2D 6C 8D 10C AC


Do you want, ab to leave?
If yes, enter the name. If not, enter 'no' (NO, No, On won't be accepted).
ab
Do you want, ba to leave?
If yes, enter the name. If not, enter 'no' (NO, No, On won't be accepted).
no
There is only one player in the game. The game is ended automatically. Thank you
 for playing.
Game ended.
Type 'newgame' to start a new game. Any other response will terminate the progra
m.
newgame
Which game would you like to play? Type 'FiveCardDraw', 'SevenCardStud', or 'Tex
asHoldEm', followed by names of players.
SevenCardStud ac ca
Start Round!

Turn 1

Deal to player ac
Player ac's hand: 6S 8S 10H
Player ca's hand:

Deal to player ca
Player ca's hand: 7D 8C 8D
Player ac's hand: * * 10H
(================================================================================)
ac: Which action will you take ? Enter :  bet_one_chip, bet_two_chips, or check.


===============================END OF THE PROGRAM=================================
ALMOST EVERY PROCESS FOR TEXASHOLDEM AND SEVENCARDSTUD WILL BE VERY SIMULAR TO FIVECARDDRAW. ALSO, THE 
REASON WHY ab and ba's numbers of wins and losses are 5 and 7 IS THAT WE HAVE DONE 
FEW GAMES WITH THOSE NAMES PREVIOUSLY. SO FOR EVERY NEW GAME FOR PREVIOUS PLAYERS, 
THEIR CHIPS WILL BE RESETTED IN EACH GAME. HOWEVER, SINCE THEY ARE SAME HUMAN BEINGS, 
WE DECIDED TO KEEP THEIR NUMBERS OF WINS AND LOSSES PERMENANTLY.

------------
Extra Credit
------------
We have implemented a TexasHoldEm class that creates and plays a TexasHoldEm class. 
Please refer to TexasHoldEm.cpp and TexasHoldEm.h.
