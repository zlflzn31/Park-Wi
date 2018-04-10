/*
The name of this file: lab2.cpp
Author: Hong Wi, hwi@wustl.edu
This file contains main function.
*/

#include "stdafx.h"
#include <vector>
#include "verifyCard.h"
#include "Deck.h"
#include "Hand.h"
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	const int arg_program_name = 0;
	const int arg_one = 1;
	const int arg_two = 2;
	const int arg_three = 3;
	const int hands_number = 9;
	const string shuffle = "-shuffle";
	ErrorControl returned;
	if (argc == arg_one)
	{
		returned = usageMsg(argv[arg_program_name], "no command line arguments");
		returned = ErrorControl::non_CmdArgs;
		return returned;
	}
	else if (argc > arg_three)
	{
		returned = usageMsg(argv[arg_program_name], " too many cmd arguements");
		returned = ErrorControl::More_than_3Args;
		return returned;
	}
	else
	{
		if (argc == arg_two && argv[arg_one] == shuffle)
		{
			returned = usageMsg(argv[arg_program_name], " only one argument with '-suffle' ");
			returned = ErrorControl::onlyOne_with_shuffle;
			return returned;
		}
		else if (argc == arg_three && argv[arg_one] != shuffle && argv[arg_two] != shuffle)
		{
			returned = usageMsg(argv[arg_program_name], "two cmd arguements but no '-shuffle' ");
			returned = ErrorControl::twoArgs_nonShuffle;
			return returned;
		}
		else if (argc == arg_two && argv[arg_one] != shuffle)
		{
			vector<Hand> hands;
			const int file_name_index = 1;
			Deck deck = Deck(argv[file_name_index]); // no shuffle/ 
			//nine empty hand ojbects are pushed back. 
			for (auto i = 0; i < hands_number; ++i)
			{
				hands.push_back(Hand());
			}

			//"deal" one card at a time from deck to each of nine hands using insertion opeartor. 
			for (auto i = 0; i < hands_number; ++i)
			{
				hands[i] << deck;
				hands[i] << deck;
				hands[i] << deck;
				hands[i] << deck;
				hands[i] << deck;
			}
			//printout deck and hand after dealt. 
			cout << "Deck after dealt" << endl;
			cout << deck << endl;
			cout << "Hand after dealt" << endl;
			for (auto i = 0; i < hands_number; ++i)
			{
				cout << "hand" + to_string(i + 1) + "= " << hands[i] << endl;
			}
			//now I do sort part. 
			//by less than operator
			sort(hands.begin(), hands.end());
			cout << "Hands sorted by less than opeartor" << endl;
			for (auto i = 0; i < hands_number; i++)
			{
				cout << "hand" + to_string(i + 1) + "= " << hands[i] << endl;
			}
			//by poker_rank and.
			sort(hands.begin(), hands.end(), poker_rank);
			cout << "Hands sorted by poker-rank operator" << endl;
			for (int i = 0; i < hands_number; i++) {
				cout << "hand" + to_string(i + 1) + "= " << hands[i] << endl;
			}

			returned = success;
			return returned;
		}
		else if ( ( argc == arg_three && argv[arg_one] == shuffle && argv[arg_two] != shuffle ) ||
				  ( argc == arg_three && argv[arg_one] != shuffle && argv[arg_two] == shuffle )
				)
		{
			vector<Hand> hands;
			int file_name_index = 0;
			//check which one is file name. 
			if (argv[arg_one] == shuffle)
			{
				file_name_index = arg_two;
			}
			if (argv[arg_two] == shuffle)
			{
				file_name_index = arg_one;
			}
			Deck deck = Deck(argv[file_name_index]);
			deck.shuffle();
			for (auto i = 0; i < hands_number; ++i)
			{
				hands.push_back(Hand());
			}
			//"deal" one card at a time from deck to each of nine hands using insertion opeartor. 
			for (auto i = 0; i < hands_number; ++i)
			{
				hands[i] << deck;
				hands[i] << deck;
				hands[i] << deck;
				hands[i] << deck;
				hands[i] << deck;
			}
			//printout deck and hand after dealt. 
			cout << "Deck after dealt" << endl;
			cout << deck << endl;
			cout << "Hand after dealt" << endl;
			for (auto i = 0; i < hands_number; ++i)
			{
				cout << "hand" + to_string(i + 1) + "= " << hands[i] << endl;
			}
			//now I do sort part. 
			//by less than operator 
			sort(hands.begin(), hands.end());
			cout << "Hands sorted by less than opeartor" << endl;
			for (auto i = 0; i < hands_number; i++)
			{
				cout << "hand" + to_string(i + 1) + "= " << hands[i] << endl;
			}
			//by poker_rank and.
			sort(hands.begin(), hands.end(), poker_rank);
			cout << "Hands sorted by poker-rank operator" << endl;
			for (int i = 0; i < hands_number; i++) {
				cout << "hand" + to_string(i + 1) + "= " << hands[i] << endl;
			}


			returned = success;
			return returned;
		}
	}
	return ErrorControl::floated_error;
}	