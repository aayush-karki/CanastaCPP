/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <iomanip>
#include <algorithm>
#include "Hand.h"
#include "Message.h"

class Player
{
public:

	// default constructor
	Player( unsigned a_totalScore = 0,
			std::string a_handCards = "",
			std::string a_meldCards = "" );

	// default destructor
	virtual ~Player() {};

	// copy constructor
	Player( const Player& a_other );

	// assignment operator
	Player& operator = ( const Player& a_other );

	// gets the saved current point
	int GetTotalPoint() const { return m_totalPoints; }

	// Get players actual hand
	const std::vector<Card> GetActualHand() const { return m_playerHand.GetActualHand(); }

	// Get players melds
	const std::vector<std::vector<Card>> GetMelds() const { return m_playerHand.GetMelds(); }

	// Get players actual hand in string format
	const std::string GetActualHandString() const { return m_playerHand.GetActualHandString(); }

	// Get players melds in string format
	const std::string GetMeldsString() const { return m_playerHand.GetMeldsString(); }

	// Get players went out status
	bool GetPlayerWentOutStatus() const { return m_wentOut; }

	// set players before turn flag status
	bool GetTurnStartFlag() const { return m_isStartOfTurn; }

	// set players went out status
	bool SetPlayerWentOutStatus( bool a_playerWentOut ) { m_wentOut = a_playerWentOut; return true; }

	// set players before turn flag status
	bool SetPlayerBeforeTurnMenuFlag( bool a_showBeforeTurnMenu ) { m_showBeforeTurnMenu = a_showBeforeTurnMenu; return true; }

	// set players before turn flag status
	bool SetTurnStartFlag( bool a_showTurnStartMenu ) { m_isStartOfTurn = a_showTurnStartMenu; return true; }


	// executes the player start of the turn logic
	std::pair<unsigned, std::vector<unsigned>> PlayerTurnController( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																	 const std::vector<Card>& a_discardPile );

	// executes the before the turn start controller
	virtual std::pair<unsigned, std::vector<unsigned>> BeforeTurnStartControl();

	// executes the player start of the turn controller
	virtual std::pair<unsigned, std::vector<unsigned>> TurnStartControl( const std::vector<Card>& a_discardPile );

	// executes the player turn continue controller
	virtual std::pair<unsigned, std::vector<unsigned>> TurnContinueControl( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																			const std::vector<Card>& a_discardPile );

	// set to the saved current point
	bool AddToTotalPoints( int a_pointsToAdd ) { m_totalPoints += a_pointsToAdd; return true; }

	// tallys the hand Point
	const int TallyHandPoint() const { return m_playerHand.TallyPoints( m_wentOut ); }

	// adds the drawn card to the deck
	bool AddCardToHand( const Card a_drawnCard ) { return m_playerHand.AddCardToHand( a_drawnCard ); }

	// Empties the cards in the hand
	void EmptyHand() { m_playerHand = Hand(); }

	// swaps the cards at the passed index 
	bool SwapHandCardPos( unsigned a_handCardIdx1, unsigned a_handCardIdx2 ) { return m_playerHand.SwapHandCardPos( a_handCardIdx1, a_handCardIdx2 ); }

	// tries to add to a existing meld using the card at the passed hand index
	std::pair<bool, std::string> AddToMeld( unsigned a_handCardIdx, unsigned a_meldIdx );

	// see if a card can be added to atleast one of the meld or not
	std::pair<unsigned, std::string> CanAddToMeld( const Card a_cardToAdd ) const { return m_playerHand.CanAddToMeld( a_cardToAdd ); }

	// tries to create a new meld using the cards at the passed hand indexs
	std::pair<bool, std::string> MakeNewMeld( std::vector<unsigned> a_handCardIdxList ) { return m_playerHand.MakeMeld( a_handCardIdxList ); }

	// takes out wild card
	std::pair<bool, std::string> TakeOutWildCard( unsigned a_meldcardIdx, unsigned a_meldIdx ) { return m_playerHand.TakeOutWildCard( a_meldcardIdx, a_meldIdx ); }

	// discards a card at passed hand index
	Card Discard( unsigned a_handCardIdx ) { return m_playerHand.Discard( a_handCardIdx ); }

	// picks up the discarded pile and adds it to hand
	bool PickUpDiscardPile( const std::vector<Card>& a_discardPile );

	// returns true if the passed meld idx is a valid index
	bool ValidateMeldIdx( unsigned a_meldIdx ) const { return m_playerHand.ValidateMeldIdx( a_meldIdx ); }

	// returns true if the passed a_CardIdx is a valid index of the passed meld
	bool ValidateCardIdx( unsigned a_meldIdx, unsigned a_CardIdx ) const { return m_playerHand.ValidateCardIdx( a_meldIdx, a_CardIdx ); }

	// checks if go out is possible or not
	bool CanGoOut() const { return m_playerHand.IsActualHandEmpty() && m_playerHand.GetHasCanasta(); }

	// prints the playern
	void PrintPlayer() const;

	// resets player's hand, and flags
	virtual bool ResetPlayerForNewRound();
protected:

	// cards of the player
	Hand m_playerHand;

	// holds the point of the player
	int m_totalPoints;

	// holds the state of to whether to show menu that
	// before the turn actually starts
	bool m_showBeforeTurnMenu;

	// holds the state of current  turn
	// is true if this is the start of the turn
	bool m_isStartOfTurn;

	// holds the value of it the player went out
	bool m_wentOut;

	// validate that rhe passed string is a number that is 
	// between lowerLimit and upperLimit inclusively
	int ValidateNumber( std::string a_numToValidate,
						unsigned a_inclusiveLowerBound,
						unsigned a_inclusiveUpperBound );

};

