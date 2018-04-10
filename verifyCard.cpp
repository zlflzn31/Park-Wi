#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <stdexcept>
#include "VerifyCard.h"
#include "Deck.h"
#include "Hand.h"
/*

The name of this file : verifyCard.cpp
Author : Hong Wi, hwi@wustl.edu

This file implements each function that are declared in header file.
*parsefile function reads input text file(char * str) and parse strings of cards in the file into vec.
For every invalid card input, this function will print out "INVALID CARD FOUND" in the terminal.
If everything is parsed with no error,
then it returns success
Also, if the file is not opened,
then it returns unable_to_open_file

*FileOutput function takes const vector<Card>& vec) and a helper function(printOutput)
print out only vaild cards.
And it returns success.
If the given vector is empty,
then it returns vector_is_empty

*pokerHand function sorts every group of five cards from the vector and determine if its ppoker hand rank.
This function won't encounter any error, since the given vector will always have vaild card inputs.
So, it returns success
*/



using namespace std;

bool Card::operator< (const Card & crs) const
{
	return (r < crs.r) || (r == crs.r && s < crs.s);
};

ErrorControl parseFile(vector<Card>& vec, char * file_name)
{
	ifstream ifs(file_name);
	if (ifs.is_open())
	{
		string line, word;
		while (getline(ifs, line)) // reading a line 
		{
			if (line.empty()) // to skip "blank" lines. 
			{
				continue;
			}
			int checkFive = 0;
			istringstream iss(line);
			istringstream buffer(line);
			vector<Card> temp;
			while (iss >> word)
			{
				if (word == "//")
				{
					break;
				}
				Card c;
				const int zero = 0; //dealing with letter index 
				const int two = 2; // dealing with letter length
				const int three = 3;// dealing with letter length 
				if (word.length() == three)  //first, dealing with 10c, 10d cases. 
				{
					char suitAdded = word.at(2);
					if (word.substr(zero, two) != "10") //checking if the input card's value is 10 or not. 
					{
						cout << "INVALID CARD FOUND" << endl;
						continue; //if the value is not 10, c.r will not be assigned a value. 
					}
					else
					{
						c.r = Card::rank::ten;  //if the value is 10, then we assign c.r card::rank::ten.
					}
					if (suitAdded == 'C' || suitAdded == 'c') { c.s = Card::suit::clubs; }
					else if (suitAdded == 'D' || suitAdded == 'd') { c.s = Card::suit::diamonds; }
					else if (suitAdded == 'H' || suitAdded == 'h') { c.s = Card::suit::hearts; }
					else if (suitAdded == 'S' || suitAdded == 's') { c.s = Card::suit::spades; }
					else
					{
						cout << "INVALID CARD FOUND" << endl;
						continue;
					} //if nothing matches, c.s will not be assigned a value. 
				}//END OF WORD.LENGTH == THREE
				else if (word.length() == two) //dealing with 2c 9d cases. 
				{
					char suitAdded = word.at(1);
					char rankAdded = word.at(0);
					if (rankAdded == '2') { c.r = Card::rank::two; }
					else if (rankAdded == '3') { c.r = Card::rank::three; }
					else if (rankAdded == '4') { c.r = Card::rank::four; }
					else if (rankAdded == '5') { c.r = Card::rank::five; }
					else if (rankAdded == '6') { c.r = Card::rank::six; }
					else if (rankAdded == '7') { c.r = Card::rank::seven; }
					else if (rankAdded == '8') { c.r = Card::rank::eight; }
					else if (rankAdded == '9') { c.r = Card::rank::nine; }
					else if (rankAdded == 'J' || rankAdded == 'j') { c.r = Card::rank::jack; }
					else if (rankAdded == 'K' || rankAdded == 'k') { c.r = Card::rank::king; }
					else if (rankAdded == 'Q' || rankAdded == 'q') { c.r = Card::rank::queen; }
					else if (rankAdded == 'A' || rankAdded == 'a') { c.r = Card::rank::ace; }
					else
					{
						cout << "INVALID CARD FOUND" << endl;
						continue;
					} //same logic I mentioned in if (word.length() == three)
					if (suitAdded == 'C' || suitAdded == 'c') { c.s = Card::suit::clubs; }
					else if (suitAdded == 'H' || suitAdded == 'h') { c.s = Card::suit::hearts; }
					else if (suitAdded == 'D' || suitAdded == 'd') { c.s = Card::suit::diamonds; }
					else if (suitAdded == 'S' || suitAdded == 's') { c.s = Card::suit::spades; }
					else
					{
						cout << "INVALID CARD FOUND" << endl;
						continue;
					}
				}//END OF WORD.LENGTH == 2
				else // if length is greater than 3, do nothing.  
				{
					cout << "INVALID CARD FOUND" << endl;
					continue;
				}// END OF IF, ELSE IF, AND ELSE (WORD.LENGTH == 2,3, OR ELSE)
				temp.push_back(c);
				++checkFive;
			}// END OF WHILE (ISS >> WORD)
			if (checkFive == 5) //if five cards are read. 
			{
				for (size_t i = 0; i < temp.size(); ++i)
				{
					vec.push_back(temp[i]);
				}
			}
			else
			{
				cout << "more or less than 5 cards" << endl;
			}
		} // END OF GETLINE(IFS,LINE)
	} // END OF IF(OPEN)
	else  //if file is not opened, return unable_to_open_file
	{
		cout << "Error: " << endl;
		cout << "file name is wrong. Try with hands.txt." << endl;
		return unable_to_open_file;
	}
	ifs.close();
	return success;
};

