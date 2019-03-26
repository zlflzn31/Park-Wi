#pragma once


#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <vector>
#include <string>
#include "verifyCard.h"
#include "deck.h" 

/*
The name of this file: Hand.h
Author: Hong Wi, hwi@wustl.edu
This header file contains header information about Hand class.
Hand class contains << operators for (insertiob for output and for from deck to hand)
two constructors (one is default),
destructor,
asString() that returns a string value,
operators ( =, ==, and < ) that are needed for comparison,
size function to return int value of hand of size,
and pokerrank function along with rank_hand to determine the rank of the hand.
And vector<Card> Hand is a private member since we dont want it be accessed without authorization.
*/


using namespace std;

//Since I seperated Deck from Hand, (I could have combined both, but I didn't since I dont want too many lines in a file) I have to include class Deck here.
class Deck;
class Hand {
	//these functions are friended due to they need to access private variable. 
	friend void operator<<(Hand &, Deck &);
	friend ostream & operator<<(ostream &, const Hand &);
	friend bool poker_rank(const Hand &, const Hand &);
	friend int rank_hand(Hand &);
	friend class PokerGame;
	friend class SevenCardStud; //lab4
	friend class TexasHoldEm;

public:
	Hand();
	Hand(const Hand &);
	int size() const;
	string asString() const;
	Hand & operator= (const Hand &);
	bool operator== (const Hand &) const;
	bool operator< (const Hand &) const;
	Card operator[] (size_t);
	void remove_card(size_t);
	~Hand();

private:
	vector<Card> hand;
	int handRank;
};
//void operator<<(Hand &hand, Deck &deck);
void operator<<(Hand &givenHand, Deck &givenDeck);


//enum of Rank of the hand is created here due to very efficient reason for poker_rank. 
enum HandRank { norank, onepair, twopairs, threeofakind, straight, flush, fullhouse, fourofakind, straightflush };

bool poker_rank(const Hand &FirHand, const Hand &SecHand);
int rank_hand(Hand &);

#endif /* HAND_H */
