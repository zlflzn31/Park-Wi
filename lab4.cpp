/*
The name of this file: lab3.cpp
Author: Hong Wi, hwi@wustl.edu, Jongwhan Park, jongwhan@wustl.edu
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
#include "GameExceptions.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	const int program_name = 0;
	const int game_name = 1;
	const int least_num_players = 1;
	const int least_num_arg = 4;
	const int hands_number = 9;
	const string shuffle = "-shuffle";
	ErrorControl returned;

	if (argc < least_num_arg)
	{
		returned = usageMsg(argv[program_name], "The program should be run with the name of a game followed by the names of two or more players.");
		return returned;
	}

	try
	{
		Game::start_game(argv[game_name]);
	}
	catch (game_already_started)
	{
		cout << "This game already started." << endl;
	}
	catch (unknown_game)
	{
		cout << "This is an unknown game." << endl;
	}

	try
	{
		shared_ptr<Game> current_game = Game::instance();
		string new_player;
		//add players
		for (int i = 2; i < argc; ++i) {
			new_player = argv[i];

			if (new_player == "no" || new_player == "no*") {
				cout << new_player << " is not a valid player name." << endl;
			}
			else {
				try
				{
					current_game->add_player(new_player);
				}
				catch (already_playing)
				{
					cout << "There is a player who is already playing." << endl;
				}
			}
		}
		while (current_game->get_num_player() >= least_num_players)
		{
			// 	ADDED BY HONG 
			cout << "Start Round!" << endl;
			current_game->before_round();
			current_game->round();
			try {
				current_game->after_round();
			}
			catch (only_one_player)
			{
				cout << "There is only one player in the game. The game is ended automatically. Thank you for playing. " << endl;
				return success;
			}
			//
		}
		try
		{
			Game::stop_game();
		}
		catch (no_game_in_progress)
		{
			cout << "No game in progress." << endl;
		}
		cout << "Game ended." << endl;
		return success;
	}
	catch (instance_not_available)
	{
		cout << "Instance is not available." << endl;
	}
}
