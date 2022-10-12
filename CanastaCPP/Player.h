/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <stack>
#include <iomanip>
#include "Hand.h"

class Player
{
public:

	// default constructor
	Player();

	// constructor when hand cards are passed
	Player( std::string a_handCards, std::string a_meldCards );

	// default destructor
	~Player() {};

	// copy constructor
	Player( const Player& a_other );

	// assignment operator
	Player& operator = ( const Player& a_other );

	// gets the saved current point
	const int GetTotalPoint() const { return m_totalPoints; }

	// Get players melds
	const std::vector<std::vector<Card>> GetMelds() const { m_playerHand.GetMelds(); };

	// tallys the hand Point
	const int TallyHandPoint() const { return m_playerHand.TallyPoints(); }

	// set to the saved current point
	bool SetTotalPoint( int a_totalPoint );

	// adds the drawn card to the deck
	bool AddCardToHand( const Card a_drawnCard ) { return m_playerHand.AddCardToHand( a_drawnCard ); }

	// Empties the cards in the hand
	void EmptyHand() { m_playerHand = Hand(); }

	// swaps the cards at the passed index 
	bool SwapHandCardPos( unsigned a_handCardIdx1, unsigned a_handCardIdx2 ) { return m_playerHand.SwapHandCardPos( a_handCardIdx1, a_handCardIdx2 ); }

	// see if a card can be added to atleast one of the meld or not
	std::pair<bool, std::string> CanAddToMeld( const Card a_cardToAdd ) const { return m_playerHand.CanAddToMeld( a_cardToAdd ); }

	// tries to create a new meld using the cards at the passed hand indexs
	std::pair<bool, std::string> MakeNewMeld( std::vector<unsigned> a_handCardIdxList ) { return m_playerHand.MakeMeld( a_handCardIdxList ); }

	// takes out wild card
	std::pair<bool, std::string> TakeOutWildCard( unsigned a_meldcardIdx, unsigned a_meldIdx ) { return m_playerHand.TakeOutWildCard( a_meldcardIdx, a_meldIdx ); }

	// tries to add to a existing meld using the card at the passed hand index
	std::pair<bool, std::string> AddToMeld( unsigned a_handCardIdx, unsigned a_meldIdx );

	// discards a card at passed hand index
	Card Discard( unsigned a_handCardIdx ) { return m_playerHand.Discard( a_handCardIdx ); }

	// picks up the discarded pile and adds it to hand
	bool PickUpDiscardPile( std::stack<Card> a_discardPile );

	// returns true if the passed meld idx is a valid index
	bool ValidateMeldIdx( unsigned a_meldIdx ) const { return m_playerHand.ValidateMeldIdx( a_meldIdx ); }

	// returns true if the passed a_CardIdx is a valid index of the passed meld
	bool ValidateCardIdx( unsigned a_meldIdx, unsigned a_CardIdx ) const { return m_playerHand.ValidateCardIdx( a_meldIdx, a_CardIdx ); }

	// checks if go out is possible or not
	bool CanGoOut() const { return m_playerHand.IsActualHandEmpty() && m_playerHand.GetHasCanasta(); }

	// prints the playern
	void PrintPlayer();

private:

	// cards of the player
	Hand m_playerHand;

	// holds the point of the player
	int m_totalPoints;
};

