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
			c.r = static_cast<Card::rank>(j); 
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
{	// betted: is true if someone bets in a rotation
	// raised: is true if someone raises in a rotation
	// betValue: the highest bet in the phase
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
		cout << "================================================================================" << endl;
		if (!p->isFold)   // if the player is in the round
		{
			cout << endl << p->playerName << ": ";
			if (p->noChip())
			{
				cout << "No chips. You have to stay until the game ends." << endl;
			}
			else
			{
				cout << "Which action will you take ? Enter : ";
				if (!betted)  // no one has betted yet, so the beginning stage.
				{
					cout << " bet_one_chip, bet_two_chips, or check. PLEASE TYPE ONCE. We don't accept anything other than that!! " << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "bet_one_chip")
						{
							cout << endl;
							cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
							cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
							betValue = 1;
							cout << "current bet value: " << betValue << "." << endl
							<< endl;
							betted = true;
							p->chip = p->chip - betValue;
							p->betCount = betValue;
							cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
							cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
							cout << endl;
							break;
						}
						else if (ans == "bet_two_chips")
						{
							if (p->chip > 1)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = 2;
								cout << "current bet value: " << betValue << "." << endl
									<< endl;
								betted = true;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								cout << "current pot is : " << pot << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is 1. You can either bet one chip or check." << endl;
							}
						}
						else if (ans == "check")
						{
							cout << endl;
							cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
							cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
							cout << "current bet value: " << betValue << "." << endl
							<< endl;
							cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
							cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
							cout << endl;
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
					cout << " raise_one_chip, raise_two_chips, call, or fold. PLEASE TYPE ONCE. We don't accept anything other than that!! " << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "raise_one_chip")
						{
							if (p->chip > betValue)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = betValue + 1;
								cout << "current bet value: " << betValue << "." << endl
									<< endl;
								raised = true;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "raise_two_chips")
						{
							cout << endl;
							if (p->chip > betValue + 1)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = betValue + 2;
								cout << "current bet value: " << betValue << "." << endl
									<< endl;
								raised = true;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "call")
						{
							cout << endl;
							if (p->chip >= betValue)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								p->chip = p->chip - betValue;
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << endl;
								cout << "Your current chip amount is : " << p->chip << ". You will bet all of your chips to the pot."
								<< "You will stay until the round is over." << endl;
								p->chip = 0;
								p->betCount = betValue;
								cout << endl;
								break;
							}
						}
						else if (ans == "fold")
						{
							cout << endl;
							cout << p->playerName << " has folded ! " << endl
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
							cout << endl;
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
	cout << "================================================================================" << endl;
	for (auto p : playersVec)
	{
		cout << p->playerName << "'s current bet count = " << p->betCount << " and total chips == " << p->chip << endl;
	}
	cout << "================================================================================" << endl;
	if (betted)  //if betted previously 
	{
		for (auto p : playersVec)
		{
			cout << "================================================================================" << endl;
			if ((!p->isFold) && (p->betCount < betValue))
			{
				cout << endl << p->playerName;
				if (p->noChip())
				{
					cout << ": No chips. You have to stay until the game ends." << endl;
				}
				else
				{
					cout << ": raise_one_chip, raise_two_chips, call, or fold. PLEASE TYPE ONCE. We don't accept anything other than that!! " << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "raise_one_chip")
						{
							if (p->chip > betValue)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = betValue + 1;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "raise_two_chips")
						{
							if (p->chip > betValue + 1)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = betValue + 2;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet: " << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "call")
						{
							if (p->chip >= betValue)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << endl;
								cout << "Your current chip amount is : " << p->chip << ". You will bet all of your chips to the pot."
								<< "You will stay until the round is over." << endl;
								p->chip = 0;
								p->betCount = betValue;
								cout << endl;
								break;
							}
						}
						else if (ans == "fold")
						{
							cout << endl;
							cout << p->playerName << " has folded ! " << endl
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
							cout << endl;
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
		cout << "================================================================================" << endl;
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
					cout << ": raise_one_chip,raise_two_chips,call, or fold. PLEASE TYPE ONCE. We don't accept anything other than that!! " << endl;
					string ans;
					while (cin >> ans)
					{
						if (ans == "raise_one_chip")
						{

							if (p->chip > betValue)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = betValue + 1;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "raise_two_chips")
						{
							if (p->chip > betValue + 1)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								betValue = betValue + 2;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								raised = true;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You mat try other action." << endl;
							}
						}
						else if (ans == "call")
						{
							if (p->chip >= betValue)
							{
								cout << endl;
								cout << p->playerName << "'s current chips before his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount before his bet." << p->betCount << endl;
								cout << "current bet value: " << betValue << "." << endl
								<< endl;
								p->chip = p->chip - (betValue - p->betCount);
								p->betCount = betValue;
								cout << p->playerName << "'s current chips after his bet: " << p->chip << endl;
								cout << p->playerName << "'s current betCount after his bet." << p->betCount << endl;
								cout << endl;

								break;
							}
							else
							{
								cout << "Your current chip amount is : " << p->chip << ". You will bet all of your chips to the pot."
									<< "You will stay until the round is over." << endl;
								p->chip = 0;
								p->betCount = betValue;
								cout << endl;
								cout << endl;

								break;
							}
						}
						else if (ans == "fold")
						{
							cout << endl;
							cout << p->playerName << " has folded ! " << endl
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
							cout << endl;
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
	for (auto p : playersVec)
	{
		if (!p->isFold)
		{
			pot = pot + p->betCount;
		}
	}
	return;
}




//after_round method
int PokerGame::after_round()
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
		rank_hand(temp[i]->playerHand);
	}
	sort(temp.rbegin(), temp.rend(), [&](shared_ptr<Player>& p1, shared_ptr<Player>& p2) { return poker_rank(p1->playerHand, p2->playerHand); });

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
		for (int j = 0; j < rankNum; ++j)
		{
	{
			Card c;
			c.s = static_cast<Card::suit>(i);
			c.r = static_cast<Card::rank>(j);
			mainDeck.add_card(c);
		}
	}
	cout << endl;
	storeGame(); 	//Store a player's results to a text file, we store every players' information in after round. 
					//Because even though game is ended automatically, we want to save their information. 

	busted(); 	// For players that lost all their chips, make them decide between resetting their chip count and quitting the game
	leave();	// After players who have no chips decide to reset their chips, then I ask all players if they want to leave. 
				// Since players with chips also have decision to leave the game, we implemented like this way. 

	if (playersVec.size() == 1)
	{
		throw only_one_player();
	}
	if (playersVec.size() == 0)
	{
		throw no_player();
	}

	//ask whether to join the game
	string joiningPlayer;
	bool join = false;
	do 
	{
		cout << endl;
		cout << "Is there any player whom you want to join? Enter 'no' if you don't want. 'NO' 'No' 'nO' won't be accepted! " << endl;
		cout << "Player's name: " << endl;
		cin >> joiningPlayer;
		if (joiningPlayer == "no")
		{
			join = false;
		}
		else 
		{
			join = true;
		}
		cout << endl;

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
	else 
	{
		++dealer;
	}
	pot = 0; //reset pot for next game. 

	return 0;
}



