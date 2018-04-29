#pragma once

/*
The name of this file: TexasHoldEm.h
Author: Hong Wi, Jongwhan Park, hwi@wustl.edu, jongwhan@wustl.edu
This header file contains header information about TexasHoldEm class.
*/

#ifndef TEXASHOLDEM_H_
#define TEXASHOLDEM_H_
#include "Deck.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"
#include "PokerGame.h"

class TexasHoldEm : public PokerGame
{
public:
	TexasHoldEm();
	Hand bestFive(const Hand &, const Hand &);
	virtual int before_turn(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
private:
	Hand shared;
};

#endif  //TEXASHOLDEM_H_