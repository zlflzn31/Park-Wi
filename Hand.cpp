#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Hand.h"
#include "verifyCard.h"
#include "Deck.h"

/*

The name of this file : Hand.cpp
Author : Hong Wi, hwi@wustl.edu


This cpp file contains general use of Hand class.
* Hand(char * copiedHand) is a copy function.

* int size() const; returns a size of hand member variable.

* string asString() const; returns a string containing a space-seperated sequence of vaild card.

* Hand & operator= (const Hand &);
* bool operator== (const Hand &) const;
* bool operator< (const Hand &) const;
-======= these three operators are implemented for comparison purpose.

* bool poker_rank(const Hand &FirHand, const Hand &SecHand); this function determines whether FirHand is higher than SecHand (based on rank).

* int rank_hand(const Hand &givenHand); this function is determining the rank of the givenhand.


*/

using namespace std;

//default constructor
Hand::Hand() = default;

//copy 
Hand::Hand(const Hand &copiedHand)
{
	this->hand = copiedHand.hand;
}
//I simply implement the printout function from verifyCard.cpp since both need to behave samely. 
string Hand::asString() const
{
	string printed = "";
	string temp;
	for (size_t i = 0; i < hand.size(); i++)
	{
		if (hand[i].r == Card::rank::two) { temp = "2"; }
		else if (hand[i].r == Card::rank::three) { temp = "3"; }
		else if (hand[i].r == Card::rank::four) { temp = "4"; }
		else if (hand[i].r == Card::rank::five) { temp = "5"; }
		else if (hand[i].r == Card::rank::six) { temp = "6"; }
		else if (hand[i].r == Card::rank::seven) { temp = "7"; }
		else if (hand[i].r == Card::rank::eight) { temp = "8"; }
		else if (hand[i].r == Card::rank::nine) { temp = "9"; }
		else if (hand[i].r == Card::rank::ten) { temp = "10"; }
		else if (hand[i].r == Card::rank::jack) { temp = "J"; }
		else if (hand[i].r == Card::rank::queen) { temp = "Q"; }
		else if (hand[i].r == Card::rank::king) { temp = "K"; }
		else if (hand[i].r == Card::rank::ace) { temp = "A"; }
		else {};
		if (hand[i].s == Card::suit::clubs) { temp += "C"; }
		else if (hand[i].s == Card::suit::diamonds) { temp += "D"; }
		else if (hand[i].s == Card::suit::hearts) { temp += "H"; }
		else if (hand[i].s == Card::suit::spades) { temp += "S"; }
		else {};
		printed += temp + " ";
	}
	return printed;
}

//return size method of elements in the container member variable ( private hand)
int Hand::size() const
{
	return hand.size();
}

//assingment operator
Hand & Hand::operator= (const Hand &givenHand)
{
	if (this == &givenHand)
	{
		return *this;
	}
	this->hand = givenHand.hand;
	return *this;
}

// Hand equivalence operator, returns true iff exactly the same sequence of cards appears in both objects
bool Hand::operator== (const Hand & h) const
{
	if (this->size() != h.size())
	{
		return false;
	}
	bool ans = true;
	for (auto i = 0; i < h.size(); ++i)
	{
		ans &= (this->hand[i] == h.hand[i]);
	}
	return ans;
}

// Hand less than operator, returns true iff the sequence of cards in the object on which the operator was called
// should appear before the sequence of cards in the passed object according to a lexical ordering
bool Hand::operator< (const Hand & h) const
{
	bool prefix = true;
	for (auto i = 0; i < this->size(); ++i)
	{
		prefix &= (this->hand[i] == h.hand[i]);
	}
	if (prefix && this->size() < h.size())
	{
		return true;
	}

	auto i = 0;
	while (this->hand[i] == h.hand[i])
	{
		++i;
	}
	return (this->hand[i] < h.hand[i]);
}

//indexing operator in #5
Card Hand::operator[](size_t i) {
	if (i >= hand.size()) {
		throw runtime_error("Error: there is no card at the position given");
	}
	else {
		return hand[i];
	}
}

