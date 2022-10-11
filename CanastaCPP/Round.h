/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <vector>
#include "Player.h"
#include "Deck.h"

// list whose turn it could be 
enum class ENUM_PlayerTurn
{
	// computer turn
	TURN_player1,

	// human's turn
	TURN_player2,

	// default value
	TURN_uninitialized
};

class Round
{
public:

	// default constructor
	Round();

	// default destructor
	~Round();

	// copy constructor
	Round( const Round& a_other );

	// assignment operator
	Round& operator = ( const Round& a_other );

	// getter function to ge tteh discard pile
	const std::stack<Card> GetDiscardPile() const { return m_discardPile; }

	// Gets the rankSuit of the top card in the discard pile
	const std::string GetDiscardPileTopRankSuit() const { return m_discardPile.top().GetRankSuit(); }

	// Checks if the round is over
	bool IsRoundOver() const { return m_playerList.front()->CanGoOut() && m_playerList.back()->CanGoOut(); }

	// increase the round number by one
	bool IncrementRoundNumber() { return ++m_currRoundNum; }

	// empties the discard pile
	bool EmptyDiscardPile();

	// adds a card to discardPile
	bool AddToDiscardPile( Card a_cardToAdd ) { m_discardPile.push( a_cardToAdd ); }

	// simulates a coin toss
	char TossACoin() { return ( rand() / 2 ) == 0 ? 'h' : 't'; }

	// clears the round
	void ClearScreen();

	// prtins the title of the game
	void PrintGameTitle();

	// print the Game info
	void PrintRound();

	// starts a new round
	bool StartNewRound();

	// Continues the round
	bool ContinueRound();

private:
	unsigned m_currRoundNum;

	bool m_roundOver;

	// m_playerTurn holds whose turn it could be
	ENUM_PlayerTurn m_playerTurn;

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

	// m_messages holds the messages that player might need 
	// as a result of their action
	// TODO turn this in to a static message class
	std::vector<std::string> m_messages;

	// draws discard and stock pile
	void PrintDiscardAndStock();

	// helper print function to use when there is 
	// 1 or less discard and stock cards
	// in case there are no card in either discard or 
	// stock pile show NA
	void Print1DiscardAnd1Stock( const std::string a_discardCard,
								 const std::string a_handCard );

	// helper print function to use when there is 
	// more than 1 discard card and 1 or less stock cards
	// in case there are no card instock pile show NA
	void Print2DiscardAnd1Stock( const std::string a_discardCard,
								 const std::string a_handCard );

	// helper print function to use when there is 
	// 1 or less discard card and more than 1 stock cards
	// in case there are no card discard pile show NA
	void Print1DiscardAnd2Stock( const std::string a_discardCard,
								 const std::string a_handCard );

	// helper print function to use when there is 
	// more than 1 discard and stock cards
	// in case there are no card discard pile show NA
	void Print2DiscardAnd2Stock( const std::string a_discardCard,
								 const std::string a_handCard );

	// holds logic for the turn
	bool TurnStartLogic();

	// helper print function to print all the message in the 
	// message vector. This prints the message and clears
	// the mesage list 
	void PrintMessages();
};

