/*
The name of this file: FiveCardDraw.cpp
Author: Hong Wi, hwi@wustl.edu, Jongwhan Park, jongwhan@wustl.edu
This is the source file for the FiveCardDraw class, which contains its constructor, turn, and round methods.
*/

#include "stdafx.h"
#include "FiveCardDraw.h"
#include "PokerGame.h"
#include <algorithm>

// FiveCardDraw constructor
FiveCardDraw::FiveCardDraw() : PokerGame()
{
	cards_per_hand = 5;
}

//before_turn method
int FiveCardDraw::before_turn(Player& p)
{
	cout << "Player's name: " << p.playerName << ", Hand content:" << p.playerHand << endl;

	vector<size_t> indices;
	bool valid_index = true;
	do {
		cout << "If any, please type valid indices of Cards which you would like to discard." << endl;
		string input;
		size_t index;
		if (getline(cin, input)) {
			valid_index = true;
			indices.clear();
			stringstream ss(input);
			while (ss >> index) {
				indices.push_back(index);
				if (index >= cards_per_hand) {
					valid_index = false;
				}
			}
		}
	} while (indices.size() > static_cast<size_t>(p.playerHand.size()) || valid_index == false);

	sort(indices.begin(), indices.end());
	reverse(indices.begin(), indices.end());

	for (size_t i = 0; i < indices.size(); ++i) {
		discardedDeck.add_card(p.playerHand[indices[i]]);
		p.playerHand.remove_card(indices[i]);
	}
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
	cout << "Player's name: " << p.playerName << ", Hand content: " << p.playerHand << endl;
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
		//while loop with a condition that looks for both values are 5 or not. If 5, then done. 
		//since we want to make sure each player has received five cards. 
		size_t eachIndex = 0;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != cards_per_hand || playersVec[endIndex]->playerHand.size() != cards_per_hand)
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck;
			++eachIndex;

		}
		//this for loop calls before_turn. 
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{
			before_turn(*playersVec[i]);
			cout << "current discard deck : " << discardedDeck << endl;
		}
		cout << "current mainDeck : " << mainDeck << endl;
		return success;
	}
	else // if deal is not at last position. i.e among 3 players, if second player is a dealer, then first player's index is the starting point. 
	{
		const int startIndex = dealer + 1;
		const int endIndex = playersVec.size() - 1;
		size_t eachIndex = startIndex;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != cards_per_hand || playersVec[dealer]->playerHand.size() != cards_per_hand)
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck; // to iterate each player in the playersvec, used % playersVec.size()
			++eachIndex;

		}
		//this for loop calls before_turn. 
		// since startIndex can happen at the middle, 
		//playersvec.size() + (starIndex % playersVec.size()) will iterate indexes that are less than startPoint. 
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{
			before_turn(*playersVec[i]);
		}
		for (size_t j = 0; j < startIndex; ++j)
		{
			before_turn(*playersVec[j]);
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
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{


			int turnResult = turn(*playersVec[i]);
			if (turnResult != 0)
			{
				return turnResult;
			}
			after_turn(*playersVec[i]);
		}
		return success;
	}
	else
	{
		const int startIndex = dealer + 1;
		const int endIndex = playersVec.size() - 1;
		for (size_t i = 0; i < playersVec.size(); ++i)
		{
			int index = (i + startIndex) % playersVec.size();
			int turnResult = turn(*playersVec[index]);
			if (turnResult != 0)
			{
				return turnResult;
			}
			after_turn(*playersVec[index]);
		}
		return success;
	}
}