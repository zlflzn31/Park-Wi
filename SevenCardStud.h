#pragma once

/*
The name of this file: SevenCardStud.h
Author: Hong Wi, Jongwhan Park, hwi@wustl.edu, jongwhan@wustl.edu
This header file contains header information about SevenCardStud class.
*/

#ifndef SEVENCARDSTUD_H_
#define SEVENCARDSTUD_H_
#include "Deck.h"
#include "Game.h"
#include "Hand.h"
#include "Player.h"
#include "PokerGame.h"

class SevenCardStud : public PokerGame
{
public:
	SevenCardStud();
	Hand bestFive(const Hand &);
	virtual int before_turn(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

#endif  //SEVENCARDSTUD_H_