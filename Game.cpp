/*
The name of this file : Game.cpp
Author : Hong Wi, hwi@wustl.edu, Jongwhan Park, jongwhan@wustl.edu
This cpp file contains definitions of methods in the Game abstract base class.
It includes methods regarding the actual Game instance (instance(), start_game, stop_game),
the players (add_player, find_player), the turns (before_turn, turn, after_turn),
and the rounds (before_round, round, after_round).
*/

#include "stdafx.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h" //lab4 jongwhan
#include "TexasHoldEm.h" //lab4 jongwhan
#include "GameExceptions.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

shared_ptr<Game> Game::pGame;

// instance method that returns a copy of the static pointer member variable
shared_ptr<Game> Game::instance() {
	if (pGame == nullptr) {
		throw instance_not_available();
	}
	else {
		shared_ptr<Game> ptr = pGame;
		return ptr;
	}
}

// start_game method. changed for lab4 jongwhan
void Game::start_game(const string& s) {
	string f = "FiveCardDraw";
	string g = "SevenCardStud";
	string h = "TexasHoldEm";

	if (pGame != nullptr) { // check if the static pointer member variable is non-singular
		throw game_already_started();
	}
	else if ((s.find(f) == string::npos && s.find(g) == string::npos && s.find(h) == string::npos) 
		|| (s.find(f) != string::npos && s.find(g) != string::npos) || (s.find(f) != string::npos && s.find(h) != string::npos)
		|| (s.find(g) != string::npos && s.find(h) != string::npos)) {
		// check if the string contains "FiveCardDraw" or "SevenCardStud". if it contains none of them or more than one of them, it is an error
		throw unknown_game();
	}
	else if (s.find(g) != string::npos) { // if string contains "SevenCardStud", dynamically allocate an instance of SevenCardStud
		shared_ptr<SevenCardStud> scs = make_shared<SevenCardStud>();
		pGame = scs;
	}
	else if (s.find(h) != string::npos) { // if string contains "TexasHoldEm", dynamically allocate an instance of TexasHoldEm
		shared_ptr<TexasHoldEm> the = make_shared<TexasHoldEm>();
		pGame = the;
	}
	else { // dynamically allocate an instance of FiveCardDraw and store its address in pGame
		shared_ptr<FiveCardDraw> fcd = make_shared<FiveCardDraw>();
		pGame = fcd;
	}
}

// stop_game method
void Game::stop_game() {
	if (pGame == nullptr) { // check if the static pointer member variable is singular
		throw no_game_in_progress();
	}
	pGame = nullptr;
}

int Game::get_num_player() {
	return playersVec.size();
}

//vector<shared_ptr<Player>> players;
ErrorControl Game::add_player(const string & givenPlayer)
{
	for (auto i : playersVec) // this for loop checks if given player's name is same with players' name of the vector. 
	{
		if ((i->playerName) == givenPlayer) // compare playername of each Player of the vector to "given" player's name. 
		{
			throw already_playing();
		}
	}
	shared_ptr<Player> p = make_shared<Player>(Player(givenPlayer));
	playersVec.push_back(p);
	return success;
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

int Game::busted()
{
	for (size_t i = 0; i < playersVec.size(); ++i) {
		if (playersVec[i]->noChip()) { // returns true if no chip ! 
			char c;
			do {
				cout << "Please reset your chip count to keep playing. Otherwise, you must quit. Please enter 'r' or 'q'." << endl;
				cin >> c;
				if (c == 'r')
				{
					playersVec[i].reset();
				}
				if (c == 'q')
				{
					ofstream ofs(playersVec[i]->playerName + ".txt");
					ofs << playersVec[i]->playerName << " " << playersVec[i]->winCounts << playersVec[i]->lossCounts << playersVec[i]->chip;
					ofs.close();
					playersVec.erase(playersVec.begin() + i);
				}
			} while (c != 'r' || c != 'q');
		}
		else // even though he or she has no chips, she or he can still leave. 
		{
			char c;
			do
			{
				cout << "You still have chips, but you can leave if you want to. Enter 'q' to leave. Otherwise, enter anything except 'q'." << endl;
				cin >> c;
				if (c == 'q')
				{
					ofstream ofs(playersVec[i]->playerName + ".txt");
					ofs << playersVec[i]->playerName << " " << playersVec[i]->winCounts << playersVec[i]->lossCounts << playersVec[i]->chip;
					ofs.close();
					playersVec.erase(playersVec.begin() + i);
				}
			} while (c != 'q');
		}
	}
	return success;
}

int Game::storeGame()
{
	auto numPlayers = playersVec.size();
	ofstream file;

	for (size_t i = 0; i < numPlayers; i++) {
		string name = playersVec[i]->playerName;
		file.close();
		file.open(name + ".txt");
		file << playersVec[i]->playerName << endl;
		file << playersVec[i]->winCounts << endl;
		file << playersVec[i]->lossCounts << endl;
		file << playersVec[i]->chip << endl;
	}
	return success;
}