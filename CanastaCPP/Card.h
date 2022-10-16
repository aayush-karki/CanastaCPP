/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <iostream>
#include <string>
#include <vector>

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

// describes the valid ranks and valid suits
struct ST_ValidRankSuit
{
	// stm_rankList lists all the rank of card in a standard deck
	// of card and last J for Joker
	const std::string stm_rankList = "23456789XJQKAJ";

	// stm_suitList lists all the suit of card in a standard deck
	// of card and 1 and 2 for Joker
	// S = spade, C = club, H = heart, and D = diamond
	const std::string stm_suitList = "SCHD12";

	// default constructor
	ST_ValidRankSuit() {};

	// checks to see of the a_rank to in valid rank list
	bool IsRankValid( const char a_rank);

	// checks to see of the a_suit to in valid suit list
	bool IsSuitValid( const char a_suit );

	// checks to see of the a_rankSuit is valid or not
	bool IsRankSuitValid( const std::string a_rankSuit);
};

class Card
{
public:
	// default constructor
	Card( char a_rank = 'A', char a_suit = 'C' );

	// constructor
	Card( const std::string a_rankSuit );

	// default destructor
	~Card() {};

	// copy constructor
	Card( const Card& a_other );

	// assignment operator
	Card& operator = ( const Card& a_other );

	// Getter functions to get rank
	const char GetRank() const { return m_rank; }
	
	// Getter functions to get suit
	const char GetSuit() const { return m_suit; }
	
	// Getter functions to get point
	const unsigned GetPoint() const { return m_point; }
	
	// Getter functions to get card type
	const ENUM_CardType GetCardType() const { return m_cardType; }

	// returns the rank and suit as string 
	const std::string GetRankSuit() const { return std::string( { m_rank, m_suit } ); }

	// converts the passed vector of cards in to string format seperated by space
	static const std::string ConvertVecToString( const std::vector<Card>& a_cardVec );

	// converts the passed vector of cards pointer in to string format seperated by space
	static const std::string ConvertVecToString( const std::vector<Card*>& a_cardVec );

	// prints all the information of the card
	void Debug();

private:
	// m_rank holds the rank of the card
	// can be one of a, 2, 3, 4, 5, 6, 7, 8, 9, 
	// X ( 10 ), J, Q, K, or J ( joker )
	// joker and jack can only be distinguished 
	// by looking at the rank
	// joker has a rank of 1 or 2, while 
	// jack has rank of S, or D, or H, or D
	char m_rank;

	// m_suit holds the suit of the card
	// can be one of C ( club ), D ( spade ), 
	// H ( heart ), D ( diamond ), 1, or 2
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

// Relational operators for Card class
bool operator==( const Card& a_lhs, const Card& a_rhs );
bool operator!=( const Card& a_lhs, const Card& a_rhs );
bool operator<( const Card& a_lhs, const Card& a_rhs );
bool operator<=( const Card& a_lhs, const Card& a_rhs );
bool operator>( const Card& a_lhs, const Card& a_rhs );
bool operator>=( const Card& a_lhs, const Card& a_rhs );
