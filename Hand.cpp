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

//equilvalence operator
bool Hand::operator== (const Hand &givenHand) const
{
	if (this->size() != givenHand.size())
	{
		return false;
	}
	bool determineTruth = true;
	for (auto i = 0; i < givenHand.size(); ++i)
	{
		determineTruth &= (this->hand[i].r == givenHand.hand[i].r && this->hand[i].s == givenHand.hand[i].s);
	}
	return determineTruth;
}

//less than opeator. 
bool Hand::operator< (const Hand &givenHand) const
{
	bool determineTruth = true;
	for (auto i = 0; i < this->size(); ++i)
	{
		determineTruth &= ((this->hand[i].r == givenHand.hand[i].r && this->hand[i].s == givenHand.hand[i].s));
	}
	if (determineTruth && this->size() < givenHand.size())
	{
		return true;
	}
	auto t_s = 0;
	while ((this->hand[t_s].r == givenHand.hand[t_s].r && this->hand[t_s].s == givenHand.hand[t_s].s))
	{
		++t_s;
	}
	return (this->hand[t_s + 1] < givenHand.hand[t_s + 1]);
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
int rank_hand(const Hand &givenHand)
{
	Card first = givenHand.hand[0];
	Card second = givenHand.hand[1];
	Card third = givenHand.hand[2];
	Card fourth = givenHand.hand[3];
	Card fifth = givenHand.hand[4];

	if ((first.s == second.s) && (second.s == third.s) && (third.s == fourth.s) && (fourth.s == fifth.s))  // if same suit. 
	{
		if (fifth.r == Card::ace)
		{
			if ((fourth.r - first.r) == 3)
			{
				return HandRank::straightflush;
			}
		}
		if (first.r == fourth.r || second.r == fifth.r)
		{
			return HandRank::fourofakind;
		}
		if ((first.r == second.r && third.r == fifth.r) ||
			(first.r == third.r && fourth.r == fifth.r))
		{
			return HandRank::fullhouse;
		}
		else if ((first.r == third.r && fourth.r != fifth.r) ||
			(second.r == fourth.r) ||
			(third.r == fifth.r && first.r != second.r))
		{
			return HandRank::threeofakind;
		}
		else if ((first.r == second.r && third.r == fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r == third.r && fourth.r == fifth.r) ||
			(first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
		{
			return HandRank::twopairs;
		}
		else if ((first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
		{
			return HandRank::onepair;
		}
		return HandRank::flush;
	}
	else //if not same suit. 
	{
		// meaning that if fifth one is great than first one by 5. - consecutive 
		if ((fifth.r - fourth.r) == 1 && (fourth.r - third.r) == 1 && (third.r - second.r) == 1 && (second.r - first.r) == 1
			)
		{
			return HandRank::straightflush;

		}
		else if (first.r == fourth.r || second.r == fifth.r)
		{
			return HandRank::fourofakind;
		}
		else if ((first.r == second.r && third.r == fifth.r) ||
			(first.r == third.r && fourth.r == fifth.r))
		{
			return HandRank::fullhouse;
		}
		else if ((fifth.r - fourth.r == 1 && fourth.r - third.r == 1 && third.r - second.r == 1 && second.r - first.r == 1) ||
			(fifth.r == Card::ace && fourth.r - third.r == 1 && third.r - second.r == 1 && second.r - first.r == 1)) // meaning every card is consecutive.
		{
			return HandRank::straight;
		}
		else if ((first.r == third.r && fourth.r != fifth.r) ||
			(second.r == fourth.r) ||
			(third.r == fifth.r && first.r != second.r))
		{
			return HandRank::threeofakind;
		}
		else if ((first.r == second.r && third.r == fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r == third.r && fourth.r == fifth.r) ||
			(first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
		{
			return HandRank::twopairs;
		}
		else if ((first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
		{
			return HandRank::onepair;
		}
		else
		{
			return HandRank::norank;
		}

	}

}


// it returns wheter firsthand is greater than secondhand. 
bool poker_rank(const Hand &FirHand, const Hand &SecHand)
{
	int first = 0, second = 1, third = 2, fourth = 3, fifth = 4; // to deal with hardcoding problem. first = first card. I set first as 0 since array index 0 is essseitnally first. 
																 // since we have const givens, I make two hand classes to deal with this problem. 
	Hand hand1;
	for (int i = 0; i < FirHand.size(); i++) {
		hand1.hand.push_back(FirHand.hand[i]);
	}
	sort(hand1.hand.begin(), hand1.hand.end());
	Hand hand2;
	for (int i = 0; i < SecHand.size(); i++) {
		hand2.hand.push_back(SecHand.hand[i]);
	}
	sort(hand2.hand.begin(), hand2.hand.end());
	int rankhand1 = rank_hand(FirHand);
	int rankhand2 = rank_hand(SecHand);
	// if these two rankhands are different, simply compare those two rankhand values. 
	//if not, we have to compare each case. 


	if (rankhand1 == rankhand2)
	{
		//if it is straight or straightflush, just sort by hand
		if (rankhand1 == HandRank::straight || rankhand1 == HandRank::straightflush)
		{
			return hand2.hand[fifth].r <hand1.hand[fifth].r;
		}
		//flush and no rank's logic acts samely, from highest ranking card to next one. 
		// enum zero to four, mine is first ~ fifth. so four == fifth. 

		else if (rankhand1 == HandRank::norank || rankhand1 == HandRank::flush)
		{
			if (hand1.hand[fifth].r == hand2.hand[fifth].r)
			{
				if (hand1.hand[fourth].r != hand2.hand[fourth].r)
				{
					return hand2.hand[fourth].r < hand1.hand[fourth].r;
				}
				else // if fourth == fourth, see third. 
				{
					if (hand1.hand[third].r != hand2.hand[third].r)
					{
						return hand2.hand[third].r < hand1.hand[third].r;
					}
					else // if third == third, see second
					{
						if (hand1.hand[second].r != hand2.hand[second].r)
						{
							return hand2.hand[second].r < hand1.hand[second].r;
						}
						else // if second == second, see first. 
						{
							if (hand1.hand[first].r != hand2.hand[first].r)
							{
								return hand2.hand[first].r < hand1.hand[first].r;
							}
						}
					}
				}

			}
			else
			{
				return hand2.hand[fifth].r < hand1.hand[fifth].r;
			}

		}
		else if (rankhand1 == HandRank::fourofakind)
		{
			return hand2.hand[third].r < hand1.hand[third].r;

		}
		else if (rankhand1 == HandRank::fullhouse)
		{
			if (hand1.hand[third].r == hand2.hand[third].r) //so,(I.E) if when same three cards in two hands. 
			{
				if (hand1.hand[second].r != hand1.hand[third].r)  //first hand == 22kkk
				{
					if (hand2.hand[second].r != hand2.hand[third].r) // second hand == 33kkk
					{
						return hand2.hand[second].r < hand1.hand[second].r;
					}
					else if (hand2.hand[fourth].r != hand2.hand[third].r) //second = kkkAA
					{
						return hand2.hand[fourth].r < hand1.hand[second].r;
					}
				}
				else // if 666kk
				{
					if (hand2.hand[second].r != hand2.hand[third].r) //22kkk
					{
						return hand2.hand[second].r < hand1.hand[fourth].r;
					}
					else if (hand2.hand[fourth].r != hand2.hand[third].r) //kkkaa
					{
						return hand2.hand[fourth].r < hand1.hand[fourth].r;
					}
				}
			}
			else // if third card of each hand is different, simply return below one. 
			{
				return hand2.hand[third].r < hand1.hand[third].r;
			}
		}
		else if (rankhand1 == HandRank::threeofakind)
		{
			if (hand1.hand[third].r == hand2.hand[third].r)
			{
				if (hand1.hand[second].r != hand1.hand[third].r) //IF FIRST HAND IS LIKE, 12888
				{
					if (hand2.hand[second].r != hand2.hand[third].r) // SO, FIRST HAND == 12888, SECOND HAND == 34888
					{
						if (hand1.hand[first].r != hand2.hand[first].r) // if first card is not same, 
						{
							return hand2.hand[first].r < hand1.hand[first].r;
						}
						else
						{
							return hand2.hand[second].r < hand1.hand[second].r;// first card is same, but second card is not same. 
						}
					}
					else if (hand2.hand[fourth].r != hand2.hand[third].r)// SO FIRST == 12888 SECOND = 888KJ. 
					{ //the other two cards cannot have any identical. 
						return hand2.hand[fourth].r < hand1.hand[first].r;

					}
				}
				else if (hand1.hand[fourth].r != hand1.hand[third].r) // IF FIRST HAND IS LIKE, 888KJ,
				{
					if (hand2.hand[second].r != hand2.hand[third].r) // first hand == 888KJ, second == 12888. 
					{
						return hand2.hand[fourth].r < hand1.hand[first].r;
					}
					else if (hand2.hand[fourth].r != hand2.hand[third].r) // first hand == 888KJ, second == 888QA. 
					{
						if (hand1.hand[fourth].r == hand2.hand[fourth].r) // if fourth card is same, then return fifth card. 
						{
							return hand2.hand[fifth].r < hand1.hand[fifth].r;
						}
						else
						{
							return hand2.hand[fourth].r < hand1.hand[fourth].r;// if fourth card is not same, then simply return it. 
						}
					}
				}
			}
			else // if if third card of each hadnd is different, simply return below one. 
			{
				return hand2.hand[third].r < hand1.hand[third].r;
			}
		}
		else if (rankhand1 == HandRank::twopairs)
		{
			if (hand1.hand[fourth].r == hand2.hand[fourth].r) // 122AA and 377AA such cases. More detailed bottom. 
			{
				// now look for second card, //(112AA, 117AA) or (122AA, 177AA).  
				//if second card is same, then return result of third card. 
				if (hand1.hand[second].r == hand2.hand[second].r)
				{
					if (hand1.hand[first].r != hand2.hand[first].r) //meaning 177AA, 377AA
					{
						return hand2.hand[first].r < hand1.hand[first].r;
					}
					else if (hand1.hand[third].r != hand2.hand[third].r) //meaning 113AA, 117AA
					{
						return hand2.hand[third].r < hand1.hand[third].r;
					}

				}
				//if second card is not same, then return the result of second card. 
				else //meaning (122AA, 133AA) or (116AA, 338AA).
				{
					return hand2.hand[second].r < hand1.hand[second].r;
				}

			}
			else //122KK and 122AA right? then simply return fourth one. 
			{
				return hand2.hand[fourth].r < hand1.hand[third].r;
			}
		}
		//if one pair
		else if (rankhand1 == HandRank::onepair)
		{
			//find one pair of each first. 
			Card::rank onePairFirHandRank;
			for (auto i = 0; i < FirHand.size() - 1; ++i) // no point of looking the last element of the hand.
			{
				if (FirHand.hand[i].r == FirHand.hand[i + 1].r)
				{
					onePairFirHandRank = FirHand.hand[i].r;
					break;
				}
			}
			Card::rank onePairSecHandRank;
			for (auto i = 0; i < SecHand.size() - 1; ++i) // no point of looking the last element of the hand.
			{
				if (SecHand.hand[i].r == SecHand.hand[i + 1].r)
				{
					onePairSecHandRank = SecHand.hand[i].r;
					break;
				}
			}
			//see if theese two one pairs are not equal, if not equal, then return the comparison of both. 
			if (onePairFirHandRank != onePairSecHandRank)
			{
				return onePairSecHandRank < onePairFirHandRank;
			}
			else // if these two are equal, then look for the other cards. 
			{
				vector<Card> FirHandOthers;
				for (auto i = 0; i < FirHand.size(); ++i)
				{
					if (FirHand.hand[i].r != onePairFirHandRank)
					{
						FirHandOthers.push_back(FirHand.hand[i]);
					}
				}
				vector<Card> SecHandOthers;
				for (auto i = 0; i < SecHand.size(); ++i)
				{
					if (SecHand.hand[i].r != onePairSecHandRank)
					{
						SecHandOthers.push_back(SecHand.hand[i]);
					}
				}
				const int first = 0;
				const int second = 1;
				const int third = 2;
				// sort is needed to be safely determining. 
				sort(FirHandOthers.begin(), FirHandOthers.end());
				sort(SecHandOthers.begin(), SecHandOthers.end());
				// then compare from the highest to lowerst. 
				if (FirHandOthers[third].r == SecHandOthers[third].r)
				{
					if (FirHandOthers[second].r == SecHandOthers[second].r)
					{
						return SecHandOthers[first].r < FirHandOthers[first].r;
					}
					else
					{
						return SecHandOthers[second].r < FirHandOthers[second].r;
					}
				}
				else
				{
					return SecHandOthers[third].r < FirHandOthers[third].r;
				}
			}
		}
		else
		{
			return ErrorControl::wrong_implementation_of_poker_rank;
		}
	}
	else  //if rankhand1 and rankhand2 are not equal, then simply return it. 
	{
		return rankhand1 > rankhand2;
	}
}
