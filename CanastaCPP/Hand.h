/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Card.h"

class Hand
{
public:
	// default constructor
	Hand();

	// constructor when the hand is passed
	Hand( std::string a_handCards, std::string a_meldCards );

	// default destructor
	~Hand();

	// copy constructor
	Hand( const Hand& a_other );

	// assignment operator
	Hand& operator = ( const Hand& a_other );

	// getter function get the number of melds
	const unsigned GetTotalMeldNum() const { return m_handCard.size() - 1; }

	// getter function get the number cards in the actual hand--vector at index 0
	const unsigned GetTotalHandCardNum() const { return m_handCard.front().size(); }

	// getter function get if the hand has a canasta or not
	const bool GetHasCanasta() const { return m_hasCanasta; }

	// getter function to get the card in a meld.
	// pass 0 for meldIdx for actual hand
	const Card GetCardAtIdx( unsigned a_meldIdx, unsigned a_meldCardIdx ) const { return *( m_handCard.at( a_meldIdx ).at( a_meldCardIdx ) ); }

	// checks if the actual hand is empty 
	bool IsActualHandEmpty() const { return m_handCard.begin()->empty(); }

	// checks if the meld has at least one wild card 
	bool MeldHasWildCard( unsigned a_meldIdx ) const;

	// checks all the meld for a conasta and if true then update m_hasCanasta
	bool UpdateCanasta();

	// adds passed card to the end of actual hand
	bool AddCardToHand( const Card a_cardToAdd );

	// see if a card can be added to atleast one of the meld or not
	std::pair<bool, std::string> CanAddToMeld( const Card a_cardToAdd ) const;

	// takes the card at index from actual hand and moves 
	// it to a meld if possible
	std::pair<bool, std::string> AddNaturalCardToMeld( unsigned a_handCardIdx, unsigned a_meldIdx );

	// takes the wildcard at index from actual hand and moves 
	// it to a meld if possible
	std::pair<bool, std::string> AddWildCardToMeld( unsigned a_handCardIdx, unsigned a_meldIdx );

	// takes the Red 3 card at index from actual hand and moves 
	// it to a new meld
	std::pair<bool, std::string> AddRed3CardToMeld( unsigned a_handCardIdx );

	// makes a meld from the card at passed index list
	std::pair<bool, std::string> MakeMeld( std::vector<unsigned> a_handCardIdxList );

	// swaps the cards at the passed index 
	bool SwapHandCardPos( unsigned a_handCardIdx1, unsigned a_handCardIdx2 );

	// takes out wild card
	std::pair<bool, std::string> TakeOutWildCard( unsigned a_meldcardIdx, unsigned a_meldIdx );

	// removes the card at a_handCardIdx and returns it.
	Card Discard( unsigned a_handCardIdx );

	// prints out the hand
	void PrintHand();

	// tallies up all the point
	const int TallyPoints() const;

	// returns true if the passed meld idx is a valid index
	bool ValidateMeldIdx( unsigned a_meldIdx ) const { return a_meldIdx < m_handCard.size(); }

	// returns true if the passed a_CardIdx is a valid index of the passed meld
	bool ValidateCardIdx( unsigned a_meldIdx, unsigned a_meldcardIdx ) const
	{
		return a_meldcardIdx < m_handCard.at( a_meldIdx ).size();
	}
private:

	// list of card that the player has in their hand 
	// including the melds
	// the vector at index 0 is the hand cards where as
	// vector at other index are melds
	std::vector<std::vector<Card*>> m_handCard;

	// is true if the meld has atleast one conasta
	bool m_hasCanasta;

	// takes the card at index from actual hand and moves 
	// it to a meld if possible
	std::pair<bool, std::string> AddCardToMeld( unsigned a_handCardIdx , unsigned a_meldIdx );

	// sorts the card at given meld in decending order.
	std::pair<bool, std::string> SortMeld( unsigned a_meldIdx );

	// checks if the meld is canasta -- i.e. has seven or more cards
	bool IsCanasta( unsigned a_meldIdx ) const { return ( m_handCard.at( a_meldIdx ).size() >= 7 ); }
};

