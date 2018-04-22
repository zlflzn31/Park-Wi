#include "stdafx.h"
#include "FiveCardDraw.h"
#include "PokerGame.h"
#include <algorithm>

PokerGame::PokerGame()
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
int PokerGame::after_round()
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

	//lab4: store a player's results to a text file
	storeGame();

	// lab4. for players that lost all their chips, make them decide between resetting their chip count and quitting the game
	busted();

	//ask the rest of the players whether to leave the game
	string leftPlayerName;
	int indexOfLeftPlayer = -1;
	bool leave;
	do {
		leave = false;
		cout << endl;
		cout << "Is there any player whom you want to leave? If there is not, enter 'no'. 'No', 'NO', 'nO' won't be accepted !  " << endl;

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
			busted(); //lab4: if a player with 0 chips tries to join the game, make him reset or not join
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
