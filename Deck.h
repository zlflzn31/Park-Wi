#pragma once

/*
The name of this file: Deck.h
Author: Hong Wi, Jongwhan Park, hwi@wustl.edu, jongwhan@wustl.edu
This header file contains header information about Deck class.
Deck class contains << operator,
two constructors (one is default),
destructor,
load function that takes a char* and returns errortype,
shuffle function to shuffle the deck,
and size to return int value of deck of size.
And vector<Card> deck is a private member since we dont want it be accessed without authorization.
*/



#ifndef DECK_H
#define DECK_H

#include "VerifyCard.h"

#include <vector>
#include <iostream>
using namespace std;

//Since I seperated Hand from Deck, (I could have combined both, but I didn't since I dont want too many lines in a file) I have to include class Hand here.
class Hand;

class Deck
{
	//these are friended due to they need to access private member variable Deck. 
	friend ostream &operator << (ostream &, const Deck &); // only for deck 
	friend void operator<<(Hand &, Deck &); // for both hand and deck 
	friend class FiveCardDraw;
public:
	Deck();
	Deck(char*);
	~Deck();
	ErrorControl load(char*);
	ErrorControl add_card(Card);
	void shuffle();
	int size() const;
private:
	vector<Card> deck;
};

ostream & operator<<(ostream &o, const Deck &passedDeck);



#endif /* DECK_H */
