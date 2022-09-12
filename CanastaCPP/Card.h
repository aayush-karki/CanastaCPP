/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <iostream>
#include <string>

// 
// describes the type of a card in a deck
// 
// And based on the type the card acts differently
// 
// natural cards are a, 4, 5, 6, 7, 8, 9, x ( or 10 ),
//		j, q, and k. They have no "special powers" 
// wild cards are 2, and J ( or jokers ) and can be 
//		substituted to any of the natural cards to make
//		a meld.
// back three are 3 of club and 3 of spade. It freeze the 
//		discard pile when discarded. The frozen discard 
//		pile cannot be picked up until a natual card is 
//		discarded.
// red three are 3 of heart and 3 of diamond. It is
//		automatically melded and new card is drawn from
//		stock pile as replacement. 
//
enum class ENUM_CardType
{
	CARDTYPE_natural,
	CARDTYPE_wildCard,
	CARDTYPE_blackThree,
	CARDTYPE_redThree,
};

class Card
{
public:
	// default constructor
	Card( char a_rank = 'a', char a_suit = 'c' );

	// default destructor
	~Card() {};

	// copy constructor
	Card( const Card& a_cardToCopy );

	// assignment constructor
	Card& operator = ( const Card& a_cardToAssign );

	// Getter functions
	const char GetRank() const { return m_rank; }
	const char GetSuit() const { return m_suit; }
	const unsigned GetPoint() const { return m_point; }
	const ENUM_CardType GetCardType() const { return m_cardType; }

	// returns the rank and suit as string 
	std::string GetRankSuit() const { return std::string( { m_rank, m_suit } ); }

private:
	// m_rank holds the rank of the card
	// can be one of a, 2, 3, 4, 5, 6, 7, 8, 9, 
	// x ( 10 ), j, q, k, or J ( joker )
	char m_rank;

	// m_suit holds the suit of the card
	// can be one of c ( club ), s ( spade ), 
	// h ( heart ), d ( diamond ), 1, or 2
	//
	// only the standard card rank has c, s, h, and d 
	// as its suit. while only joker can have 1, and 2 
	// as its suit 
	char m_suit;

	// m_pointholds the score of each indivisual card
	// Card			 			Points
	// 4, 5, 6, 7. Black 3 			5
	// 8, 9, 10, J, Q, K 			10
	// 2, A 						20
	// Joker 						50
	// Red 3 						100
	unsigned m_point;

	// m_cardType holds the card type.
	// It can be either natural, or wildcard, or 
	// black three, or red three
	ENUM_CardType m_cardType;
};

