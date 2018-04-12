#pragma once
#ifndef FiveCardDraw_H_
#define FiveCardDraw_H_

#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "VerifyCard.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <vector> 
#include <string>


class FiveCardDraw : public Game
{
	friend bool poker_rank(const shared_ptr<Player>&, const shared_ptr<Player>&);
protected:
	size_t dealer;
	Deck discardedDeck; // discard deck. 
	Deck mainDeck; // main deck. 
public:
	FiveCardDraw();
	virtual int before_turn(Player&);
	virtual int turn(Player&);
	virtual int after_turn(Player&);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

bool poker_rank(const shared_ptr<Player>&, const shared_ptr<Player>&);

#endif  //FiveCardDraw_H_
