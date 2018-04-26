#pragma once

/*
The name of this file: FiveCardDraw.h
Author: Hong Wi, Jongwhan Park, hwi@wustl.edu, jongwhan@wustl.edu
This header file contains header information about FiveCardDraw class, which inherits the Game class.
*/

#ifndef FiveCardDraw_H_
#define FiveCardDraw_H_

#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "VerifyCard.h"
#include "Game.h"
#include "PokerGame.h"
#include <iostream>
#include <sstream>
#include <vector> 
#include <string>
#include <fstream>
#include <algorithm>

class FiveCardDraw : public PokerGame
{
public:
	FiveCardDraw();
	virtual int before_turn(Player&);
	virtual int turn(Player&);
	virtual int after_turn(Player&);
	virtual int before_round();
	virtual int round();
};

#endif  //FiveCardDraw_H_