void Hand::remove_card(size_t i) {
	if (i >= hand.size()) {
		throw runtime_error("Error: there is no card at the position given");
	}
	else {
		hand.erase(hand.begin() + i);
	}
}

//destructor
Hand::~Hand()
{
}

//printing out hands overloaded function using asString
ostream & operator<<(ostream &o, const Hand &givenHand)
{
	o << givenHand.asString() << endl;
	return o;
}
//Removing card from givenDeck and adding it to givenHand. 
void operator<<(Hand &givenHand, Deck &givenDeck)
{

	const int one = 1;
	Card card = givenDeck.deck[(givenDeck.deck.size() - one)];
	givenHand.hand.push_back(card);
	givenDeck.deck.pop_back();
	sort(givenHand.hand.begin(), givenHand.hand.end());
}

//it determines the rank of a given hand. 
int rank_hand(Hand & h)
{
	Card first = h.hand[0];
	Card second = h.hand[1];
	Card third = h.hand[2];
	Card fourth = h.hand[3];
	Card fifth = h.hand[4];

	// All 5 cards have same suit.
	if (first.s == second.s && second.s == third.s && third.s == fourth.s && fourth.s == fifth.s)
	{
		// If all 5 cards have same suit and their ranks are consecutive, it is a straight flush.
		if ((first.r + 4 == fifth.r) || (first.r == '6' && fifth.r == Card::rank::ten) || (first.r == '7' && fifth.r == 'J') ||
			(first.r == '8' && fifth.r == 'Q') || (first.r == '9' && fifth.r == 'K') || (first.r == Card::rank::ten && fifth.r == 'A') ||
			(first.r == '2' && second.r == '3' && third.r == '4' && fourth.r == '5' && fifth.r == 'A'))
		{
			h.handRank = HandRank::straightflush;
		}
		// If their ranks are not consecutive, it is just a flush.
		else
		{
			h.handRank = HandRank::flush;
		}
	}
	// AAAAB or ABBBB
	else if ((first.r == fourth.r) || (second.r == fifth.r))
	{
		h.handRank = HandRank::fourofakind;
	}
	// AABBB or AAABB
	else if ((first.r == second.r && second.r != third.r && third.r == fifth.r) ||
		(first.r == third.r && third.r != fourth.r && fourth.r == fifth.r))
	{
		h.handRank = HandRank::fullhouse;
	}
	// 5 consecutive ranks regardless of suit
	else if ((first.r + 1 == second.r && second.r + 1 == third.r && third.r + 1 == fourth.r && fourth.r + 1 == fifth.r) ||
		(first.r == '6' && second.r == '7' && third.r == '8' && fourth.r == '9' && fifth.r == Card::rank::ten) ||
		(first.r == '7' && second.r == '8' && third.r == '9' && fourth.r == Card::rank::ten && fifth.r == 'J') ||
		(first.r == '8' && second.r == '9' && third.r == Card::rank::ten && fourth.r == 'J' && fifth.r == 'Q') ||
		(first.r == '9' && second.r == Card::rank::ten && third.r == 'J' && fourth.r == 'Q' && fifth.r == 'K') ||
		(first.r == Card::rank::ten && second.r == 'J' && third.r == 'Q' && fourth.r == 'K' && fifth.r == 'A') ||
		(first.r == '2' && second.r == '3' && third.r == '4' && fourth.r == '5' && fifth.r == 'A'))
	{
		h.handRank = HandRank::straight;
	}
	// AAABC, ABBBC, ABCCC
	else if ((first.r == third.r && third.r != fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r == fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r != third.r && third.r == fifth.r))
	{
		h.handRank = HandRank::threeofakind;
	}
	// AABBC, AABCC, ABBCC
	else if ((first.r == second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
		(first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r) ||
		(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r == fifth.r))
	{
		h.handRank = HandRank::twopairs;
	}
	// AABCD, ABBCD, ABCCD, ABCDD
	else if ((first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
	{
		h.handRank = HandRank::onepair;
	}
	else
	{
		h.handRank = HandRank::norank;
	}
	return h.handRank;
}

// returns true iff the first hand object ranks higher than the second hand object in the poker hand ranking definition
bool poker_rank(const Hand & h1, const Hand & h2)
{
	// if two hands' ranks are different
	if (h1.handRank != h2.handRank)
	{
		return (h1.handRank > h2.handRank);
	}

	Card c10 = h1.hand[0];
	Card c11 = h1.hand[1];
	Card c12 = h1.hand[2];
	Card c13 = h1.hand[3];
	Card c14 = h1.hand[4];
	Card c20 = h2.hand[0];
	Card c21 = h2.hand[1];
	Card c22 = h2.hand[2];
	Card c23 = h2.hand[3];
	Card c24 = h2.hand[4];

	// if both ranks are no rank or flush
	if (h1.handRank == HandRank::norank || h1.handRank == HandRank::flush)
	{
		if (c14.r != c24.r) { return (c24 < c14); }
		else
		{
			if (c13.r != c23.r) { return (c23 < c13); }
			else
			{
				if (c12.r != c22.r) { return (c22 < c12); }
				else
				{
					if (c11.r != c21.r) { return (c21 < c11); }
					else
					{
						return (c20 < c10);
					}
				}
			}
		}
	}
	// if both ranks are one pair
	else if (h1.handRank == HandRank::onepair)
	{
		int h1rank, h2rank;
		Hand h1copy = Hand(h1);
		Hand h2copy = Hand(h2);
		for (auto i = 0; i < h1.size() - 1; ++i)
		{
			if (h1.hand[i].r == h1.hand[i + 1].r)
			{
				h1rank = i;
				h1copy.hand.erase(h1copy.hand.begin() + i, h1copy.hand.begin() + (i + 2));
			}
			if (h2.hand[i].r == h2.hand[i + 1].r)
			{
				h2rank = i;
				h2copy.hand.erase(h2copy.hand.begin() + i, h2copy.hand.begin() + (i + 2));
			}
		}
		if (!(h1.hand[h1rank] == h2.hand[h2rank]))
		{
			return (h2.hand[h2rank] < h1.hand[h1rank]);
		}
		else
		{
			sort(h1copy.hand.begin(), h1copy.hand.end());
			sort(h2copy.hand.begin(), h2copy.hand.end());
			c10 = h1copy.hand[0];
			c11 = h1copy.hand[1];
			c12 = h1copy.hand[2];
			c20 = h2copy.hand[0];
			c21 = h2copy.hand[1];
			c22 = h2copy.hand[2];
			if (c12.r != c22.r) { return (c22 < c12); }
			else
			{
				if (c11.r != c21.r) { return (c21 < c11); }
				else
				{
					return (c20 < c10);
				}
			}
		}
	}
	// if both ranks are two pair
	else if (h1.handRank == HandRank::twopairs)
	{
		int h1rank, h2rank;
		Hand h1copy = Hand(h1);
		Hand h2copy = Hand(h2);
		for (auto i = h1.size() - 2; i >= 0; i--)
		{
			if (h1.hand[i].r == h1.hand[i + 1].r)
			{
				h1rank = i;
				h1copy.hand.erase(h1copy.hand.begin() + i, h1copy.hand.begin() + (i + 2));
				break;
			}
		}
		for (auto i = h2.size() - 2; i >= 0; i--)
		{
			if (h2.hand[i].r == h2.hand[i + 1].r)
			{
				h2rank = i;
				h2copy.hand.erase(h2copy.hand.begin() + i, h2copy.hand.begin() + (i + 2));
				break;
			}
		}
		if (!(h1.hand[h1rank] == h2.hand[h2rank]))
		{
			return (h2.hand[h2rank] < h1.hand[h1rank]);
		}
		else
		{
			sort(h1copy.hand.begin(), h1copy.hand.end());
			sort(h2copy.hand.begin(), h2copy.hand.end());
			for (auto i = 0; i < h1.size() - 1; ++i)
			{
				if (h1.hand[i].r == h1.hand[i + 1].r)
				{
					h1rank = i;
					break;
				}
			}
			for (auto i = 0; i < h1.size() - 1; ++i)
			{
				if (h2.hand[i].r == h2.hand[i + 1].r)
				{
					h2rank = i;
					break;
				}
			}
			if (h1copy.hand[h1rank].r != h2copy.hand[h2rank].r)
			{
				return (h2copy.hand[h2rank] < h1copy.hand[h1rank]);
			}
			else
			{
				h1copy.hand.erase(h1copy.hand.begin() + h1rank, h1copy.hand.begin() + (h1rank + 2));
				h2copy.hand.erase(h2copy.hand.begin() + h2rank, h2copy.hand.begin() + (h2rank + 2));
				return (h2copy.hand[0] < h1copy.hand[0]);
			}
		}
	}
	// if both ranks are three of a kind
	else if (h1.handRank == HandRank::threeofakind)
	{
		int h1rank, h2rank;
		Hand h1copy = Hand(h1);
		Hand h2copy = Hand(h2);
		for (auto i = 0; i < h1.size() - 2; ++i)
		{
			if (h1.hand[i].r == h1.hand[i + 1].r && h1.hand[i + 1].r == h1.hand[i + 2].r)
			{
				h1rank = i;
			}
			if (h2.hand[i].r == h2.hand[i + 1].r && h2.hand[i + 1].r == h2.hand[i + 2].r)
			{
				h2rank = i;
			}
		}
		if (h1copy.hand[h1rank].r != h2copy.hand[h2rank].r)
		{
			return (h2copy.hand[h2rank] < h1copy.hand[h1rank]);
		}
		else
		{
			h1copy.hand.erase(h1copy.hand.begin() + h1rank, h1copy.hand.begin() + (h1rank + 3));
			h2copy.hand.erase(h2copy.hand.begin() + h2rank, h2copy.hand.begin() + (h2rank + 3));
			sort(h1copy.hand.begin(), h1copy.hand.end());
			sort(h2copy.hand.begin(), h2copy.hand.end());
			c10 = h1copy.hand[0];
			c11 = h1copy.hand[1];
			c20 = h2copy.hand[0];
			c21 = h2copy.hand[1];
			if (c11.r != c21.r) { return (c21 < c11); }
			else
			{
				return (c20 < c10);
			}
		}
	}
	// if both ranks are straight or straight flush
	else if (h1.handRank == HandRank::straight || h1.handRank == HandRank::straightflush)
	{
		return (h2.hand[4] < h1.hand[4]);
	}
	// if both ranks are full house
	else if (h1.handRank == HandRank::fullhouse)
	{
		int triple1, triple2;
		if (c10.r == c12.r)
		{
			triple1 = 0;
		}
		else
		{
			triple1 = h1.size() - 1;
		}
		if (c20.r == c22.r)
		{
			triple2 = 0;
		}
		else
		{
			triple2 = h2.size() - 1;
		}
		if (h1.hand[triple1].r != h2.hand[triple2].r)
		{
			return (h2.hand[triple2] < h1.hand[triple1]);
		}
		else
		{
			return (h2.hand[h2.size() - 1 - triple2] < h1.hand[h1.size() - 1 - triple1]);
		}
	}
	// if both ranks are four of a kind
	else
	{
		int quad1, quad2;
		if (c10.r == c13.r)
		{
			quad1 = 0;
		}
		else
		{
			quad1 = h1.size() - 1;
		}
		if (c20.r == c23.r)
		{
			quad2 = 0;
		}
		else
		{
			quad2 = h2.size() - 1;
		}
		if (h1.hand[quad1].r != h2.hand[quad2].r)
		{
			return (h2.hand[quad2] < h1.hand[quad1]);
		}
		else
		{
			return (h2.hand[h2.size() - 1 - quad2] < h1.hand[h1.size() - 1 - quad1]);
		}
	}
}