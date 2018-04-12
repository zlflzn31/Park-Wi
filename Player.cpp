#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Player::Player(char * givenName) :
	playerName(givenName), winCounts(0), lossCounts(0) { //using the parameter to initialize the playerName. Also, Initaiizing win and loss to 0. 
	playerHand = Hand(); // this has to be default constructed to be empty. 
	string fileName = givenName;  
	ifstream ifs(fileName + ".txt"); //fileName should be same as player's name, so I added .txt after it. 
	if (ifs.is_open())
	{
		string line;
		vector<string> stored = vector<string>(); // since we have to verify the number of strings, vector<string> will be the best way. 
		while (!ifs.eof()) // check if the stream's eofbit error state flag is set or not ... ? 
		{
			getline(ifs, line);
			stored.push_back(line);
		}
		//vector size matters. If stored's size is less than 3, then it cant extract  every information we need (name, win, loss). 
		//so it has to be greater than 3. 
		if (stored.size() >= 3) 
		{
			playerName = stoi(stored[0]);
			winCounts = stoi(stored[1]); //to convert from string to int. 
			lossCounts = stoi(stored[2]); //to convert from string to int. 
		}
		else //if "both values cannot be extracted" meaning that stored.size is not greater 3. 
		{
			winCounts = 0; //should be re-setted to 0.
			lossCounts = 0; // same here. 
		}


	}
	else // if not opened, 
	{
		return; // finish execution. 
	}

}

ostream & operator<<(ostream & out, const Player & p)
{
	out << p.playerName << " " << p.winCounts << " " << p.lossCounts << endl; // between each variable, there should be a space. 
	return out;
}
