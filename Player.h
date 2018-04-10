#pragma once

#include "stdafx.h"
#include "VerifyCard.h"
#include "Hand.h"
#include "Deck.h"

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
struct Player
{

	string playerName;
	Hand playerHand;
	
	unsigned int winCounts;
	unsigned int lossCounts;

	Player(char*);

};
ostream& operator<<(ostream&, const Player&); // non-member insertion operator << 