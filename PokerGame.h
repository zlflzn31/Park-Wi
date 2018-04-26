#pragma once

#ifndef PokerGame_H_
#define PokerGame_H_

#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "VerifyCard.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <vector> 
#include <string>
#include <fstream>
#include <algorithm>

class PokerGame : public Game
{
	friend bool poker_rank(const shared_ptr<Player>&, const shared_ptr<Player>&);

public:
	PokerGame();
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round();
protected:
	size_t cards_per_hand;
	size_t dealer;
	Deck discardedDeck; // discard deck. 
	Deck mainDeck; // main deck. 
	unsigned int foldCounts;  // numOfFold: number of players who fold
	void betting();
	
};

bool poker_rank(const shared_ptr<Player>&, const shared_ptr<Player>&);

#endif  //PokerGame_H_
