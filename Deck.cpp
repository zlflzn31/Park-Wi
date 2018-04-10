#include "stdafx.h"
#include "verifyCard.h"
#include "Deck.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <stdexcept>

/*

The name of this file : Deck.cpp
Author : Hong Wi, hwi@wustl.edu

This cpp file contains general use of Deck class.
* Deck(char * fileName) is a constructor that will call load(fileName);

* load function(char* fileName) returns errorcontrol to determine the success or the failiure.
This function behaaves samely from parsefile function of verifyCard.cpp.

* shuffle function simply shuffles private member varialbe deck.

* size function returns private member variable deck's size.

* operator<< is for printing out what is in deck member variable.

*/


using namespace std;

Deck::Deck()
{
}

Deck::Deck(char* fileName)
{

	ErrorControl loaded = load(fileName);
	if (loaded == ErrorControl::unable_to_open_file) // if the error is occurred
	{
		throw runtime_error("Error: unable to open a file"); // referenced from https://www.cs.uaf.edu/2010/spring/cs202/lecture/03_02_exceptions.html.
	}
}

Deck::~Deck()
{
}

ErrorControl Deck::load(char* fileName)
{
	ifstream ifs(fileName);
	if (ifs.is_open())
	{
		string line, word;
		while (getline(ifs, line)) // reading a line 
		{
			if (line.empty()) // to skip "blank" lines. 
			{
				continue;
			}
			istringstream iss(line);
			while (iss >> word)
			{
				if (word == "//" || word == " //")
				{
					break;
				}
				Card c;
				const int zero = 0; //dealing with letter index 
				const int two = 2; // dealing with letter length
				const int three = 3;// dealing with letter length 
				if (word.length() == three)  //first, dealing with 10c, 10d cases. 
				{
					char suitAdded = word.at(2);
					if (word.substr(zero, two) != "10") //checking if the input card's value is 10 or not. 
					{
						cout << "INVALID CARD" << endl;
						continue; //if the value is not 10, c.r will not be assigned a value. 
					}
					else
					{
						c.r = Card::rank::ten;  //if the value is 10, then we assign c.r card::rank::ten.
					}
					if (suitAdded == 'C' || suitAdded == 'c') { c.s = Card::suit::clubs; }
					else if (suitAdded == 'D' || suitAdded == 'd') { c.s = Card::suit::diamonds; }
					else if (suitAdded == 'H' || suitAdded == 'h') { c.s = Card::suit::hearts; }
					else if (suitAdded == 'S' || suitAdded == 's') { c.s = Card::suit::spades; }
					else
					{
						cout << "INVALID CARD" << endl;
						continue;
					} //if nothing matches, c.s will not be assigned a value. 
				}//END OF WORD.LENGTH == THREE

				else if (word.length() == two) //dealing with 2c 9d cases. 
				{
					char suitAdded = word.at(1);
					char rankAdded = word.at(0);

					if (rankAdded == '2') { c.r = Card::rank::two; }
					else if (rankAdded == '3') { c.r = Card::rank::three; }
					else if (rankAdded == '4') { c.r = Card::rank::four; }
					else if (rankAdded == '5') { c.r = Card::rank::five; }
					else if (rankAdded == '6') { c.r = Card::rank::six; }
					else if (rankAdded == '7') { c.r = Card::rank::seven; }
					else if (rankAdded == '8') { c.r = Card::rank::eight; }
					else if (rankAdded == '9') { c.r = Card::rank::nine; }
					else if (rankAdded == 'J' || rankAdded == 'j') { c.r = Card::rank::jack; }
					else if (rankAdded == 'K' || rankAdded == 'k') { c.r = Card::rank::king; }
					else if (rankAdded == 'Q' || rankAdded == 'q') { c.r = Card::rank::queen; }
					else if (rankAdded == 'A' || rankAdded == 'a') { c.r = Card::rank::ace; }
					else
					{
						cout << "INVALID CARD" << endl;
						continue;
					}//same logic I mentioned in if (word.length() == three)
					if (suitAdded == 'C' || suitAdded == 'c') { c.s = Card::suit::clubs; }
					else if (suitAdded == 'H' || suitAdded == 'h') { c.s = Card::suit::hearts; }
					else if (suitAdded == 'D' || suitAdded == 'd') { c.s = Card::suit::diamonds; }
					else if (suitAdded == 'S' || suitAdded == 's') { c.s = Card::suit::spades; }
					else
					{
						cout << "INVALID CARD" << endl;
						continue;
					}
				}//END OF WORD.LENGTH == 2
				 // if more than length 3. ... 
				deck.push_back(c);
			} //end of while iss >> word

		}
		ifs.close();
		return success;
	}
	else
	{
		return unable_to_open_file;
	}
};

// add_card method in #4
ErrorControl Deck::add_card(Card c) {
	deck.push_back(c);
	return success;
}

void Deck::shuffle()
{
	random_device rd;
	mt19937 g(rd());
	std::shuffle(deck.begin(), deck.end(), g); // usage is referred from C++ reference page. Stated in the instruction. 
};

int Deck::size() const
{
	return deck.size();
}

//same logic from printOutput function. 
ostream & operator<<(ostream & o, const Deck &passedDeck)
{

	string validCard;
	for (size_t i = 0; i < passedDeck.size(); ++i)
	{
		if (passedDeck.deck[i].r == Card::rank::two) { validCard = "2"; }
		else if (passedDeck.deck[i].r == Card::rank::three) { validCard = "3"; }
		else if (passedDeck.deck[i].r == Card::rank::four) { validCard = "4"; }
		else if (passedDeck.deck[i].r == Card::rank::five) { validCard = "5"; }
		else if (passedDeck.deck[i].r == Card::rank::six) { validCard = "6"; }
		else if (passedDeck.deck[i].r == Card::rank::seven) { validCard = "7"; }
		else if (passedDeck.deck[i].r == Card::rank::eight) { validCard = "8"; }
		else if (passedDeck.deck[i].r == Card::rank::nine) { validCard = "9"; }
		else if (passedDeck.deck[i].r == Card::rank::ten) { validCard = "10"; }
		else if (passedDeck.deck[i].r == Card::rank::jack) { validCard = "J"; }
		else if (passedDeck.deck[i].r == Card::rank::queen) { validCard = "Q"; }
		else if (passedDeck.deck[i].r == Card::rank::king) { validCard = "K"; }
		else if (passedDeck.deck[i].r == Card::rank::ace) { validCard = "A"; }
		else {};
		if (passedDeck.deck[i].s == Card::suit::clubs) { validCard += "C"; }
		else if (passedDeck.deck[i].s == Card::suit::diamonds) { validCard += "D"; }
		else if (passedDeck.deck[i].s == Card::suit::hearts) { validCard += "H"; }
		else if (passedDeck.deck[i].s == Card::suit::spades) { validCard += "S"; }
		else {};
		o << validCard << endl;
	}
	return o;
}
