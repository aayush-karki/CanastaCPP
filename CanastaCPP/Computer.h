/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Player.h"

// TODO (FEATURE) Change the AI. AI should take the discard pile and opponets meld into considiration
// TODO (FEATURE) It would be nice if the AI also keeps tracks of "Showed" card or card Counting and factors that in to its decision

class Computer :
	public Player
{
public:
	// default constructor
	Computer( unsigned a_totalScore = 0,
			  std::string a_handCards = "",
			  std::string a_meldCards = "" ) :
		Player( a_totalScore,
				a_handCards,
				a_meldCards )
	{};

	// default destructor
	virtual ~Computer() {};

	// copy constructor
	Computer( const Computer& a_other ) : Player( a_other ) {};

	// assignment operator
	Computer& operator = ( const Computer& a_other );

	// executes the before the turn start controller
	virtual std::pair<unsigned, std::vector<unsigned>> BeforeTurnStartControl() { return { 1, {2} }; }

	// executes the player start of the turn controller
	virtual std::pair<unsigned, std::vector<unsigned>> TurnStartControl( const std::vector<Card>& a_discardPile );

	// executes the player turn continue controller
	virtual std::pair<unsigned, std::vector<unsigned>> TurnContinueControl( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																			const std::vector<Card>& a_discardPile );

	// executes the player start of the turn controller
	virtual std::pair<std::pair<unsigned, std::vector<unsigned>>, std::string> TurnStartHelp( const std::vector<Card>& a_discardPile );

	// executes the player turn continue controller
	virtual  std::pair < std::pair<unsigned, std::vector<unsigned>>, std::string> TurnContinueHelp( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																									const std::vector<Card>& a_discardPile );
};

