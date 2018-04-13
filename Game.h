#pragma once

/*
The name of this file: Game.h
Author: Hong Wi, Jongwhan Park, hwi@wustl.edu, jongwhan@wustl.edu
This header file contains header information about Game class, including all methods concerning turns and rounds.
It also contains start_game and stop_game methods, and an instance method.
*/

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
	int get_num_player();
	virtual int before_turn(Player&) = 0;
	virtual int turn(Player&) = 0;
	virtual int after_turn(Player&) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
};
#endif  //GAME_H_