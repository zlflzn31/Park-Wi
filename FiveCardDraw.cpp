/*
The name of this file: FiveCardDraw.cpp
Author: Hong Wi, hwi@wustl.edu, Jongwhan Park, jongwhan@wustl.edu
This is the source file for the FiveCardDraw class, which contains its constructor, turn, and round methods.
FiveCardDraw's behavior is implemented by this class and pokergame class. 
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
	cout << "Enter the positions of the card that you want to discard. From 0 ~ 4. " << endl;
	cout << "You can discard multiple cards. Seperate the indices in between with 'space'. " << endl;
	cout << "For any player after the 'first' one, you have to PRESS ENTER ONCE!! and then type the indices you want to discard. \n";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string line, s;
	vector<int> v;
	getline(cin, line);
	stringstream iss(line);
	while (iss >> s) {
		if (s == "0" || s == "1" || s == "2" || s == "3" || s == "4") {
			v.push_back(stoi(s));
		}
	}
	sort(v.rbegin(), v.rend());

	for (size_t i = 0; i < v.size(); ++i) {
		Card c = p.playerHand[i];
		p.playerHand.remove_card(v[i]);
		discardedDeck.add_card(c);
	}

	return success;
/*	while (cin >> in)
	{
		if (in == "n")
		{
			break;
		}
		else if (in == "0" || in == "1" || in == "2" || in == "3" || in == "4")
		{
			vector<shared_ptr<Player>> temp;
			Card c;
			for (size_t i = 0; i < playersVec.size(); ++i)
			{
					temp.push_back(playersVec[i]);				
					if (temp[i]->playerName == p.playerName)
					{
						c = temp[i]->playerHand[stoi(in)];

					}
			}
			p.playerHand.remove_card( stoi(in) );
			discardedDeck.add_card(c);
			cout << stoi(in) << endl;
		}
		else
		{
			cout << "Please, enter valid strings" << endl;
		}
	}
	return success;*/
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
	cout << "Player's name: " << p.playerName << ", Hand content: " << p.playerHand << ", folded: " << (p.isFold ? "True" : "False") << endl;
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
	cout << "ROUND IS IN ACTION" << endl;
	cout << "***********************************************************" << endl;

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
					cout << " after_turn in round" << endl;
				}
			}
			cout << " before betting in round" << endl;
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
					cout << " after_turn in round" << endl;
				}
			}
			cout << " before betting in round" << endl;
			betting();
		}
		return success;
	}
}