ErrorControl fileOutput(const vector<Card>& vec)
{
	const int vec_size_when_0 = 0;

	if (vec.size() == vec_size_when_0)
	{
		cout << "Error: " << endl
			<< "vector is empty." << endl;
		return vector_is_empty;
	}
	for (size_t s = 0; s < vec.size(); ++s)
	{
		printOutput(vec[s]);
	}
	return success;
};

/*
printOutput function prints only. (being called from fileOutput)
This is solely for efficiency and stability of const vec.
*/
void printOutput(Card c)
{
	string temp;
	if (c.r == Card::rank::two) { temp += '2'; };
	if (c.r == Card::rank::three) { temp += '3'; };
	if (c.r == Card::rank::four) { temp += '4'; };
	if (c.r == Card::rank::five) { temp += '5'; };
	if (c.r == Card::rank::six) { temp += '6'; };
	if (c.r == Card::rank::seven) { temp += '7'; };
	if (c.r == Card::rank::eight) { temp += '8'; };
	if (c.r == Card::rank::nine) { temp += '9'; };
	if (c.r == Card::rank::ten) { temp += "10"; };
	if (c.r == Card::rank::jack) { temp += 'J'; };
	if (c.r == Card::rank::king) { temp += 'K'; };
	if (c.r == Card::rank::queen) { temp += 'Q'; };
	if (c.r == Card::rank::ace) { temp += 'A'; };
	if (c.s == Card::suit::clubs) { temp += 'C'; };
	if (c.s == Card::suit::spades) { temp += 'S'; };
	if (c.s == Card::suit::hearts) { temp += 'H'; };
	if (c.s == Card::suit::diamonds) { temp += 'D'; };
	cout << temp << endl;
}

ErrorControl pokerHand(const vector<Card> & vec)
{
	int numberOfCards = 5;
	int numberOfHands = vec.size() / numberOfCards;
	for (size_t s = 0; s < numberOfHands; ++s)
	{
		vector<Card> temp;
		for (size_t k = 0; k < numberOfCards; ++k)
		{
			temp.push_back(vec[5 * s + k]); //for each five cards at a time from the vec 0~ vec.size().
		} // from here, temp will have five cards. 
		sort(temp.begin(), temp.end());
		//since five cards will determine the rank at each time. 
		Card first = temp[0];
		Card second = temp[1];
		Card third = temp[2];
		Card fourth = temp[3];
		Card fifth = temp[4];

		if ((first.s == second.s) && (second.s == third.s) && (third.s == fourth.s) && (fourth.s == fifth.s))  // if same suit. 
		{
			if (fifth.r == Card::ace)
			{
				if ((fourth.r - first.r) == 3)
				{
					cout << "straight flush" << endl;
				}
			}
			else
			{
				if ((fifth.r - first.r) == 4)  // meaning that if fifth one is great than first one by 5. - consecutive 
				{
					cout << "straight flush" << endl;
				}
				else
				{
					cout << "flush" << endl;
				}
			}
		}
		else if (first.r == fourth.r || second.r == fifth.r)
		{
			cout << "four of a kind" << endl;
		}


		else if ((first.r == second.r && third.r == fifth.r) ||
			(first.r == third.r && fourth.r == fifth.r))
		{
			cout << "full house" << endl;
		}
		else if ((fifth.r - fourth.r == 1 && fourth.r - third.r == 1 && third.r - second.r == 1 && second.r - first.r == 1) ||
			(fifth.r == Card::ace && fourth.r - third.r == 1 && third.r - second.r == 1 && second.r - first.r == 1)) // meaning every card is consecutive.
		{
			cout << "straight" << endl;
		}
		else if ((first.r == third.r && fourth.r != fifth.r) ||
			(second.r == fourth.r) ||
			(third.r == fifth.r && first.r != second.r))
		{
			cout << "three of a kind" << endl;
		}
		else if ((first.r == second.r && third.r == fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r == third.r && fourth.r == fifth.r) ||
			(first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
		{
			cout << "two pairs" << endl;
		}
		else if ((first.r == second.r && second.r != third.r && third.r != fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r == third.r && third.r != fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r != third.r && third.r == fourth.r && fourth.r != fifth.r) ||
			(first.r != second.r && second.r != third.r && third.r != fourth.r && fourth.r == fifth.r))
		{
			cout << "one pair" << endl;
		}
		else
		{
			cout << "no rank" << endl;
		}
	}
	return success;
};

ErrorControl usageMsg(char* program_name, char* msg)
{
	cout << "Usage: " << program_name << msg << endl;
	return command_line_wrong;
};
