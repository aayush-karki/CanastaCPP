/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Deck.h"

/* *********************************************************************
Function Name: Deck
Purpose: To construct a Deck object and to populate its member variables
Parameters: none
Return Value: none
Algorithm:
			1) repeate twice
				2) for first 4 char in m_suitList
					3) for first 13 char in m_rankList
						4) create a new Card object
						5) push the newly created card object to m_stock
				6) create 2 new card object for J1 and J2
Assistance Received: none
********************************************************************* */
Deck::Deck()
{
	// creating the deck of cards
	for( unsigned currDeckNum = 0; currDeckNum < 2; ++currDeckNum )
	{
		for( unsigned currSuitIdx = 0; currSuitIdx < 4; ++currSuitIdx )
		{
			for( unsigned currRankIdx = 0; currRankIdx < 13; ++currSuitIdx )
			{
				m_stock.push_back( new Card( m_rankList.at( currRankIdx ), m_suitList.at( currSuitIdx ) ) );
			}
		}

		// creating a card for joker1 and joker2 and adding it to the m_stock
		m_stock.push_back( new Card( m_rankList.at( 13 ), m_suitList.at( 4 ) ) );
		m_stock.push_back( new Card( m_rankList.at( 13 ), m_suitList.at( 5 ) ) );
	}
}

/* *********************************************************************
Function Name: Deck
Purpose: To destruct a Deck object and to its dynamically allocated
		memory
Parameters: none
Return Value: none
Algorithm:
			1) loop over m_stock and delete each element untill it is empty
			2) loop over m_delt and delete each element untill it is empty
Assistance Received: none
********************************************************************* */
Deck::~Deck()
{
	// dellocating the top element in the m_stock 
	std::vector<Card*>::iterator currPtr = m_stock.begin();

	while( currPtr != m_stock.end() )
	{
		delete ( *currPtr );
		++currPtr;
	}

	// dellocating the top element in the m_dealt 
	currPtr = m_dealt.begin();
	while( currPtr != m_stock.end() )
	{
		delete ( *currPtr );
		++currPtr;
	}
}

/* *********************************************************************
Function Name: Deck
Purpose: To create a new Deck object and copy the passed Deck object's
		member variables data into the newly created Deck object
Parameters:
			a_deckToCopy, a constant object of Deck class passed by
				reference. It holds a constant memory address of the
				Deck object to be copied.
Return Value: none
Algorithm:
			1) for each element in the m_stock of the passed deck object
				2) dynamically create a new Card object using the rank and suit
					data of the element
				3) push back the newly created Card object to the m_stock of
					this deck object
			4) repeate steps 1, 2, and 3 for m_dealt of the passed deck ojbect
Assistance Received: none
********************************************************************* */
Deck::Deck( const Deck& a_other )
{
	// copying the data from m_stock of the passed deck to this deck and
	// dynamically created a Card
	std::vector<Card*>::const_iterator currPtr;
	for( currPtr = a_other.GetStock().begin();
		 currPtr != a_other.GetStock().end();
		 ++currPtr )
	{
		m_stock.push_back( new Card( m_rankList.at( ( *currPtr )->GetRank() ),
									 m_suitList.at( ( *currPtr )->GetSuit() ) ) );
	}

	// copying the data from m_stock of the passed deck to this deck
	// dynamically created a Card
	for( currPtr = a_other.GetDealt().begin();
		 currPtr != a_other.GetDealt().end();
		 ++currPtr )
	{
		m_stock.push_back( new Card( m_rankList.at( ( *currPtr )->GetRank() ),
									 m_suitList.at( ( *currPtr )->GetSuit() ) ) );
	}
}

/* *********************************************************************
Function Name: operator=
Purpose: To deep-copy the passed deck object's member variables data into
		this card object
Parameters:
			a_cardToAssign, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: its own memory address
Algorithm:
			1) check for self assignment, if yes then return the 
				pointer to self
			2) inialize a tempDeck by using the copy constructor
			3) swap the m_stock of the temp deck object with m_stock of
				this object
			4) swap the m_dealt of the temp deck object with m_dealt of
				this object
Assistance Received: cppreference, stackoverflow forum
********************************************************************* */
Deck& Deck::operator=( const Deck& a_other )
{
	// checking for self assignment
	if( this == &a_other )
	{
		return *this;
	}

	// creating a coyp of the passed deck object
	Deck tempDeck(a_other);

	// swapping m_stock
	std::swap( this->m_stock, tempDeck.m_stock );
	std::swap(this->m_dealt, tempDeck.m_dealt );
}
