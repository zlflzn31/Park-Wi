#include "stdafx.h"
#include "Game.h"
#include<iostream>
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

// start_game method. NOT COMPLETED
void start_game(const string& s) {
	if (pGame != nullptr) {
		throw 
	}
}
//NOT COMPLETED

//vector<shared_ptr<Player>> players;
ErrorControl Game::add_player(const string & givenPlayer)
{

	if (// there is a same name. 
	    )
	{
		throw runtime_error("Error: already_playing");
	}
	else // if there is no same name. we have to add. 
	{
		// I have no idea from here ): 
		Player addedPlayer = Player(givenPlayer); 

	}
	//I feel that we have to iterate all the vector<player> However, we have vector of pointers, so it seems a bit challenging to do so. 
	for (vector<Player> iterator it = players.begin(); it != players.end(); ++it)
	{

	}
	return ErrorControl();
}

shared_ptr<Player> Game::find_player(const string &)
{
	return shared_ptr<Player>();
}
