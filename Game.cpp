#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// instance method that returns a copy of the static pointer member variable
shared_ptr<Game> Game::instance() {
	if (pGame == nullptr) {
		throw runtime_error("Error: instance_not_available");
	}
	else {
		shared_ptr<Game> ptr = pGame;
		return pGame;
	}
}

// start_game method
void Game::start_game(const string& s) {
	string f = "FiveCardDraw";
	if (pGame != nullptr) { // check if the static pointer member variable is non-singular
		throw runtime_error("Error: game_already_started");
	}
	else if (s.find(f) == string::npos) { // check if the string contains "FiveCardDraw"
		throw runtime_error("Error: unknown_game");
	}
	else { // dynamically allocate an instance of FiveCardDraw and store its address in pGame
		shared_ptr<FiveCardDraw> fcd = make_shared<FiveCardDraw>(); 
		pGame = fcd;
	}
}

// stop_game method
void Game::stop_game() {
	if (pGame == nullptr) { // check if the static pointer member variable is singular
		throw runtime_error("Error: no_game_in_progress");
	}
	pGame = nullptr;
}

//vector<shared_ptr<Player>> players;
ErrorControl Game::add_player(const string & givenPlayer)
{
	string playerName = givenPlayer; // name of "given" player's
	//this for loop checks if given player's name is same with players' name of the vector. 
	for (vector<shared_ptr<Player>>::iterator it = playersVec.begin(); it != playersVec.end(); ++it) 
	{
		if ((*it)->playerName == playerName) { // compare playername of each Player of the vector to "given" player's name. 
			throw runtime_error("Error: already_playing");
		}
	} 
	//this below logic push backs the given player's name into the vector of the players. 
	vector<char> playerNameCStyle(playerName.length() + 1);
	strcpy(&playerNameCStyle[0], playerName.c_str());
	char* pnc = &playerNameCStyle[0];
	Player temp(pnc);
	playersVec.push_back(make_shared<Player>(temp));
	return ErrorControl();
}

shared_ptr<Player> Game::find_player(const string & givenPlayer)
{
	//a logic to iterate vector<shared_ptr<Playrer>> in game class. 
	for (vector<shared_ptr<Player>>::iterator it = playersVec.begin(); it != playersVec.end(); ++it) 
	{
		if ((*it)->playerName == givenPlayer) {
			return *it;
		}
	}
	//if no matching, return a singular pointer. So I decided to return nullptr. 
	return nullptr;
}
