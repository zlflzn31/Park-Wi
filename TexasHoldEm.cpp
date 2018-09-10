#include "stdafx.h"
#include "TexasHoldEm.h"
#include "PokerGame.h"
#include "GameExceptions.h"
using namespace std;


/*
The name of this file : TexasHoldEm.cpp
Author : Hong Wi, hwi@wustl.edu
Jongwhan Park, jongwhan@wustl.edu
This cpp file delas with TexasHoldEm. 
It follows the procedure of a game from PokerGame.cpp. 
After then, everything of this file is to run a TexasHoldEm game on the command prompt.
*/


TexasHoldEm::TexasHoldEm() // default constructor
{
	shared = Hand();
}

Hand TexasHoldEm::bestFive(const Hand &h1, const Hand &h2)
{
	vector<Hand> vh;

	Hand h;
	for (auto i = 0; i < h1.size(); ++i) {
		h.hand.push_back(h1.hand[i]);
	}
	for (auto i = 0; i < h2.size(); ++i) {
		h.hand.push_back(h2.hand[i]);
	}
	// construct a vector with all possible Hands of 5. we do this by excluding 2 cards out of the given 7
	for (int i = 0; i < 7; ++i) {
		for (int j = i + 1; j < 7; ++j) {
			Hand candidate;
			for (int k = 0; k < 7; ++k) {
				if ((k != i) && (k != j)) {
					candidate.hand.push_back(h.hand[k]);
				}
			}
			sort(candidate.hand.begin(), candidate.hand.end());
			rank_hand(candidate);
			vh.push_back(candidate);
		}
	}
	sort(vh.begin(), vh.end(), [](Hand &h1, Hand &h2) { return (rank_hand(h1) > rank_hand(h2)); });
	return vh[0];
}

int TexasHoldEm::before_turn(Player &)
{
	return success;
}

int TexasHoldEm::turn(Player &)
{
	return success;
}

int TexasHoldEm::after_turn(Player &)
{
	return success;
}

int TexasHoldEm::before_round()
{
	mainDeck.shuffle();
	dealer = 0;
	return success;
}

int TexasHoldEm::round()
{
	// turn 1
	cout << "\nTurn 1" << endl;
	for (size_t i = 0; i < playersVec.size(); ++i) {
		cout << "\nDeal to player " << playersVec[i]->playerName;
		playersVec[i]->playerHand << mainDeck;
		playersVec[i]->playerHand << mainDeck;
		cout << "\nPlayer " << playersVec[i]->playerName << "'s hand: " << playersVec[i]->playerHand;
		for (size_t j = 0; j < playersVec.size(); ++j) {
			if (j != i) {
				string temp;
				for (auto k = 0; k < playersVec[j]->playerHand.size(); ++k) {
					temp += "* ";
				}
				cout << "Player " << playersVec[j]->playerName << "'s hand: " << temp << endl;
			}
		}
	}
	cout << "Shared cards: none" << endl;
//	betting();

	//turn 2
	cout << "\nTurn 2" << endl;
	shared << mainDeck;
	shared << mainDeck;
	shared << mainDeck;
	for (size_t i = 0; i < playersVec.size(); ++i) {
		cout << "\nPlayer " << playersVec[i]->playerName << "'s hand: " << playersVec[i]->playerHand;
		for (size_t j = 0; j < playersVec.size(); ++j) {
			if (j != i) {
				string temp;
				for (auto k = 0; k < playersVec[j]->playerHand.size(); ++k) {
					temp += "* ";
				}
				cout << "Player " << playersVec[j]->playerName << "'s hand: " << temp << endl;
			}
		}
	}
	cout << "Shared cards: " << shared;
//	betting();

	//turn 3
	cout << "\nTurn 3" << endl;
	shared << mainDeck;
	for (size_t i = 0; i < playersVec.size(); ++i) {
		cout << "\nPlayer " << playersVec[i]->playerName << "'s hand: " << playersVec[i]->playerHand;
		for (size_t j = 0; j < playersVec.size(); ++j) {
			if (j != i) {
				string temp;
				for (auto k = 0; k < playersVec[j]->playerHand.size(); ++k) {
					temp += "* ";
				}
				cout << "Player " << playersVec[j]->playerName << "'s hand: " << temp << endl;
			}
		}
	}
	cout << "Shared cards: " << shared;
	//	betting();

	//turn 4
	cout << "\nTurn 4" << endl;
	shared << mainDeck;
	for (size_t i = 0; i < playersVec.size(); ++i) {
		cout << "\nPlayer " << playersVec[i]->playerName << "'s hand: " << playersVec[i]->playerHand;
		for (size_t j = 0; j < playersVec.size(); ++j) {
			if (j != i) {
				string temp;
				for (auto k = 0; k < playersVec[j]->playerHand.size(); ++k) {
					temp += "* ";
				}
				cout << "Player " << playersVec[j]->playerName << "'s hand: " << temp << endl;
			}
		}
	}
	cout << "Shared cards: " << shared;
	//	betting();

	return success;
}

