/*
The name of this file: FiveCardDraw.cpp
Author: Hong Wi, hwi@wustl.edu, Jongwhan Park, jongwhan@wustl.edu
This is the source file for the FiveCardDraw class, which contains its constructor, turn, and round methods.
*/

#include "stdafx.h"
#include "FiveCardDraw.h"
#include "GameExceptions.h"


// FiveCardDraw constructor
FiveCardDraw::FiveCardDraw() : PokerGame()
{
	cards_per_hand = 5;
}

//before_turn method
int FiveCardDraw::before_turn(Player& p)
{
	if (p.isFold)
	{
		return 0;
	}

	cout << "Player's name: " << p.playerName << ", Hand content:" << p.playerHand;
	cout << "Enter the position, IN ORDER, of the card that you want to discard. From 0 ~ 4. " << endl;
	cout << "You can discard multiple cards until you enter 'n' at the end. " <<
			"i.e (012n) or (01 {endl} 2n)  will discard 0,1, and 2 cards. " << endl;
	char in;
	int i = 0, j = 0; // i is index from user input. 
	while (cin >> in)
	{

		if (in == 'n')
		{
			break;
		}
		else if (in == '0' || in == '1' || in == '2' || in == '3' || in == '4')
		{
			i = in - 48; // change the char value to int
			try
			{
				Card c = p.playerHand[i - j];
				p.playerHand.remove_card(i - j);
				discardedDeck.add_card(c);
				++j;
			}
			catch (out_of_range err)
			{
				cout << err.what() << " Try again." << endl;
			}
		}
		else
		{
			continue;
		}
	}
	cout << endl;
	
	return success;
}

//turn method
int FiveCardDraw::turn(Player& p)
{
	size_t t = 0;
	int initialPlayerHandSize = p.playerHand.size();

	while (t < cards_per_hand - initialPlayerHandSize)
	{
		if (mainDeck.size() > 0) {
			p.playerHand << mainDeck;
		}
		else if (discardedDeck.size() > 0) {
			p.playerHand << discardedDeck;
		}
		else {
			return no_cards_left;
		}

		++t;
	}

	return success;
}

//after_turn method
int FiveCardDraw::after_turn(Player& p)
{
	cout << "Player's name: " << p.playerName << ", Hand content: " << p.playerHand << ", folded: " << (p.isFold ? "True" : "False")  <<endl;
	return success;
}

//before_round method
int FiveCardDraw::before_round()
{
	mainDeck.shuffle();

	if (dealer == playersVec.size() - 1) // if dealer is at last position. 
	{
		const int startIndex = 0;
		const int endIndex = playersVec.size() - 1;

		//lab4 part 
		//to join the game, each player should spend a chip into the pot. 
		//so pot should be incremented by 1. 
		for (auto player : playersVec)
		{
			--player->chip;
			++pot;
		}
		//while loop with a condition that looks for both values are 5 or not. If 5, then done. 
		//since we want to make sure each player has received five cards. 
		size_t eachIndex = 0;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != cards_per_hand || playersVec[endIndex]->playerHand.size() != cards_per_hand)
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck;
			++eachIndex;

		}
		
		// 1st betting phase:
		// reset the records
		foldCounts = 0;
		for (auto p : playersVec)
		{
			p->isFold = false;
			cout << p->playerName << ": " << p->playerHand;
		}
		betting();

		if (playersVec.size() - foldCounts >= 2)
		{
			for (auto p : playersVec)
			{
				if (!p->isFold)
				{
					before_turn(*p);
				}
			}
		}
		return success;
	}
	else // if deal is not at last position. i.e among 3 players, if second player is a dealer, then first player's index is the starting point. 
	{
		const int startIndex = dealer + 1;
		const int endIndex = playersVec.size() - 1;

		//lab4 part 
		//to join the game, each player should spend a chip into the pot. 
		//so pot should be incremented by 1. 
		for (auto player : playersVec)
		{
			--player->chip;
			++pot;
		}

		size_t eachIndex = startIndex;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != cards_per_hand || playersVec[dealer]->playerHand.size() != cards_per_hand)
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck; // to iterate each player in the playersvec, used % playersVec.size()
			++eachIndex;

		}
		
		// 1st betting phase:
		foldCounts = 0;
		for (auto p : playersVec)
		{
		p->isFold = false;
		cout << p->playerName << ": " << p->playerHand;
		}
		betting();

		// players discard cards staring at the dealer
		if (playersVec.size() - foldCounts >= 2)
		{
			for (size_t i = startIndex; i < playersVec.size(); ++i)
			{
				if (!playersVec[i]->isFold)
				{
					before_turn(*playersVec[i]);
				}
			}
			for (auto j = 0; j < startIndex; ++j)
			{
				if (!playersVec[j]->isFold)
					before_turn(*playersVec[j]);
			}
		}
		

		return success;
	}
}

// round method
int FiveCardDraw::round()
{
	if (dealer == playersVec.size() - 1) // if dealer is at last position. 
	{

		const int startIndex = 0;
		const int endIndex = playersVec.size() - 1;
		if (playersVec.size() - foldCounts >= 2)
		{
			for (size_t i = startIndex; i < playersVec.size(); ++i)
			{
				if (!playersVec[i]->isFold)
				{
					int turnResult = turn(*playersVec[i]);
					if (turnResult != 0)
					{
						return turnResult;
					}
					after_turn(*playersVec[i]);
				}
			}
			betting();
		}
		return success;
	}
	else
	{
		const int startIndex = dealer + 1;
		const int endIndex = playersVec.size() - 1;
		if (playersVec.size() - foldCounts >= 2)
		{
			for (size_t i = 0; i < playersVec.size(); ++i)
			{
				int index = (i + startIndex) % playersVec.size();
				if (!playersVec[index]->isFold)
				{ 
					int turnResult = turn(*playersVec[index]);
					if (turnResult != 0)
					{
						return turnResult;
					}
					after_turn(*playersVec[index]);
				}
			}
			betting();
		}
		return success;
	}
}
