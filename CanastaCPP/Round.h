/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <vector>
#include <stack>
#include "Player.h"
#include "Deck.h"
#include "Card.h"

class Round
{
public:

	// default constructor
	Round();

	// default destructor
	~Round() {};

	// copy constructor
	Round( const Round& a_other );

	// assignment operator
	Round& operator = ( const Round& a_other );

	// getter function to ge tteh discard pile
	const std::stack<Card> GetDiscardPile() const { return m_discardPile; }

	// Gets the rankSuit of the top card in the discard pile
	const std::string GetDiscardPileTopRankSuit() const { return m_discardPile.top().GetRankSuit(); }

	bool IsRoundOver()
	{
		//return std::any_of( m_playerList.begin(), m_playerList.end(), []( const Player* a_player ){a_player->CanGoOut(); } );
	}

	// increase the round number by one
	bool IncrementRoundNumber() {return ++m_currRoundNum;}

	// empties the discard pile
	bool EmptyDiscardPile();

	// adds a card to discardPile
	bool AddToDiscardPile( Card a_cardToAdd );

	// simulates a coin toss
	bool TossACoin();

	// print the Game info
	void PrintRound();

	// starts a new round
	bool StartRound();

	// Continues the round
	bool ConinueRound();


private:
	unsigned m_currRoundNum;

	bool m_roundOver;

	// m_playerTurn holds 0 or 1;
	// if = 0, then it is player 1 turn. Player1 is human.
	unsigned m_playerTurn;

	// m_playerListholds the list of player playing the game, 
	// contains 2 player object both of them are object of  
	// classes that are derived form player class.
	std::vector<Player*> m_playerList;

	// m_deck holds deck object used for the game, contains 
	// 2 decks in it with each containing 52 standard card 
	// plus 2 jokers for a total of 108 cards. 
	Deck m_deck;

	// m_discardPile holds cards that are discarded by players,
	// additional player can pick up the whole discarded pile if
	// the last added to the pile help them in making a meld.
	std::stack<Card> m_discardPile;



};

