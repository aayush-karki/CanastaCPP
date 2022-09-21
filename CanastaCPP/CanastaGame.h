/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Round.h"

class CanastaGame
{
public:
	// default contructor
	CanastaGame();

	// default destructor
	~CanastaGame();

	void RunGame();

private:

	// holds the actual game logics and component
	Round m_round;

	// holds boolean value to quit the game
	bool m_gameStart;

};

