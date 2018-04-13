//
// File name: HandDeck.cpp
// Name of author: Jongwhan Park
// Email of author: jongwhan@wustl.edu
// Summary: Lab 2 source file that contains definitions of Deck and Hand classes, along with their methods.
//

#include "stdafx.h"
#include "HandDeck.h"
#include <string>

// Deck constructor that takes a file name and passes it into a call to the load method
Deck::Deck(char * file_name)
{
	load(file_name);
}

// Deck destructor
Deck::~Deck()
{
}

// Deck load method that takes a file name, opens up a file, and reads in valid card definition strings from the file
// this simply uses the parseFile I wrote in labs 0 and 1
// if the file could not be opened, throw a runtime error
ReturnType Deck::load(char * file_name)
{
	ReturnType result = parseFile(d_, file_name);
	if (result == ReturnType::unable_to_open_file)
	{
		throw runtime_error("Unable to open file");
	}
	else
	{
		return success;
	}
}

// Deck shuffle method that randomizes the order of cards
void Deck::shuffleCards()
{
	shuffle(this->d_.begin(), this->d_.end(), default_random_engine{});
}

// Deck size method
int Deck::size() const
{
	return this->d_.size();
}

// Deck insertion operator
ostream & operator<< (ostream & o, const Deck & d)
{
	for (size_t i = 0; i < d.d_.size(); ++i)
	{
		string s = "";

		if (d.d_[i].r == Card::rank::ten)
		{
			s += "10";
		}
		else
		{
			s += d.d_[i].r;
		}
		s += d.d_[i].s;
		o << s << endl;
	}
	return o;
}

// Hand default constructor
Hand::Hand()
{
}

// Hand copy constructor
Hand::Hand(const Hand & h)
	:h_(h.h_), handRank(h.handRank)
{}

// Hand destructor
Hand::~Hand()
{
}

// Hand assignment operator
Hand & Hand::operator= (const Hand & h)
{
	// checks for self-assignment
	if (this == &h)
	{
		return *this;
	}
	this->h_ = h.h_;
	this->handRank = h.handRank;
	return *this;
}

// Hand size method
int Hand::size() const
{
	return this->h_.size();
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
		ans &= (this->h_[i] == h.h_[i]);
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
		prefix &= (this->h_[i] == h.h_[i]);
	}
	if (prefix && this->size() < h.size())
	{
		return true;
	}

	auto i = 0;
	while (this->h_[i] == h.h_[i])
	{
		++i;
	}
	return (this->h_[i] < h.h_[i]);
}

// Hand as string method that returns a C++ style string of valid card definition strings
string Hand::asString() const
{
	string ans;
	for (auto i = 0; i < this->size(); ++i)
	{
		Card c = this->h_[i];
		if (c.r == Card::rank::ten)
		{
			ans += "10";
		}
		else
		{
			ans += c.r;
		}
		ans += c.s;
		ans += " ";
	}
	return ans;
}

// Hand insertion operator for Hand
ostream & operator<< (ostream & o, const Hand & h)
{
	o << h.asString();
	return o;
}

// deal operator that takes a card from the deck and puts it in a hand
void operator<< (Hand & h, Deck & d)
{
	Card c = d.d_[d.d_.size() - 1];
	h.h_.push_back(c);
	d.d_.pop_back();
	sort(h.h_.begin(), h.h_.end());
}

