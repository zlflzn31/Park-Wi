#pragma once
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

	Player(char*);

};
ostream& operator<<(ostream&, const Player&); // non-member insertion operator << 

#endif  //PLAYER_H_