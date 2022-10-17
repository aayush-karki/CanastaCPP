/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Player.h"
class Human :
	public Player
{
public:
	// default constructor
	Human( unsigned a_totalScore = 0,
		   std::string a_handCards = "",
		   std::string a_meldCards = "" ) :
		Player( a_totalScore,
				a_handCards,
				a_meldCards ) {};

	// default destructor
	virtual ~Human() {};

	// copy constructor
	Human( const Human& a_other ): Player(a_other) {};

	// assignment operator
	Human& operator = ( const Human& a_other );

	// executes the before the turn start controller
	virtual std::pair<unsigned, std::vector<unsigned>> BeforeTurnStartControl() { return Player::BeforeTurnStartControl(); }

	// executes the player start of the turn controller
	virtual std::pair<unsigned, std::vector<unsigned>> TurnStartControl( const std::vector<Card>& a_discardPile )
	{
		return Player::TurnStartControl( a_discardPile );
	}

	// executes the player turn continue controller
	virtual std::pair<unsigned, std::vector<unsigned>> TurnContinueControl( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																			const std::vector<Card>& a_discardPile )
	{
		return Player::TurnContinueControl( a_otherPlayerMeld, a_discardPile );
	}

};

