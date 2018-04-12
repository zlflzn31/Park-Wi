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
	mainDeck.shuffle();

	playersVec[0];
	if ( dealer == playersVec.size() -1) // if dealer is at last position. 
	{
		const int startIndex = 0;
		const int endIndex = playersVec.size()-1;
		const int max_handsize = 5;
		//while loop with a condition that looks for both values are 5 or not. If 5, then done. 
		//since we want to make sure each player has received five cards. 
		size_t eachIndex = 0;
		//this while loop deals one card from deck to each player. 
		while ( playersVec[startIndex]->playerHand.size() != max_handsize && playersVec[endIndex]->playerHand.size() != max_handsize ) 
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck;
			++eachIndex;
		}
		//this for loop calls before_turn. 
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{
			//at each player, call before turn. 
			//return 0, if success. 
		}
	}
	else // if deal is not at last position. i.e among 3 players, if second player is a dealer, then first player's index is the starting point. 
	{
		const int startIndex = dealer + 1;
		const int endIndex = playersVec.size() - 1;
		const int max_handsize = 5;
		size_t eachIndex = startIndex;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != max_handsize && playersVec[dealer]->playerHand.size() != max_handsize)
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck; // to iterate each player in the playersvec, used % playersVec.size()
			++eachIndex;
		}
		//this for loop calls before_turn. 
		// since startIndex can happen at the middle, 
		//playersvec.size() + (starIndex % playersVec.size()) will iterate indexes that are less than startPoint. 
		for (size_t i = startIndex; i < playersVec.size() + (startIndex % playersVec.size() ); ++i)
		{
			//at each player, call before turn. 
			//return 0, if success. 
		}
	}

	return 0; //temporarily inserted. 
}

int FiveCardDraw::round()
{
	if (dealer == playersVec.size() - 1) // if dealer is at last position. 
	{
		const int startIndex = 0;
		const int endIndex = playersVec.size() - 1;
		const int max_handsize = 5;
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{
			//at each player, call turn and after_turn. 
			// if any turn method returns a non-zero value, then immediately return it.
			//return 0, if success. 

		}
	}
	else
	{
		const int startIndex = dealer + 1;
		const int endIndex = playersVec.size() - 1;
		const int max_handsize = 5;
		for (size_t i = startIndex; i < playersVec.size() + (startIndex % playersVec.size()); ++i)
		{
			//at each player, call turn and after_turn. 
			// if any turn method returns a non-zero value, then immediately return it.
			//return 0, if success. 
		}
	}

	return 0; //temporarily inserted. 
}

// this is needed to sort in after_round. 
bool poker_rank(shared_ptr<Player>& p1, shared_ptr<Player>& p2)
{
	if (p1.get() == NULL) // if p1 is singular, return false. 
	{
		return false;
	}
	else // if p1 is not singualr, return true.  
	{
		return true;
	}
	if (p2.get() == NULL) // if p2 = singular, return true/. 
	{
		return true;
	}
	return poker_rank(p1->playerHand, p2->playerHand);
}

int FiveCardDraw::after_round()
{
	vector<shared_ptr<Player>> temp;
	for (size_t i = 0; i < playersVec.size(); ++i)
	{
		temp.push_back(playersVec[i]);
	}
	sort(temp.begin(), temp.end());
	return 0;
}
