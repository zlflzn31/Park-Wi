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
