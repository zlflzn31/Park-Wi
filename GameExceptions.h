#pragma once
#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H
#include <stdexcept>
using namespace std;

struct only_one_player : public exception
{
	explicit only_one_player() : exception() { }
};
struct no_player : public exception
{
	explicit no_player() : exception() { }
};
struct no_game_in_progress : public exception
{
	explicit no_game_in_progress() : exception() { }
};

struct already_playing : public exception
{
	explicit already_playing() : exception() { }
};

struct instance_not_available : public exception
{
	explicit instance_not_available() : exception() { }
};

struct game_already_started : public exception
{
	explicit game_already_started() : exception() { }
};

struct unknown_game : public exception
{
	explicit unknown_game() : exception() { }
};

#endif //GameExceptions_H_
