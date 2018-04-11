#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include <string>
#include <mutex>
#include "Game.h"


using namespace std;
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
