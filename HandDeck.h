//
// File name: HandDeck.h
// Name of author: Jongwhan Park
// Email of author: jongwhan@wustl.edu
// Summary: Lab 2 header file that contains declarations of the Hand and Deck classes, and enum of HandRank
//

#include "Card.h"

#ifndef HANDDECK_H
#define HANDDECK_H

class Deck;

class Hand
{
	friend ostream & operator<< (ostream &, const Hand &);
	friend void operator<< (Hand &, Deck &);
	friend void rankHands(Hand &);
	friend bool poker_rank(const Hand &, const Hand &);
public:
	Hand();
	Hand(const Hand &);
	~Hand();
	Hand & operator= (const Hand &);
	int size() const;
	bool operator== (const Hand &) const;
	bool operator< (const Hand &) const;
	string asString() const;
//private:
	vector<Card> h_;
	int handRank;
};

class Deck
{
	friend ostream & operator<<(ostream &, const Deck &);
	friend void operator<< (Hand &, Deck &);
public:
	Deck(char *);
	~Deck();
	ReturnType load(char *);
	void shuffleCards();
	int size() const;
private:
	vector<Card> d_;
};

enum HandRank
{
	no_rank,
	one_pair,
	two_pair,
	three_of_a_kind,
	straight,
	flush,
	full_house,
	four_of_a_kind,
	straight_flush
};

ostream & operator<< (ostream &, const Hand &);
void operator<< (Hand &, Deck &);
void rankHands(Hand &);
bool poker_rank(const Hand &, const Hand &);

#endif /* HANDDECK_H */