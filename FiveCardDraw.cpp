#include "stdafx.h"
#include "FiveCardDraw.h"
#include <algorithm>

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
	if (dealer == playersVec.size() - 1) // if dealer is at last position. 
	{
		const int startIndex = 0;
		const int endIndex = playersVec.size() - 1;
		const int max_handsize = 5;
		//while loop with a condition that looks for both values are 5 or not. If 5, then done. 
		//since we want to make sure each player has received five cards. 
		size_t eachIndex = 0;
		//this while loop deals one card from deck to each player. 
		while (playersVec[startIndex]->playerHand.size() != max_handsize && playersVec[endIndex]->playerHand.size() != max_handsize)
		{
			playersVec[eachIndex % playersVec.size()]->playerHand << mainDeck;
			++eachIndex;
		}
		//this for loop calls before_turn. 
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{
			before_turn(*playersVec[i]);
			//return 0, if success. 
		}
		return success;
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
		for (size_t i = startIndex; i < playersVec.size(); ++i)
		{
			int turnResult = turn(*playersVec[i]);
			if (turnResult != 0)
			{
				return turnResult;
			}
			after_turn(*playersVec[i]);
			//at each player, call turn and after_turn. 
			// if any turn method returns a non-zero value, then immediately return it.
			//return 0, if success. 
		}
		for (size_t j = 0; j < startIndex; ++j)
		{
			int turnResult = turn(*playersVec[j]);
			if (turnResult != 0)
			{
				return turnResult;
			}
			after_turn(*playersVec[j]);
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

int FiveCardDraw::after_round()
{
	vector<shared_ptr<Player>> temp;
	for (size_t i = 0; i < playersVec.size(); ++i)
	{
		temp.push_back(playersVec[i]);
	}
	sort(temp.begin(), temp.end(), [&](shared_ptr<Player>& p1, shared_ptr<Player>& p2) { return poker_rank(p1, p2); });

	size_t index = 0;
	while (temp[index] < temp[index + 1]) // if temp[index] >= temp[index+1] meaning that, temp[index] is the loser. 
	{
		++temp[index]->lossCounts;
		++index;
	}
	for (size_t i = index; i < temp.size(); ++i)// So from the index to temp.size() (exclusive), they are the winners. 
	{
		++temp[i]->winCounts;
	}

	cout << endl;
	for (size_t i = temp.size() - 1; i >= 0; --i) // print out from highest to lowest. and 0 index is the lowest. 
	{
		cout << "player name: " << temp[i]->playerName << "number of wins: " << temp[i]->winCounts << "number of losses: " << temp[i]->lossCounts << "player's hand: " << temp[i]->playerHand << endl;
	}

	for (size_t p = 0; p < playersVec.size(); ++p) // move all players cards to main deck. 
	{
		for (size_t h = 0; h < playersVec[p]->playerHand.size(); ++h)
		{
			mainDeck.add_card(playersVec[p]->playerHand[h]); // add card from player's hand at position h
			playersVec[p]->playerHand.remove_card(h); // and remove the card of the hand at position h. 
		}
	}
	Hand discardDeckHolder;
	for (size_t dh = 0; dh < discardDeckHolder.size(); ++dh)
	{
		mainDeck.add_card(discardDeckHolder[dh]);
		discardDeckHolder.remove_card(dh);
	}


	//ask the rest of the players whether to leave the game

	string leftPlayerName;
	string playerTempHolder;
	int indexOfLeftPlayer = -1;
	bool leave;

	do {
		cout << endl;
		cout << "Is ther any player whom you want to leave? If there is not, enter 'no'. 'No', 'NO', 'nO' won't be accepted !  " << endl;

		cout << "Player's name: " << endl;
		cin >> leftPlayerName;
		playerTempHolder = leftPlayerName;

		if (playerTempHolder.find("no") != string::npos && playerTempHolder.length() == 2) {
			leave = false; // meaning that no one is leaving, so done with this do-while loop. 
		}
		else {
			leave = true; // we want someone to leave the game. 
		}
		bool validPlayer = true;
		for (size_t i = 0; i < playersVec.size(); ++i)
		{
			if (leftPlayerName != playersVec[i]->playerName)
			{
				validPlayer = false;
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
	string joiningPlayerTempHolder;
	bool join = false;
	do {
		cout << endl;
		cout << "Is there any player whom you want to join? Enter 'no' if you don't want. 'NO' 'No' 'nO' won't be accepted! " << endl;
		cout << "Player's name: " << endl;
		cin >> joiningPlayer;
		joiningPlayerTempHolder = joiningPlayer;
		if (joiningPlayerTempHolder.find("no") != string::npos && joiningPlayerTempHolder.length() == 2) {
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