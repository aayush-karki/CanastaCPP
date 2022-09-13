/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/
#include "Card.h"

/* *********************************************************************
Function Name: Card
Purpose: To construct a Card object and to populate its member variables
Parameters:
			a_rank, a character. It holds the rank of the card
			a_suit, a character. It holds the suit of the card
Return Value: none
Algorithm:
			1) assigns each of the parameters to the correspnding
				member variable
			2) if the rank is '2' or 'J' then assign the type to be
				ENUM_CardType::CARDTYPE_wildCard
			3) else if the rank is '3'
				4) Check the suit of the card, if it is 'h' or 'd'
					then assign the type to be ENUM_CardType::CARDTYPE_redThree
				5) Else the type is ENUM_CardType::CARDTYPE_blackThree
			6) else the rank is ENUM_CardType::CARDTYPE_natural
			7) if the type is ENUM_CardType::CARDTYPE_redThree
				then assign the point to be 100
			8) else if the rank is 'J' then assign the point to be 50
			9) else if the rank is '2' or 'a' then assign the point to
				be 20
			10) else if the rank is '8', or '9', or 'x', or 'j', or 'q',
				or 'k'then assign the point to be 10
			11) else assign the point to be 5
Assistance Received: none
********************************************************************* */
Card::Card( char a_rank, char a_suit ) : m_rank( a_rank ), m_suit( a_suit )
{
	// figuring out the card type and assigning it to the m_cardType
	if( m_rank == '2' || m_rank == 'J' )
	{
		m_cardType = ENUM_CardType::CARDTYPE_wildCard;
	}
	else if( m_rank == '3' )
	{
		if( m_suit == 'h' || m_suit == 'd' )
		{
			m_cardType = ENUM_CardType::CARDTYPE_redThree;
		}
		else
		{
			m_cardType = ENUM_CardType::CARDTYPE_blackThree;
		}
	}
	else
	{
		m_cardType = ENUM_CardType::CARDTYPE_natural;
	}

	// figuring out the point of the card and assigning it to m_point
	if( m_cardType == ENUM_CardType::CARDTYPE_redThree )
	{
		m_point = 100;
	}
	else if( m_rank == 'J' )
	{
		m_point = 50;
	}
	else if( m_rank == '2' || m_rank == 'a' )
	{
		m_point = 20;
	}
	else if( m_rank == '8' || m_rank == '9' || m_rank == 'x' ||
			 m_rank == 'j' || m_rank == 'q' || m_rank == 'k' )
	{
		m_point = 10;
	}
	else
	{
		m_point = 5;
	}
}

/* *********************************************************************
Function Name: Card
Purpose: To create a new card object and copy the passed Card object's
		member variables data into the newly created card object
Parameters:
			a_other, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be copied.
Return Value: none
Algorithm:
			1) assigns each of the member of the passed card object
				to the correspnding member variable of this object
Assistance Received: none
********************************************************************* */
Card::Card( const Card& a_other )
{
	this->m_rank = a_other.GetRank();
	this->m_suit = a_other.GetSuit();
	this->m_point = a_other.GetPoint();
	this->m_cardType = a_other.GetCardType();
}

/* *********************************************************************
Function Name: operator=, assignment operator
Purpose: To copy the passed Card object's member variables data into
		this card object
Parameters:
			a_cardToAssign, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: its own memory address
Algorithm:
			1) assigns each of the member of the passed card object
				to the correspnding member variable of this object
			2) return its own memory address
Assistance Received: none
********************************************************************* */
Card& Card::operator=( const Card& a_other )
{
	this->m_rank = a_other.GetRank();
	this->m_suit = a_other.GetSuit();
	this->m_point = a_other.GetPoint();
	this->m_cardType = a_other.GetCardType();

	return *this;
}

/* *********************************************************************
Function Name: Debug
Purpose: To see if the card was properly set uped or not
Parameters: none
Return Value: none
Algorithm:
			1) print all the member variable to the screen
Assistance Received: none
********************************************************************* */
void Card::Debug()
{
	std::cout << "Rank: " << m_rank << std::endl;
	std::cout << "Suit: " << m_suit << std::endl;
	std::cout << "Point: " << m_point << std::endl;

	switch( ( m_cardType ) )
	{
		case ( ENUM_CardType::CARDTYPE_natural ):
		{
			std::cout << "Card type: CARDTYPE_natural" << std::endl;
			break;
		}
		case ( ENUM_CardType::CARDTYPE_wildCard ):
		{
			std::cout << "Card type: CARDTYPE_wildCard" << std::endl;
			break;
		}
		case ( ENUM_CardType::CARDTYPE_redThree ):
		{
			std::cout << "Card type: CARDTYPE_redThree" << std::endl;
			break;
		}
		case ( ENUM_CardType::CARDTYPE_blackThree ):
		{
			std::cout << "Card type: CARDTYPE_blackThree" << std::endl;
			break;
		}
		default:
			std::cout << "Card type: error" << std::endl;

			break;
	}

	std::cout << "my card print function: " << GetRankSuit() << std::endl << std::endl;

}

