/*
The name of this file: lab2.cpp
Author: Hong Wi, hwi@wustl.edu
This file contains main function.
*/

#include "stdafx.h"
#include "verifyCard.h"
#include "Deck.h"
#include "Hand.h"
#include "Game.h"
#include "Player.h"
#include "Hand.h"
#include "FiveCardDraw.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	const int program_name = 0;
	const int game_name = 1;
	const int least_num_players = 2;
	const int least_num_arg = 4;
	const int hands_number = 9;
	const string shuffle = "-shuffle";
	ErrorControl returned;
	
	try
	{
		if (argc < least_num_arg)
		{
			returned = usageMsg(argv[program_name], "The program should be run with the name of a game followed by the names of two or more players.");
			return returned;
		}
		else
		{
			Game::start_game(argv[game_name]);
			shared_ptr<Game> current_game = Game::instance();

			string new_player;

			//add players
			for (int i = 2; i < argc; i++) {
				new_player = argv[i];

				if (new_player == "no" || new_player == "no*") {
					cout << new_player << " is not a valid player name." << endl;
				}
				else {
					current_game->add_player(new_player);
				}
			}

			while(current_game->get_num_player() >= least_num_players)
			{
				current_game->before_round();
				current_game->round();
				current_game->after_round();
			}
			Game::stop_game();
			return success;
		}
	}
	catch (const runtime_error& error) {
		cerr << error.what() << endl;
		return run_time_error;
	}
	catch (...) {
		Game::stop_game();
		return usageMsg(argv[program_name], "Unknown error");
	}
}