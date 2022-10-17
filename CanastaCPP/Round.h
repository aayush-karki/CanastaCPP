/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Computer.h"
#include "Human.h"
#include "Deck.h"
#include "Message.h"

// list whose turn it could be 
enum class ENUM_PlayerTurn
{
	// computer turn
	TURN_computer = 0,

	// human's turn
	TURN_human,

	// default value
	TURN_uninitialized
};

class Round
{
public:

	// default constructor
	Round( unsigned a_currRoundNum = 1,
		   ENUM_PlayerTurn a_playerTurn = ENUM_PlayerTurn::TURN_uninitialized,
		   unsigned a_compTotalScore = 0,
		   std::string a_compActualHand = "",
		   std::string a_compMelds = "",
		   unsigned a_humanTotalScore = 0,
		   std::string a_humanActualHand = "",
		   std::string a_humanMelds = "",
		   std::string a_stockCards = "",
		   std::string a_discardPile = "" );

	// default destructor
	~Round();

	// copy constructor
	Round( const Round& a_other );

	// assignment operator
	Round& operator = ( const Round& a_other );

	// getter function to get the current round number
	const unsigned GetCurrRoundNum() { return m_currRoundNum; }

	// getter function to get the discard pile
	const std::vector<Card> GetDiscardPile() const { return m_discardPile; }

	// Gets the rankSuit of the top card in the discard pile
	const std::string GetDiscardPileTopRankSuit() const { return m_discardPile.front().GetRankSuit(); }

	// Gets the rankSuit of the top card in the discard pile
	const Card GetDiscardPileTopCard() const { return m_discardPile.front(); }

	// gets the current player
	const Player* GetCurrPlayerPtr() const { return m_playerList.at( ( unsigned )m_playerTurn ); }

	// gets the not the current player
	const Player* GetOtherPlayerPtr() const { return m_playerTurn == ENUM_PlayerTurn::TURN_computer ? m_playerList.front() : m_playerList.back(); }

	// gets the computer player
	const Player* GetComputerPlayerPtr() const { return m_playerList.front(); }

	// gets the human player
	const Player* GetHumanPlayerPtr() const { return m_playerList.back(); }

	// Get stock in string format
	const std::string GetStockString() const { return m_deck.GetStockString(); };

	// Get discard pile in string format
	const std::string GetDiscardedPile() const { return Card::ConvertVecToString( m_discardPile ); }

	// get the player turn 
	const ENUM_PlayerTurn GetPlayerTurn() const { return m_playerTurn; }

	// Checks if the round is over
	bool IsRoundOver() const { return m_playerList.front()->CanGoOut() || m_playerList.back()->CanGoOut(); }

	// increase the round number by one
	bool IncrementRoundNumber() { return ++m_currRoundNum; }

	// starts a new round
	bool StartNewRound();

	// continues the round
	std::pair<bool, bool> ContinueRound();

	// clears the round
	void ClearScreen();

	// prtins the title of the game
	void PrintGameTitle();

	// print the Game info
	void PrintRound();

private:

	// holds the current round number
	unsigned m_currRoundNum;

	// indicates if the round is over or not by player going out
	bool m_playerWentOut;

	// indicates if it is currently start of the round or not
	bool m_roundStart;

	// indicates if the player drew a red 3 which is also the 
	// last card in stack
	bool m_lastCardR3Drwan;

	// indicates if the both the player can not use the discard pile
	// to make a meld when the stock is empty
	bool m_endCausedCusDiscardPile;

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
	std::vector<Card> m_discardPile;

	// empties the discard pile
	bool EmptyDiscardPile();

	// adds a card to discardPile
	bool AddToDiscardPile( Card a_cardToAdd ) { m_discardPile.insert( m_discardPile.begin(),a_cardToAdd ); return true; }

	// simulates a coin toss
	char TossACoin() { return ( rand() / 2 ) == 0 ? 'h' : 't'; }

	// holds the logic for before turn controller
	std::pair<bool, bool> BeforeTurnLogic( unsigned a_userChoice );

	// holds the logic for turn start controller
	bool TurnStartLogic( unsigned a_userChoice );

	// holds the logic for turn continue controller
	bool TurnContinueLogic( std::vector<unsigned> a_userChoice );

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
};

