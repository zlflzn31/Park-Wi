#include "stdafx.h"
#include "PokerGame.h"
#include "GameExceptions.h"

PokerGame::PokerGame()
{
	dealer = 0;
	discardedDeck = Deck();
	foldCounts = 0;
	mainDeck = Deck();
	vector<Card> cards = vector<Card>();
	int suitNum = 4;
	int rankNum = 13;
	for (int i = 0; i < suitNum; ++i)
	{
		for (int j = 0; j < rankNum; ++j)
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

void PokerGame::betting()
{	// isBet: is true if someone bets in a rotation
	// isRaise: is true if someone raises in a rotation
	// bet: the highest bet in the phase
	bool betted = false, raised = false;
	unsigned int betValue = 0;

	// reset all players' record
	for (size_t i = 0; i < playersVec.size(); ++i)
	{
		playersVec[i]->betCount = 0;
	}
	// I just found that this for loop seems much easier to implement, since I  dont have to write, 
	// playersVec[i] for every p. 
	for (auto p : playersVec)
	{
		if (!p->isFold)   // if the player is in the round
		{
			cout << endl << p->playerName << ": ";
			if (p->noChip())
			{
				cout << "No chips. You have to stay until the game ends." << endl;
			}
			else
			{
				cout << "Which action will you talk ? Enter : ";
				if (!betted)  // no one has bet, so the beginning stage.
				{
					cout << " bet_one_chip, " << "bet_two_chips, " << ", or check. " << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "bet_one_chip")
						{
							betValue = 1;
							cout << "You have betted: " << betValue << " times. " << endl
								<< endl;
							betted = true;
							p->chip = p->chip - betValue;
							p->betCount = betValue;
							break;
						}
						else if (ans == "bet_two_chips")
						{
							if (p->chip > 1)
							{
								betValue = 2;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								betted = true;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is 1. You can either bet one chip or check." << endl;
							}
						}
						else if (ans == "check")
						{
							cout << "You have betted: " << betValue << " times. " << endl
								<< endl;
							break;
						}
						else
						{
							cout << "ENTER A VAILD OPTION. " << endl;
						}
					}
				}
				else // if betted. 
				{
					cout << " raise_one_chip, " << "raise_two_chips, " << "call, " << "or fold." << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "raise_one_chip")
						{
							if (p->chip > betValue)
							{
								betValue = betValue + 1;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								raised = true;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "raise_two_chips")
						{
							if (p->chip > betValue + 1)
							{
								betValue = betValue + 2;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								raised = true;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "call")
						{
							if (p->chip >= betValue)
							{
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You will bet all of your chips to the pot."
									<< "You will stay until the round is over." << endl;
								p->chip = 0;
								p->betCount = betValue;
								break;
							}
						}
						else if (ans == "fold")
						{
							cout << "You have betted: " << betValue << " times. " << endl
								<< endl;
							for (int i = 0; i < p->playerHand.size(); ++i)
							{
								Card c = p->playerHand[i];
								p->playerHand.remove_card(i);
								discardedDeck.add_card(c);
							}
							p->isFold = true;
							++foldCounts;
							pot = pot + p->betCount;
							p->betCount = 0;
							break;
						}
						else
						{
							cout << "ENTER A VAILD OPTION. " << endl;
						}
					}
				}
			}
		}
	}

	if (betted)  //if betted previously 
	{
		for (auto p : playersVec)
		{
			if ((!p->isFold) && (p->betCount < betValue))
			{
				cout << endl << p->playerName;
				if (p->noChip())
				{
					cout << ": No chips. You have to stay until the game ends." << endl;
				}
				else
				{
					cout << ": raise_one_chip, " << "raise_two_chips, " << "call, " << "or fold." << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "raise_one_chip")
						{
							if (p->chip > betValue)
							{
								betValue = betValue + 1;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "raise_2_chips")
						{
							if (p->chip > betValue + 1)
							{
								betValue = betValue + 2;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "call")
						{
							if (p->chip >= betValue)
							{
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You will bet all of your chips to the pot."
									<< "You will stay until the round is over." << endl;
								p->chip = 0;
								p->betCount = betValue;
								break;
							}
						}
						else if (ans == "fold")
						{
							cout << "You have betted: " << betValue << " times. " << endl
								<< endl;
							for (int i = 0; i < p->playerHand.size(); ++i)
							{

								Card c = p->playerHand[i];
								p->playerHand.remove_card(i);
								discardedDeck.add_card(c);
							}
							p->isFold = true;
							++foldCounts;
							pot = pot + p->betCount;
							p->betCount = 0;
							break;
						}
						else
						{
							cout << "PLEASE ENTER A VALID OPTION" << endl;
						}
					}
				}
			}
		}
	}






	while (raised)  // if raised previously 
	{
		raised = false;
		for (auto p : playersVec)
		{
			if ((!p->isFold) && (p->betCount < betValue))
			{
				cout << p->playerName << endl;
				if (p->noChip())
				{
					cout << ": No chips. You have to stay until the game ends." << endl;
				}
				else
				{
					cout << ": raise_one_chip, " << "raise_two_chips, " << "call, " << "or fold." << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "raise_1_chip")
						{
							if (p->chip > betValue)
							{
								betValue = betValue + 1;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "raise_2_chips")
						{
							if (p->chip > betValue + 1)
							{
								betValue = betValue + 2;
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "call")
						{
							if (p->chip >= betValue)
							{
								cout << "You have betted: " << betValue << " times. " << endl
									<< endl;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								break;
							}
							else
							{
								cout << "Your current chip value is : " << p->chip << ". You will bet all of your chips to the pot."
									<< "You will stay until the round is over." << endl;
								p->chip = 0;
								p->betCount = betValue;
								break;
							}
						}
						else if (ans == "fold")
						{
							cout << "Cumulative bet is now " << betValue << endl;
							for (int i = 0; i < p->playerHand.size(); ++i)
							{
								Card c = p->playerHand[i];
								p->playerHand.remove_card(i);
								discardedDeck.add_card(c);
							}
							p->isFold = true;
							++foldCounts;
							pot = pot + p->betCount;
							p->betCount = 0;
							break;
						}
						else
						{
							cout << "PLEASE ENTER A VALID OPTION." << endl;
						}
					}
				}
			}
		}
	}
	// after the betting phase, push all the remaining players' bets into the pot
	for (auto p : playersVec)
	{
		if (!p->isFold)
		{
			pot = pot + p->betCount;
		}
	}
}




//after_round method
int PokerGame::after_round()
{

	vector<shared_ptr<Player>> temp;
	for (size_t i = 0; i < playersVec.size(); ++i)
	{
		if (!temp[i]->isFold)
		{
			temp.push_back(playersVec[i]);
		}
	}
	sort(temp.begin(), temp.end(), [&](shared_ptr<Player>& p1, shared_ptr<Player>& p2) { return poker_rank(p1->playerHand, p2->playerHand); });

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
		cout << "player name: " << temp[i]->playerName << "\nnumber of wins: " << temp[i]->winCounts << "\nnumber of losses: " << temp[i]->lossCounts << "\nnumber of chips: " << temp[i]->chip << "\nplayer's hand: " << temp[i]->playerHand << endl;

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

	//lab4: store a player's results to a text file
	storeGame();

	// lab4. for players that lost all their chips, make them decide between resetting their chip count and quitting the game
	busted();


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
	// if one player exists in the game, then end the game. 
	if (playersVec.size() == 1)
	{
		Game::stop_game();
	}

	return 0;
}