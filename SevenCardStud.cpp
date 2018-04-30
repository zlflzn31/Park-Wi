#include "stdafx.h"
#include "SevenCardStud.h"
#include "PokerGame.h"
#include "GameExceptions.h"
using namespace std;

SevenCardStud::SevenCardStud() // default constructor
{
}

Hand SevenCardStud::bestFive(const Hand &h) 
{
	vector<Hand> vh;
	
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
	sort(vh.begin(), vh.end(), [](Hand &h1, Hand &h2) { return (rank_hand(h1) > rank_hand(h2)); }); // descending order
	return vh[0];
}

int SevenCardStud::before_turn(Player &p)
{
	return success;
}

int SevenCardStud::turn(Player &p)
{
	return success;
}

int SevenCardStud::after_turn(Player &p)
{
	return success;
}

int SevenCardStud::before_round()
{
	mainDeck.shuffle();
	dealer = 0;
	return success;
}

int SevenCardStud::round()
{
	// number of face down / face up cards that will be dealt in each turn
	const vector<int> faceDown = { 2, 0, 0, 0, 1 }; 
	const vector<int> faceUp = { 1, 1, 1, 1, 0 };

	for (int i = 0; i < 5; ++i) { // for each turn i
		cout << "\nTurn " << (i + 1) << endl;
		for (unsigned int j = 0; j < playersVec.size(); ++j) { // for each player j
			cout << "\nDeal to player " << playersVec[j]->playerName;
			for (auto k = 0; k < faceDown[i] + faceUp[i]; ++k) { // deal cards face down/face up
				playersVec[j]->playerHand << mainDeck;
			}
			cout << "\nPlayer " << playersVec[j]->playerName << "'s hand: " << playersVec[j]->playerHand; // print all of player j's hand
			for (unsigned int l = 0; l < playersVec.size(); ++l) { // for each player l that is not j, print out his hand, except with * for cards that are face down
				if (l != j) {
					string temp;
					for (auto m = 0; m < playersVec[l]->playerHand.size(); ++m) { // print out each card in a player's hand
						if (m == 2 || m == 3 || m == 4 || m == 5) {
							Card c = playersVec[l]->playerHand[m];
							if (c.r == Card::rank::two) { temp += '2'; };
							if (c.r == Card::rank::three) { temp += '3'; };
							if (c.r == Card::rank::four) { temp += '4'; };
							if (c.r == Card::rank::five) { temp += '5'; };
							if (c.r == Card::rank::six) { temp += '6'; };
							if (c.r == Card::rank::seven) { temp += '7'; };
							if (c.r == Card::rank::eight) { temp += '8'; };
							if (c.r == Card::rank::nine) { temp += '9'; };
							if (c.r == Card::rank::ten) { temp += "10"; };
							if (c.r == Card::rank::jack) { temp += 'J'; };
							if (c.r == Card::rank::king) { temp += 'K'; };
							if (c.r == Card::rank::queen) { temp += 'Q'; };
							if (c.r == Card::rank::ace) { temp += 'A'; };
							if (c.s == Card::suit::clubs) { temp += 'C'; };
							if (c.s == Card::suit::spades) { temp += 'S'; };
							if (c.s == Card::suit::hearts) { temp += 'H'; };
							if (c.s == Card::suit::diamonds) { temp += 'D'; };
						}
						else {
							temp += "*";
						}
						temp += " ";
					}
					cout << "Player " << playersVec[l]->playerName << "'s hand: " << temp << endl;
				}
			}
		}
//		betting();
	}
	return success;
}

//after_round method
int SevenCardStud::after_round()
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
		rank_hand(bestFive(temp[i]->playerHand));
	}
	sort(temp.rbegin(), temp.rend(), [&](shared_ptr<Player>& p1, shared_ptr<Player>& p2) { return (rank_hand(bestFive(p1->playerHand)) > rank_hand(bestFive(p2->playerHand))); });

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
//	reverse(temp.begin(), temp.end());
	cout << endl;
	for (size_t i = 0; i < temp.size(); ++i)
	{
		cout << rank_hand(bestFive(temp[i]->playerHand));
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



