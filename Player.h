#pragma once

/*
The name of this file: Player.h
Author: Hong Wi, Jongwhan Park, hwi@wustl.edu, jongwhan@wustl.edu
This header file contains header information about Player struct.
This includes the constructor, and win and loss counts of each Player.
*/

#ifndef PLAYER_H_
#define PLAYER_H_


#include "VerifyCard.h"
#include "Hand.h"
#include "Deck.h"

struct Player
{

	string playerName;
	Hand playerHand;

	unsigned int winCounts;
	unsigned int lossCounts;
	unsigned int chip;
	//lab4 
	bool isFold;
	unsigned int betCount;
	Player(string);
	int resetChip();
	bool noChip();
};
ostream& operator<<(ostream&, const Player&); // non-member insertion operator << 

#endif  //PLAYER_H_