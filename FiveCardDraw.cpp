/*
The name of this file: FiveCardDraw.cpp
Author: Hong Wi, hwi@wustl.edu, Jongwhan Park, jongwhan@wustl.edu
This is the source file for the FiveCardDraw class, which contains its constructor, turn, and round methods.
*/

#include "stdafx.h"
#include "FiveCardDraw.h"
#include <algorithm>

// FiveCardDraw constructor
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

//before_turn method
int FiveCardDraw::before_turn(Player& p)
{
	cout << "Player's name: " << p.playerName << ", Hand content:" << p.playerHand << endl;

	vector<size_t> indices;
	const int max_handsize = 5;
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
				if (index >= max_handsize) {
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
	const int maxHandSize = 5;
	int initialPlayerHandSize = p.playerHand.size();

	while (t < maxHandSize - initialPlayerHandSize)
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
		const int max_handsize = 5;
		//while loop with a condition that looks for both values are 5 or not. If 5, then done. 
		//since we want to make sure each player has received five cards. 
		size_t eachIndex = 0;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != max_handsize || playersVec[endIndex]->playerHand.size() != max_handsize)
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
		const int max_handsize = 5;
		size_t eachIndex = startIndex;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != max_handsize || playersVec[dealer]->playerHand.size() != max_handsize)
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
		const int max_handsize = 5;
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
		const int max_handsize = 5;
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

// this is needed to sort in after_round. 
bool poker_rank(const shared_ptr<Player>& p1, const shared_ptr<Player>& p2)
{
	if (p1.get() == NULL) // if p1 is singular, return false. 
	{
		return false;
	}
	else if (p2.get() == NULL)
	{
		return true;
	}
	else
	{
		return poker_rank(p1->playerHand, p2->playerHand);
	}
}

//after_round method
int FiveCardDraw::after_round()
{

	vector<shared_ptr<Player>> temp;
	for (size_t i = 0; i < playersVec.size(); ++i)
	{
		temp.push_back(playersVec[i]);
	}
	sort(temp.begin(), temp.end(), [&](shared_ptr<Player>& p1, shared_ptr<Player>& p2) { return poker_rank(p1, p2); });

	size_t index = 0;
	size_t lastIndex = temp.size() - 1;

	while (temp[index] != temp[lastIndex])
	{
		++temp[index]->lossCounts;
		++index;
	}
	++temp[lastIndex]->winCounts;
	reverse(temp.begin(), temp.end());
	cout << endl;
	for (size_t i = 0; i < temp.size(); ++i)
	{
		cout << "player name: " << temp[i]->playerName << "\nnumber of wins: " << temp[i]->winCounts << "\nnumber of losses: " << temp[i]->lossCounts << "\nplayer's hand: " << temp[i]->playerHand << endl;

	}
	mainDeck.deck.clear();
	discardedDeck.deck.clear();
	for (size_t p = 0; p < playersVec.size(); ++p)
	{
		playersVec[p]->playerHand.hand.clear();
	}
	vector<Card> cardsToMain = vector<Card>();
	int suitNum = 4;
	int rankNum = 13;
	for (int i = 0; i < suitNum; i++)
	{
		for (int j = 0; j < rankNum; j++)
		{
			Card c;
			c.s = static_cast<Card::suit>(i);
			c.r = static_cast<Card::rank>(j);
			mainDeck.add_card(c);
		}
	}

	//ask the rest of the players whether to leave the game
	string leftPlayerName;
	int indexOfLeftPlayer = -1;
	bool leave;
	do {
		leave = false;
		cout << endl;
		cout << "Is ther any player whom you want to leave? If there is not, enter 'no'. 'No', 'NO', 'nO' won't be accepted !  " << endl;

		cout << "Player's name: " << endl;
		cin >> leftPlayerName;
		if (leftPlayerName == "no")
		{
			leave = false;
		}
		else {
			cout << "leave the person!!! " << endl;
			leave = true; // we want someone to leave the game. 
		}
		bool validPlayer = false;
		for (size_t i = 0; i < playersVec.size(); ++i)
		{
			if (leftPlayerName == playersVec[i]->playerName)
			{
				validPlayer = true;
				break;
			}
		}
		if (leave && validPlayer)  // if validPlayer is not true ( meaning that we have an invalid player, so we should skip this part)
		{
			ofstream ofs(leftPlayerName + ".txt");
			ofs << leftPlayerName;
			ofs.close();

			for (size_t i = 0; i < playersVec.size(); ++i)
			{
				if (leftPlayerName == (*playersVec[i]).playerName) {
					indexOfLeftPlayer = i;
				}
			}
			if (indexOfLeftPlayer != -1) {
				playersVec.erase(playersVec.begin() + indexOfLeftPlayer);
			}
		}
		indexOfLeftPlayer = -1;
	} while (leave);

	//ask whether to join the game
	string joiningPlayer;
	bool join = false;
	do {
		cout << endl;
		cout << "Is there any player whom you want to join? Enter 'no' if you don't want. 'NO' 'No' 'nO' won't be accepted! " << endl;
		cout << "Player's name: " << endl;
		cin >> joiningPlayer;
		if (joiningPlayer == "no")
		{
			join = false;
		}
		else {
			join = true;
		}

		if (join)
		{
			add_player(joiningPlayer); //add_player has a logic to check the duplicates. 
		}
	} while (join);
	cout << endl;

	//next dealer ! 
	if (dealer >= playersVec.size() - 1)
	{
		dealer = 0;
	}
	else {
		++dealer;
	}

	return 0;
}
