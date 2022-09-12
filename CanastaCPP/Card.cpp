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
			a_cardToCopy, a constant object of card class passed by
				reference. It holds a constant memory address of the
				card object to be copied.
Return Value: none
Algorithm:
			1) assigns each of the member of the passed card object
				to the correspnding member variable of this object
Assistance Received: none
********************************************************************* */
Card::Card( const Card& a_cardToCopy )
{
	this->m_rank = a_cardToCopy.GetRank();
	this->m_suit = a_cardToCopy.GetSuit();
	this->m_point = a_cardToCopy.GetPoint();
	this->m_cardType = a_cardToCopy.GetCardType();
}

/* *********************************************************************
Function Name: operator=
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
Card& Card::operator=( const Card& a_cardToAssign )
{
	this->m_rank = a_cardToAssign.GetRank();
	this->m_suit = a_cardToAssign.GetSuit();
	this->m_point = a_cardToAssign.GetPoint();
	this->m_cardType = a_cardToAssign.GetCardType();

	return *this;
}