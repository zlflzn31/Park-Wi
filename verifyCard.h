#pragma once

/*
The name of this file: verifyCard.h
Author: Hong Wi, hwi@wustl.edu
This header file declares functions and struct
that are needed to parse and print strings of cards from text file.
And for determining the hand rank.
*/


#ifndef VERIFYCARD_H
#define VERIFYCARD_H
#include <vector>

using namespace std;

/*
This struct is created for storing suit and rank value.
*/
struct Card
{
	enum suit { clubs, diamonds, hearts, spades };  //CDHS
	enum rank { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
	rank r;
	suit s;
	bool operator< (const Card &) const;
	//	Card();

};

/*
This enum controls error and success behaviors.
*/
enum ErrorControl {
	success = 0,
	unable_to_open_file = 1,
	command_line_wrong = 2,
	vector_is_empty = 3,
	onlyOne_with_shuffle = 4,
	twoArgs_nonShuffle = 5,
	non_CmdArgs = 6,
	More_than_3Args = 7,
	floated_error = 8,
	wrong_implementation_of_poker_rank = 9,
	no_cards_left = 10
};

/*
This function takes two arguments, (reference of vector<Card> and char*).
char* will be name of text file.
It only parses a line that has five cards at a time. Otherwise, it doesn't parse.
If more than or less than 5 cards, it prints out a warning message and doesn't parse.
If a blank space is given, nothing happens, just skips.
And if no errors happened, it returns "success"
Otherwise, (if file is not open) it returns "unable_to_open_file".

*/
ErrorControl parseFile(vector<Card>&, char *);

/*
This function takes a reference of const vector<Card>,
and prints the parsed cards in the vector.
It returns "success" after it prints everything.
If vector<Card> is empty, then it returns "vector_is_empty".
*/
ErrorControl fileOutput(const vector<Card>&);

/*
This helper method is created as a helper method for fileoutput.
It takes Card struct as an argument.
And it returns nothing.
*/
void printOutput(Card);

/*
This method determines the poker hand rank and prints out it from the given const vector<Card>.
*/
ErrorControl pokerHand(const vector<Card> &);

/*
usageMsg takes a program_name as a parameter and returns nothing.
*/
ErrorControl usageMsg(char*, char*);

#endif /* VERIFYCARD_H */


