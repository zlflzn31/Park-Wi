#include "stdafx.h"
#include "FiveCardDraw.h"

FiveCardDraw::FiveCardDraw()
{
	dealer = 0;
	discardedDeck = Deck();

	mainDeck = Deck();
	vector<Card> cards = vector<Card>();
	int suitNum = 4;
	int rankNum = 13;
	for (int i = 0; i < suitNum; i++)
	{
		for (int j = 0; j < rankNum; j++)
		{
			Card c;
			c.s = static_cast<Card::suit>(i); // I used static cast, but I feel that it should be different... 
			c.r = static_cast<Card::rank>(j); // 
			mainDeck.add_card(c);
		}
	}
}

int FiveCardDraw::before_turn(Player& p)
{
	cout << "Player's name: " << p.playerName << ", Hand content:" << p.playerHand << endl;
	
	int count = 0;
	vector<size_t> indices;
	do {
		cout << "If any, please type valid indices of Cards which you would like to discard." << endl;
		string input;
		size_t index;
		if (getline(cin, input)) {
			stringstream ss(input);
			while (ss >> index) {
				indices.push_back(index);
			}
		}
	} while (indices.size() > static_cast<size_t>(p.playerHand.size()));

	for (size_t i = 0; i < indices.size(); ++i) {
		discardedDeck.add_card(p.playerHand[i]);
		p.playerHand.remove_card(i);
	}
	return success;
}

int FiveCardDraw::turn(Player& p)
{
	for (size_t i = 0; i < 5 - static_cast<size_t>(p.playerHand.size()); ++i) {
		if (mainDeck.size() > 0) {
			p.playerHand << mainDeck;
		}
		else if (discardedDeck.size() > 0) {
			p.playerHand << discardedDeck;
		}
		else {
			return no_cards_left;
		}
	}
	return success;
}

int FiveCardDraw::after_turn(Player& p)
{
	cout << "Player's name: " << p.playerName << ", Hand content: " << p.playerHand << endl;
	return success;
}

int FiveCardDraw::before_round()
{
	return 0;
}

int FiveCardDraw::round()
{
	return 0;
}

int FiveCardDraw::after_round()
{
	return 0;
}