/* *********************************************************************
Function Name: operator==, equal to operator
Purpose: to compare if two card are the same
Parameters:
			a_lhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
			a_rhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: boolean value, true if a_lhs is equal a_rhs
Algorithm:
			1) compare the return of RankSuit() of the each card with
				each other, if both of them are equal then the two
				card is equal
Assistance Received: none
********************************************************************* */
bool operator==( const Card& a_lhs, const Card& a_rhs )
{
	return ( a_lhs.GetRankSuit() == a_rhs.GetRankSuit() );
}

/* *********************************************************************
Function Name: operator!=, not equal to operator
Purpose: to compare if two card are not the same
Parameters:
			a_lhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
			a_rhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: boolean value, true if a_lhs is not equal to a_rhs
Algorithm:
			1) return the negated result of a_lhs == a_rhs
Assistance Received: none
********************************************************************* */
bool operator!=( const Card& a_lhs, const Card& a_rhs )
{
	return !( a_lhs == a_rhs );
}

/* *********************************************************************
Function Name: operator<, less than operator
Purpose: to compare if the card on the left hand side is less than the
	card on the right. the hierarchy is J <	2 < 3 < 4 < 5 < 6 < 7 < 8 <
	9 < x < j < q < k < a, and the suit is c < d < h < s
Parameters:
			a_lhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
			a_rhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: boolean value, true if a_lhs is less than a_rhs
Algorithm:
			1) if a_lhs == a_rhs is true then return false
			2) else if the rank is equal compare the suit and
				return the result
			3) else if a_lhs's rank is 'j' return true
			4) else if a_lhs's rank is 'a' return false
			5) else if a_rhs's rank is 'a' return true
			6) else compare the ranksuit and return the result
Assistance Received: none
********************************************************************* */
bool operator<( const Card& a_lhs, const Card& a_rhs )
{
	// checking if they are equal 
	if( a_lhs == a_rhs )
	{
		return false;
	}
	// checking if the rank is equal then compare the suits
	else if( a_lhs.GetRank() == a_rhs.GetRank() )
	{
		return a_lhs.GetSuit() < a_rhs.GetSuit();
	}
	else if( a_lhs.GetRank() == 'J' )
	{
		return true;
	}
	else if( a_lhs.GetRank() == 'a' )
	{
		return false;
	}
	else if( a_rhs.GetRank() == 'a' )
	{
		return true;
	}
	else
	{
		return (a_lhs.GetRankSuit() < a_rhs.GetRankSuit());
	}
}

/* *********************************************************************
Function Name: operator<=, less than or equal to operator
Purpose: to compare if the card on the left hand side is less than
	or equal to the card on the right.
Parameters:
			a_lhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
			a_rhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: boolean value, true if a_lhs is less than or euqal
	to a_rhs
Algorithm:
			1) return the result of a_lhs == a_rhs or a_lhs < a_rhs
Assistance Received: none
********************************************************************* */
bool operator<=( const Card& a_lhs, const Card& a_rhs )
{
	return ( a_lhs == a_rhs || a_lhs < a_rhs );
}

/* *********************************************************************
Function Name: operator>, more than operator
Purpose: to compare if the card on the left hand side is more than
	the card on the right.
Parameters:
			a_lhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
			a_rhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: boolean value, true if a_lhs is more than a_rhs
Algorithm:
			1) return the negated result of a_lhs <= a_rhs
Assistance Received: none
********************************************************************* */
bool operator>( const Card& a_lhs, const Card& a_rhs )
{
	return ( !( a_lhs <= a_rhs ) );
}

/* *********************************************************************
Function Name: operator>=, more than or equal to operator
Purpose: to compare if the card on the left hand side is more than
	or equal to the card on the right.
Parameters:
			a_lhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
			a_rhs, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be assigned.
Return Value: boolean value, true if a_lhs is more than or equal to
	a_rhs
Algorithm:
			1) return the negated result of a_lhs < a_rhs
Assistance Received: none
********************************************************************* */
bool operator>=( const Card& a_lhs, const Card& a_rhs )
{
	return ( !( a_lhs < a_rhs ) );
}
