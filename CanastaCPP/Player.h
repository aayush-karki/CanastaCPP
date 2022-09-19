/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Hand.h"
class Player
{
public:

private:

	// cards of the player
	Hand m_playerHand;

	// holds the point of the player
	unsigned m_totalPoints;

	// is true if the player has atleast one conasta
	bool m_hasConasta;

	// holds value to check if the player can finish 
	// the round or not
	bool m_canGoOut;
	
};

