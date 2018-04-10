========================================================================
    CONSOLE APPLICATION : lab2 Project Overview
========================================================================
Hong Wi , lab 2

Program Name: _lab2
Author: Hong Wi hwi@wustl.edu
Files: verifyCard.h, verifyCard.cpp, Deck.h, Deck.cpp, Hand.h, Hand.cpp, lab2.cpp (which contains a main function). ReadMe.txt

1. File Description
2. Error Cases
3. behaviors
4. any Error
5. design decision
6. extra credits 
---------------------------------------

1. File Description 
verifyCard.h : struct Card with using enum, and opeartor<, 
			   Error control with using enum, 
			   function declarations for parsefile function ,
			   fileOutput fuctnion(with printOutput helper function),
			   pokerHand function, and
			   UsageMsg function.

			   
verifyCard.cpp : main source file with implementing functions that were declared from verifyCard.h. 


Deck.h : class Deck with 
	friend ostream &operator << (ostream &, const Deck &); // only for deck 
	friend void operator<<(Hand &, Deck &); // for both hand and deck 
	public:
		Deck();
		Deck(char*);
		~Deck();
		ErrorControl load(char*);
		void shuffle();
		int size() const;
	private:
		vector<Card> deck;
	ostream & operator<<(ostream &o, const Deck &passedDeck);

Deck.cpp :
	Deck.cpp deals with general use of deck class. It compares and prints out what the private member "deck" contains. Also, it reutns size of member deck, and shuffls what insdide of it.

Hand.h :
	friend void operator<<(Hand &, Deck &);
	friend ostream & operator<<(ostream &, const Hand &); 
	friend bool poker_rank(const Hand &hand1, const Hand &hand2);
	friend int rank_hand(const Hand &ahand);
	public:
		Hand();
		Hand(const Hand &);
		int size() const;
		string asString() const;
		Hand & operator= (const Hand &);
		bool operator== (const Hand &) const;
		bool operator< (const Hand &) const;
		~Hand();

	private:
		vector<Card> hand;
	void operator<<(Hand &givenHand, Deck &givenDeck);
	enum HandRank { norank, onepair, twopairs, threeofakind, straight, flush, fullhouse, fourofakind, straightflush };
	bool poker_rank(const Hand &FirHand, const Hand &SecHand);
	int rank_hand(const Hand &givenHand);

Hand.cpp :
	Hand.cpp deals with general use of hand class. It has contrcutor, destructor and copy function like anyother class. 
	Also, it has operators to deal with comparison purpose. 
	Also, << operator prints out what is inside of hand class, and removes what inside of deck and adds it to hand. 
	poker_rank and rank_hand functions are dealing with to compare two hand objects and determine which one is bigger. 

lab2.cpp : this is a main function that deals with errorcontrol cases. 

ReadMe.txt : Text description of all files and error cases. 


2. Error Cases
There are FOUR CASES in enum ErrorControl: 
	success = 0,
	unable_to_open_file = 1,
	command_line_wrong = 2,
	vector_is_empty = 3,
	onlyOne_with_shuffle = 4,
	twoArgs_nonShuffle = 5,
	non_CmdArgs = 6,
	More_than_3Args = 7,
	floated_error = 8,
	wrong_implementation_of_poekr_rank = 9

================================================================================\

3. Behaviors
input file = the file from lab0 (exactly same)
command line argument = _lab2 hands.txt -shuffle
-OUTPUT--------------------------------------------------------
Deck after dealt
3C
2S
4H
9H
8S
3D
QS

Hand after dealt
hand1= 10H JC JD JS AC

hand2= 5D 7D 7H 7S 8C

hand3= 2C 2D 10D 10S QH

hand4= 2H 6D 7C 9D QC

hand5= 4D 6H 10C QD KC

hand6= 5S 8H KD KS AD

hand7= 3H 3S 5H 8D KH

hand8= 6C 6S JH AH AS

hand9= 4C 4S 5C 9C 9S

Hands sorted by less than opeartor
hand1= 2C 2D 10D 10S QH

hand2= 3H 3S 5H 8D KH

hand3= 4C 4S 5C 9C 9S

hand4= 2H 6D 7C 9D QC

hand5= 4D 6H 10C QD KC

hand6= 6C 6S JH AH AS

hand7= 5D 7D 7H 7S 8C

hand8= 5S 8H KD KS AD

hand9= 10H JC JD JS AC

Hands sorted by poker-rank operator
hand1= 10H JC JD JS AC

hand2= 5D 7D 7H 7S 8C

hand3= 6C 6S JH AH AS

hand4= 2C 2D 10D 10S QH

hand5= 4C 4S 5C 9C 9S

hand6= 5S 8H KD KS AD

hand7= 3H 3S 5H 8D KH

hand8= 4D 6H 10C QD KC

hand9= 2H 6D 7C 9D QC
--------------------------------------------
It seems working now on :) 

4. Any errors while doing this lab
I spent lots of times dealing with poker rank condition. Not 100percently implementing it causes some wierd ordering. 
Other than that, I was fine. 

5. design decision
The major design decision is that I sepearted hand and deck classes in different cpp files. 
I could have combined together, but I thought that it would be really long. So I decided to seperated them. Thereby, I had to created variable, 
class Deck; class Hand; in each header file. 

6. extra credit 

A.8 - A.9 (exception)
This one applies to my case even though I did not use try and catch . 
If everycase in my maint function is not applied to any specific event, I return ErrorControl::floated_error. 

A.12 - A.15 (pointers and arrays)
Since I am using vector container, I am not dealing with fixed length buffers. Also, I do not dereference zero pointer. 
I do use 

A.16 (debugging)
This point is where I am trying very hard right now. 

B.10 - B.12 (constructor)

In my Deck constructor, I do not initialize anything here, simply I call a fuction that is called "load". 
Also, I declared everything of deck class in header file first and defined in cpp file. I also made the member variable as private. 


B.18 
Rather than making as a private function, I made operators as friended to hand and deck classes to access private member variable. 

B. 31 
Yes I did include inclusion guards to each my header file. I followed it as instructed in the programming guideline. 
