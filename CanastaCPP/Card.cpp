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
			1) check if the rank and suit is valid
			2) assigns each of the parameters to the correspnding
				member variable
			3) if the rank is '2' or 'J' then assign the type to be
				ENUM_CardType::CARDTYPE_wildCard
			4) else if the rank is '3'
				5) Check the suit of the card, if it is 'h' or 'd'
					then assign the type to be ENUM_CardType::CARDTYPE_redThree
				6) Else the type is ENUM_CardType::CARDTYPE_blackThree
			7) else the rank is ENUM_CardType::CARDTYPE_natural
			8) if the type is ENUM_CardType::CARDTYPE_redThree
				then assign the point to be 100
			9) else if the rank is < 'A' then assign the point to be 50
			10) else if the rank is '2' or 'A' then assign the point to
				be 20
			11) else if the rank is '8', or '9', or 'X', or 'J', or 'Q',
				or 'K'then assign the point to be 10
			12) else assign the point to be 5
Assistance Received: none
********************************************************************* */
Card::Card( char a_rank, char a_suit ) :
	m_rank( a_rank ), m_suit( a_suit ), m_point( 20 ),
	m_cardType( ENUM_CardType::CARDTYPE_natural )

{
	ST_ValidRankSuit validRankSuit;

	if( !( validRankSuit.IsRankValid( a_rank ) ) ||
		!( validRankSuit.IsSuitValid( a_suit ) ) )
	{
		std::cerr << "Rank Suit passed is not valid!!!! " << m_rank << m_suit
			<< std::endl;
		return;
	}

	// figuring out the card type and assigning it to the m_cardType
	if( m_rank == '2' || ( m_rank == 'J' && m_suit < 'A' ) )
	{
		m_cardType = ENUM_CardType::CARDTYPE_wildCard;
	}
	else if( m_rank == '3' )
	{
		if( m_suit == 'H' || m_suit == 'D' )
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
	else if( m_suit < 'A' )
	{
		m_point = 50;
	}
	else if( m_rank == '2' || m_rank == 'A' )
	{
		m_point = 20;
	}
	else if( m_rank == '8' || m_rank == '9' || m_rank == 'X' ||
			 m_rank == 'J' || m_rank == 'Q' || m_rank == 'K' )
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
Purpose: To construct a Card object and to populate its member variables
Parameters:
			a_rankSuit, a const string. It holds the rank as the 0th
				character and suit as the 1th character
Return Value: none
Algorithm:
			1) call the default constructor by constructor delegation and
				pass the 0th character of string as first parameter and
				1st character as second parameter
Assistance Received: none
********************************************************************* */
Card::Card( const std::string a_rankSuit ) :
	Card( a_rankSuit[ 0 ], a_rankSuit[ 1 ] )
{
	// here the a_rankSuit is not checked as the Card class checks for
	// rank and suit
}

/* *********************************************************************
Function Name: Card
Purpose: To create a new card object and copy the passed Card object's
		member variables data into the newly created card object
Parameters:
			a_other, a constant object of card class passed by
				reference. It holds the card object to be copied.
Return Value: none
Algorithm:
			1) assigns each of the member of the passed card object
				to the correspnding member variable of this object
Assistance Received: none
********************************************************************* */
Card::Card( const Card& a_other ) :
	m_rank( a_other.GetRank() ),
	m_suit( a_other.GetSuit() ),
	m_point( a_other.GetPoint() ),
	m_cardType( a_other.GetCardType() )
{}

/* *********************************************************************
Function Name: operator=, assignment operator
Purpose: To copy the passed Card object's member variables data into
		this card object
Parameters:
			a_other, a constant object of card class passed by reference.
				It holds a card object that is used to assign this
				card object.
Return Value: its own memory address
Algorithm:
			1) check for self assignment if yes return itself
			2) assigns each of the member of the passed card object
				to the correspnding member variable of this object
			3) return its own memory address
Assistance Received: none
********************************************************************* */
Card& Card::operator=( const Card& a_other )
{
	// checking for self assigmnet 
	if( this == &a_other )
	{
		return *this;
	}

	// copying the data
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
		card on the right. the hierarchy is J (Joker) <	2 < 3 < 4 < 5 < 6
		< 7 < 8 < 9 < x < J ( Jack ) < Q < K < A,
		and the suit is C < D < H < S
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
			3) else if a_lhs's suit is less than 'A' return true
			4) else if a_rhs's suit is less than 'A' return false
			5) else if a_lhs's rank is 'A' return false
			6) else if a_rhs's rank is 'A' return true
			7) else if a_lhs's rank is 'K' return false
			8) else if a_rhs's rank is 'K' return true
			9) else if a_lhs's rank is 'Q' return false
			10) else if a_rhs's rank is 'Q' return true
			11) else if a_lhs's rank is 'J' return false
			12) else if a_rhs's rank is 'J' return true
			13) else compare the rank and return the result
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
	// here we do not need to worry about 'J' ( Joker ) and
	// 'J' (Jack) because Joker can only have 1 or 2 as suit 
	//  which would be less than Jack's suit as they are 
	// alphabhets
	else if( a_lhs.GetRank() == a_rhs.GetRank() )
	{
		return a_lhs.GetSuit() < a_rhs.GetSuit();
	}
	// from before if know that from now the ranks of lCard and
	// rCard is different
	// checking for Joker which is the smallest
	// if left hand is joker then return true
	else if( a_lhs.GetSuit() < 'A' )
	{
		return true;
	}
	// if right hand is joker then return false
	else if( a_rhs.GetSuit() < 'A' )
	{
		return false;
	}
	// checking for A which is the largest
	else if( a_lhs.GetRank() == 'A' )
	{
		return false;
	}
	else if( a_rhs.GetRank() == 'A' )
	{
		return true;
	}
	// checking for K which is the next largest
	else if( a_lhs.GetRank() == 'K' )
	{
		return false;
	}
	else if( a_rhs.GetRank() == 'K' )
	{
		return true;
	}
	// checking for Q which is the next largest
	else if( a_lhs.GetRank() == 'Q' )
	{
		return false;
	}
	else if( a_rhs.GetRank() == 'Q' )
	{
		return true;
	}
	// checking for J (Jack) which is the next largest
	// here we have already checked for Joker so we
	// do not have to worry about that
	else if( a_lhs.GetRank() == 'J' )
	{
		return false;
	}
	else if( a_rhs.GetRank() == 'J' )
	{
		return true;
	}
	// rest of them which are 2, 3, 4, 5, 6, 7, 8, 9, and X
	// order in Ascii follow our order
	else
	{
		return ( a_lhs.GetRank() < a_rhs.GetRank() );
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


/* *********************************************************************
Function Name: IsRankValid
Purpose: to see if the passed rank is valid rank or not
Parameters:
			a_rank, a const character. It holds the rank that needs to
				be validated
Return Value: boolean value, true if a_rank is valid
Algorithm:
			1) use std::find() to see if the char is in stm_rankList
			2) if return of step 1 is the end() of stm_rankList then
				return false else return true
Assistance Received: none
********************************************************************* */
bool ST_ValidRankSuit::IsRankValid( const char a_rank )
{
	std::string::const_iterator findReturnIte = std::find( stm_rankList.begin(),
														   stm_rankList.end(),
														   a_rank );
	return ( findReturnIte != stm_rankList.end() );
}

/* *********************************************************************
Function Name: IsSuitValid
Purpose: to see if the passed suit is valid suit or not
Parameters:
			a_suit, a const character. It holds the suit that needs to
				be validated
Return Value: boolean value, true if a_suit is valid
Algorithm:
			1) use std::find() to see if the char is in stm_suit
			2) if return of step 1 is the end() of stm_suit then
				return false else return true
Assistance Received: none
********************************************************************* */
bool ST_ValidRankSuit::IsSuitValid( const char a_suit )
{
	std::string::const_iterator findReturnIte = std::find( stm_suitList.begin(),
														   stm_suitList.end(),
														   a_suit );
	return ( findReturnIte != stm_suitList.end() );
}

/* *********************************************************************
Function Name: IsRankSuitValid
Purpose: to to see of the passeda_rankSuit is valid or not
Parameters:
			a_rankSuit, a const string. It holds the rank and suit
				that needs to be validated. The rank is the 0th character
			and suit is the 1th character
Return Value: boolean value, true if a_suit is valid
Algorithm:
			1) check to see if the a_rankSuit is size 2, if not return
				false
			2) use the IsRankValid() and IsSuitFunction to validate the
				suit and return the result
Assistance Received: none
********************************************************************* */
bool ST_ValidRankSuit::IsRankSuitValid( const std::string a_rankSuit )
{
	// the size should always be 2
	if( a_rankSuit.size() != 2 )
	{
		return false;
	}

	// validating the rank and suit
	return ( IsRankValid( a_rankSuit.at( 0 ) ) &&
			 IsSuitValid( a_rankSuit.at( 1 ) ) );
}

/* *********************************************************************
Function Name: ConvertVecToString
Purpose: converts the passed vector of card into string format
Parameters: 
			a_cardVec, vector of cards passed by reference holds the 
				cards that are to be converted into string.
Return Value:
			const string, containing the rank and suit of
				cards passed to the funciton. Each card
				is seperated by blank space. 
Algorithm:
			1) create a string
			2) for each card in the actual hand add that to the back of
					string created in step 1
			3) remove the last extra space
Assistance Received: none
********************************************************************* */
 const std::string Card::ConvertVecToString( const std::vector<Card>& a_cardVec )
{
	// if the are no cards in the passed vector return ""
	if( a_cardVec.empty() )
	{
		return "";
	}

	// converting the card into string
	std::string cardStr = "";
	for( unsigned cardIdx = 0; cardIdx < a_cardVec.size(); ++cardIdx )
	{
		// adding cards to the string
		cardStr += a_cardVec.at( cardIdx ).GetRankSuit() + " ";
	}

	// removing the last " "
	std::string cardStrNoLastSpace = "";

	for( unsigned strIdx = 0; strIdx < cardStr.size() - 1; ++strIdx )
	{
		cardStrNoLastSpace += cardStr.at( strIdx );
	}

	return cardStrNoLastSpace;
}


/* *********************************************************************
Function Name: ConvertVecToString
Purpose: converts the passed vector of card pointer into string format
Parameters:
			a_cardVec, vector of cards pointer passed by reference holds the
				cards that are to be converted into string.
Return Value:
			const string, containing the rank and suit of
				cards passed to the funciton. Each card
				is seperated by blank space.
Algorithm:
			1) create a string
			2)	for each card in the actual hand add that to the back of
				string created in step 1
Assistance Received: none
********************************************************************* */
const std::string Card::ConvertVecToString( const std::vector<Card*>& a_cardVec )
{
	// if the are no cards in the passed vector return ""
	if( a_cardVec.empty() )
	{
		return "";
	}

	// converting the card into string
	std::string cardStr = "";
	for( unsigned cardIdx = 0; cardIdx < a_cardVec.size(); ++cardIdx )
	{
		// adding cards to the string
		cardStr += a_cardVec.at( cardIdx )->GetRankSuit() + " ";
	}

	// removing the last " "
	std::string cardStrNoLastSpace = "";

	for( unsigned strIdx = 0; strIdx < cardStr.size() - 1; ++strIdx )
	{
		cardStrNoLastSpace += cardStr.at( strIdx );
	}

	return cardStrNoLastSpace;
}