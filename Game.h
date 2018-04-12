#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "VerifyCard.h"
#include <mutex>

using namespace std;
class Deck;
struct Player;
class FiveCardDraw;

class Game {

protected:
	static shared_ptr<Game> pGame;
	Deck mainDeck;
	vector<shared_ptr<Player>> playersVec;

public:
	static shared_ptr<Game> instance();
	static void start_game(const string&);
	static void stop_game();

	ErrorControl add_player(const string&);
	shared_ptr<Player> find_player(const string&);
	virtual int before_turn(Player&) = 0;
	virtual int turn(Player&) = 0;
	virtual int after_turn(Player&) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
};
#endif  //GAME_H_
