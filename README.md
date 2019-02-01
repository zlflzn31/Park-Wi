# Park-Wi

Hong Wi, Jongwhan Park lab4(Card game project)
===========================
Program name: lab4.exe

Author: Hong Wi (hwi@wustl.edu), Jongwhan Park (jongwhan@wustl.edu)

Included: lab4.cpp, Deck.h, Deck.cpp, FiveCardDraw.h, FiveCardDraw.cpp, Game.h, Game.cpp, GameExceptions.h, Hand.h, Hand.cpp, Player.h, Player.cpp, PokerGame.h, PokerGame.cpp, SevenCardStud.h, SevenCardStud.cpp, TexasHoldEm.h, TexasHoldEm.cpp, verifyCard.h, verifyCard.cpp

----------------
File Description
----------------
- lab4.cpp: Contains the main function that runs the functions developed in this lab. This file takes in the name of the game and the names of players on the command line, and makes a corresponding game. Then, it starts the game and proceeds with the game until it stops. You can choose from FiveCardDraw, SevenCardStud, and TexasHoldEm.
- Deck.h: Header file that contains declarations of Deck class.
- Deck.cpp: Source file that contains definitions of Deck class, along with its methods.
- FiveCardDraw.h: Header file for a FiveCardDraw class that is derived through public inheritance from the Game abstract base class. This header file enables the player to play the FiveCardDraw game.
- FiveCardDraw.cpp: Source file for a FiveCardDraw class that includes definitions of game, player, turn, and round methods that is specified to this class. This source file enables the player to play the FiveCardDraw game.
- Game.h: Header file for a Game abstract base class.
- Game.cpp: Source file for a Game abstract base class, that includes various game, player, turn, and round methods.
- GameExceptions.h: Header file that contains exceptions that are thrown in specific circumstances.
- Hand.h: Header file that contains declarations of Hand class.
- Hand.cpp: Source file that contains definitions of Hand class, along with its methods.
- Player.h: Header file for the Player struct that contains member variables and its methods.
- Player.cpp: Source file for the Player struct that includes its constructor and an overloaded insertion operator.
- PokerGame.h: Header file that contains declarations of PokerGame class, which is an intermedate class derived from Game class.
- PokerGame.cpp: Source file for the PokerGame class that includes its functions.
- SevenCardStud.h: Header file for a SevenCardStud class that is derived through public inheritance from the PokerGame base class. This header file enables the player to play the SevenCardStud game.
- SevenCardStud.cpp: Source file for a SevenCardStud class that includes definitions of round, after_round method. It also includes a definition for the bestFive function that determines the best rank that can be obtained by choosing 5 out of 7 cards. This source file enables the player to play the SevenCardStud game.
- TexasHoldEm.h: Header file for a TexasHoldEm class that is derived through public inheritance from the PokerGame base class. This header file enables the player to play the TexasHoldEm game.
- TexasHoldEm.cpp: Source file for a TexasHoldEm class that includes definitions of round, after_round method. It also includes a definition for the bestFive function that determine the best rank that can be obtained by choosing 5 out of 7 cards, which compose of 2 of player's cards and 5 of shared cards. This source file enables the player to play the TexasHoldEm game.
- verifyCard.h: Header file that contains declarations of the Card struct, enum types of ReturnType depending on success or failure of the program, and parseFile, printVector, rankHands, and usage functions.
- verifyCard.cpp: Source file that contains definitions of the Card struct.
- ReadMe.txt: Documentation of details of the lab, different errors encountered, and results of trials.

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

![output](https://user-images.githubusercontent.com/21351568/47060581-d2183680-d193-11e8-8d11-96b4b8ae8ecb.png)

(!) EVERY PROCESS FOR TEXASHOLDEM AND SEVENCARDSTUD WILL BE VERY SIMULAR TO FIVECARDDRAW.

------------
Extra Credit
------------
We have implemented a TexasHoldEm class that creates and plays a TexasHoldEm class. 
Please refer to TexasHoldEm.cpp and TexasHoldEm.h.