// rankHands method that determines the handRank private variable of a Hand. assume hands are sorted and has 5 cards
void rankHands(Hand & h)
{
	Card first = h.h_[0];
	Card second = h.h_[1];
	Card third = h.h_[2];
	Card fourth = h.h_[3];
	Card fifth = h.h_[4];

	// All 5 cards have same suit.
	if (first.s == second.s && second.s == third.s && third.s == fourth.s && fourth.s == fifth.s)
	{
		// If all 5 cards have same suit and their ranks are consecutive, it is a straight flush.
		if ((first.r + 4 == fifth.r) || (first.r == '6' && fifth.r == Card::rank::ten) || (first.r == '7' && fifth.r == 'J') ||
			(first.r == '8' && fifth.r == 'Q') || (first.r == '9' && fifth.r == 'K') || (first.r == Card::rank::ten && fifth.r == 'A') ||
			(first.r == '2' && second.r == '3' && third.r == '4' && fourth.r == '5' && fifth.r == 'A'))
		{
			h.handRank = HandRank::straight_flush;
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
		h.handRank = HandRank::four_of_a_kind;
	}
	// AABBB or AAABB
	else if ((first.r == second.r && second.r != third.r && third.r == fifth.r) ||
		(first.r == third.r && third.r != fourth.r && fourth.r == fifth.r))
	{
		h.handRank = HandRank::full_house;
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
		h.handRank = HandRank::three_of_a_kind;
	}
	// AABBC, AABCC, ABBCC
	else if ((first.r == second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
		(first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r) ||
		(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r == fifth.r))
	{
		h.handRank = HandRank::two_pair;
	}
	// AABCD, ABBCD, ABCCD, ABCDD
	else if ((first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
		(first.r != second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
	{
		h.handRank = HandRank::one_pair;
	}
	else
	{
		h.handRank = HandRank::no_rank;
	}
}

// returns true iff the first hand object ranks higher than the second hand object in the poker hand ranking definition
bool poker_rank(const Hand & h1, const Hand & h2)
{
	// if two hands' ranks are different
	if (h1.handRank != h2.handRank)
	{
		return (h1.handRank > h2.handRank);
	}

	Card c10 = h1.h_[0];
	Card c11 = h1.h_[1];
	Card c12 = h1.h_[2];
	Card c13 = h1.h_[3];
	Card c14 = h1.h_[4];
	Card c20 = h2.h_[0];
	Card c21 = h2.h_[1];
	Card c22 = h2.h_[2];
	Card c23 = h2.h_[3];
	Card c24 = h2.h_[4];

	// if both ranks are no rank or flush
	if (h1.handRank == HandRank::no_rank || h1.handRank == HandRank::flush)
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
	else if (h1.handRank == HandRank::one_pair)
	{
		int h1rank, h2rank;
		Hand h1copy = Hand(h1);
		Hand h2copy = Hand(h2);
		for (auto i = 0; i < h1.size() - 1; ++i)
		{
			if (h1.h_[i].r == h1.h_[i + 1].r)
			{
				h1rank = i;
				h1copy.h_.erase(h1copy.h_.begin() + i, h1copy.h_.begin() + (i + 2));
			}
			if (h2.h_[i].r == h2.h_[i + 1].r)
			{
				h2rank = i;
				h2copy.h_.erase(h2copy.h_.begin() + i, h2copy.h_.begin() + (i + 2));
			}
		}
		if (!(h1.h_[h1rank] == h2.h_[h2rank])) 
		{ 
			return (h2.h_[h2rank] < h1.h_[h1rank]); 
		}
		else
		{
			sort(h1copy.h_.begin(), h1copy.h_.end());
			sort(h2copy.h_.begin(), h2copy.h_.end());
			c10 = h1copy.h_[0];
			c11 = h1copy.h_[1];
			c12 = h1copy.h_[2];
			c20 = h2copy.h_[0];
			c21 = h2copy.h_[1];
			c22 = h2copy.h_[2];
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
	else if (h1.handRank == HandRank::two_pair)
	{
		int h1rank, h2rank;
		Hand h1copy = Hand(h1);
		Hand h2copy = Hand(h2);
		for (auto i = h1.size() - 2; i >= 0; i--)
		{
			if (h1.h_[i].r == h1.h_[i + 1].r)
			{
				h1rank = i;
				h1copy.h_.erase(h1copy.h_.begin() + i, h1copy.h_.begin() + (i + 2));
				break;
			}
		}
		for (auto i = h2.size() - 2; i >= 0; i--)
		{
			if (h2.h_[i].r == h2.h_[i + 1].r)
			{
				h2rank = i;
				h2copy.h_.erase(h2copy.h_.begin() + i, h2copy.h_.begin() + (i + 2));
				break;
			}
		}
		if (!(h1.h_[h1rank] == h2.h_[h2rank]))
		{
			return (h2.h_[h2rank] < h1.h_[h1rank]);
		}
		else
		{
			sort(h1copy.h_.begin(), h1copy.h_.end());
			sort(h2copy.h_.begin(), h2copy.h_.end());
			for (auto i = 0; i < h1.size() - 1; ++i)
			{
				if (h1.h_[i].r == h1.h_[i + 1].r)
				{
					h1rank = i;
					break;
				}
			}
			for (auto i = 0; i < h1.size() - 1; ++i)
			{
				if (h2.h_[i].r == h2.h_[i + 1].r)
				{
					h2rank = i;
					break;
				}
			}
			if (h1copy.h_[h1rank].r != h2copy.h_[h2rank].r)
			{
				return (h2copy.h_[h2rank] < h1copy.h_[h1rank]);
			}
			else
			{
				h1copy.h_.erase(h1copy.h_.begin() + h1rank, h1copy.h_.begin() + (h1rank + 2));
				h2copy.h_.erase(h2copy.h_.begin() + h2rank, h2copy.h_.begin() + (h2rank + 2));
				return (h2copy.h_[0] < h1copy.h_[0]);
			}
		}
	}
	// if both ranks are three of a kind
	else if (h1.handRank == HandRank::three_of_a_kind)
	{
		int h1rank, h2rank;
		Hand h1copy = Hand(h1);
		Hand h2copy = Hand(h2);
		for (auto i = 0; i < h1.size() - 2; ++i)
		{
			if (h1.h_[i].r == h1.h_[i + 1].r && h1.h_[i + 1].r == h1.h_[i + 2].r)
			{
				h1rank = i;
			}
			if (h2.h_[i].r == h2.h_[i + 1].r && h2.h_[i + 1].r == h2.h_[i + 2].r)
			{
				h2rank = i;
			}
		}
		if (h1copy.h_[h1rank].r != h2copy.h_[h2rank].r)
		{
			return (h2copy.h_[h2rank] < h1copy.h_[h1rank]);
		}
		else
		{
			h1copy.h_.erase(h1copy.h_.begin() + h1rank, h1copy.h_.begin() + (h1rank + 3));
			h2copy.h_.erase(h2copy.h_.begin() + h2rank, h2copy.h_.begin() + (h2rank + 3));
			sort(h1copy.h_.begin(), h1copy.h_.end());
			sort(h2copy.h_.begin(), h2copy.h_.end());
			c10 = h1copy.h_[0];
			c11 = h1copy.h_[1];
			c20 = h2copy.h_[0];
			c21 = h2copy.h_[1];
			if (c11.r != c21.r) { return (c21 < c11); }
			else
			{
				return (c20 < c10);
			}
		}
	}
	// if both ranks are straight or straight flush
	else if (h1.handRank == HandRank::straight || h1.handRank == HandRank::straight_flush)
	{
		return (h2.h_[4] < h1.h_[4]);
	}
	// if both ranks are full house
	else if (h1.handRank == HandRank::full_house)
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
		if (h1.h_[triple1].r != h2.h_[triple2].r)
		{
			return (h2.h_[triple2] < h1.h_[triple1]);
		}
		else
		{
			return (h2.h_[h2.size() - 1 - triple2] < h1.h_[h1.size() - 1 - triple1]);
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
		if (h1.h_[quad1].r != h2.h_[quad2].r)
		{
			return (h2.h_[quad2] < h1.h_[quad1]);
		}
		else
		{
			return (h2.h_[h2.size() - 1 - quad2] < h1.h_[h1.size() - 1 - quad1]);
		}
	}
}