int TexasHoldEm::after_round()
{
	vector<shared_ptr<Player>> temp;
	vector<shared_ptr<Player>> foldedTemp;

	for (size_t i = 0; i < playersVec.size(); ++i)
	{
		if (playersVec[i]->isFold == false)
		{
			temp.push_back(playersVec[i]);
		}
		else
		{
			foldedTemp.push_back(playersVec[i]);
		}
	}
	for (size_t i = 0; i < temp.size(); ++i) // determine hand rank of each player
	{
		rank_hand(bestFive(temp[i]->playerHand, shared));
	}
	sort(temp.rbegin(), temp.rend(), [&](shared_ptr<Player>& p1, shared_ptr<Player>& p2) { return (rank_hand(bestFive(p1->playerHand, shared)) > rank_hand(bestFive(p2->playerHand, shared))); });

	size_t index = 0;
	size_t lastIndex = temp.size() - 1;

	while (temp[index] != temp[lastIndex])
	{
		++temp[index]->lossCounts;
		++index;
	}

	++temp[lastIndex]->winCounts;
	// pot will be pushed to the winner 
	for (size_t o = 0; o < playersVec.size(); ++o)
	{
		if (temp[lastIndex]->playerName == playersVec[o]->playerName)
		{
			cout << "current pot value : " << pot << endl;
			playersVec[o]->chip = playersVec[o]->chip + pot;
		}
	}
	cout << temp[lastIndex]->playerName << endl;
	reverse(temp.begin(), temp.end());
	cout << endl;
	for (size_t i = 0; i < temp.size(); ++i)
	{
		cout << "player name: " << temp[i]->playerName << "\nnumber of wins: " << temp[i]->winCounts << "\nnumber of losses: " << temp[i]->lossCounts << "\nnumber of chips: " << temp[i]->chip << "\nplayer's hand: " << temp[i]->playerHand << endl;
	}
	for (size_t i = 0; i < foldedTemp.size(); ++i)
	{
		++foldedTemp[i]->lossCounts;
		cout << "player name: " << foldedTemp[i]->playerName << "\nnumber of wins: " << foldedTemp[i]->winCounts << "\nnumber of losses: " << foldedTemp[i]->lossCounts << "\nnumber of chips: " << foldedTemp[i]->chip << "\nfolded, so hands can't be shown" << endl;

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
	for (int i = 0; i < suitNum; ++i)
	{
		for (int j = 0; j < rankNum; ++j)
		{
			Card c;
			c.s = static_cast<Card::suit>(i);
			c.r = static_cast<Card::rank>(j);
			mainDeck.add_card(c);
		}
	}
	cout << endl;
	//lab4: store a player's results to a text file
	storeGame();

	// lab4. for players that lost all their chips, make them decide between resetting their chip count and quitting the game
	busted();
	if (playersVec.size() == 1)
	{
		throw only_one_player();
	}

	// --------------- THIS BELOW PART SHOULD DEAL WITH THAT 
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
			try
			{
				add_player(joiningPlayer); //add_player has a logic to check the duplicates. 
			}
			catch (already_playing)
			{
				cout << "There is a player who is already in the game." << endl;
			}
			if (playersVec[playersVec.size() - 1]->chip == 0)
			{
				busted(); //lab4: if a player with 0 chips tries to join the game, make him reset or not join
			}
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
