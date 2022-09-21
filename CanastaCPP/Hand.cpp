/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Hand.h"

/* *********************************************************************
Function Name: Hand
Purpose: To construct a Hand object and to populate its member variables.
Parameters: none
Return Value: none
Algorithm:
		1) set the m_hasCanasta to false
		2) resize m_hanCard to 1
Assistance Received: none
********************************************************************* */
Hand::Hand()
	: m_hasCanasta( false )
{
	m_handCard.resize( 1 );
}

/* *********************************************************************
Function Name: Hand
Purpose: To construct a Hand object and to populate its member variables
		m_handCard is populated using the passed parameter.
Parameters:
			a_handCards, a string containing the rank and suit of cards.
				Each card is seperated by blank space.
			a_meldCards, a string containing the rank and suit of cards
				in the m_stock. Each card is seperated by blank space
				and each meld is inside '[' and ']'
Return Value: none
Algorithm:
			1) initialize a string stream with the passed string
				a_handCards as parameter called passedStringStream
			2) initialize a string called extractdRankSuit
				and assign it a value of ""
			3) while(  a ranksuit can be extracted form passedStringStream
				into the extractdRankSuit )
			{
				4) create a new card and push it back to the first vector of
					vector--m_handCard.at[0]
			}
			5) empty and clear the passedStringStream and then
				assign the a_meldCards to the passedStringStream
			6) Initialize a bool hasMoreMeld and assign it to true.
			7) while (hasMoreMeld)
			{
				8) increase the size of m_handCard by 1
				9) initailize 2 bool as starOfMeld and endOfMeld and initiaize
					them to start to false
				10) while(  a ranksuit can be extracted form passedStringStream
					into the extractdRankSuit )
				{
					11) Check if the extracted string is of size 3 and has either
						'[' or ']'. if it has '[' then set startOfMeld to true
						if it has ']' set endOfMeld to true and remove it from
						extractdRankSuit
					12) else if Check if the extracted string is of size 4 and if
						it is check if it has both '[' and ']'. then set both the
						 startOfMeld and endOfMeld to true and remove them from
						extractdRankSuit
					13) else if check if the string is of size 2 then create a
						new card using the string as parameter and push it back to
						the m_handCard
					17) check if endOfMeld
						18) if yes check if the stringstream at eof by using peek()
							19) if yes set hasMoreMeld to false
							20) else set hasMoreMeld to true
				}
			}
Assistance Received: cplusplus
********************************************************************* */
Hand::Hand( std::string a_handCards, std::string a_meldCards ) :
	Hand()
{
	// processing the a_handCards
	std::stringstream passedStringStream( a_handCards );
	std::string extractdRankSuit = "";

	// populaitng the vector at 0th index of m_handCard
	// as the 0th vector is the place where the hand card are placed

	// populating the m_handCard
	while( passedStringStream >> extractdRankSuit )
	{
		// validaitng the size of the extracted string
		if( extractdRankSuit.size() != 2 )
		{
			std::cerr << "Extracted Rank and Suit in the m_handCards is not length 2" << std::endl;
			continue;
		}

		m_handCard.at( 0 ).push_back( new Card( extractdRankSuit ) );
	}

	// chekcing it the meld is empty then do nothing
	if( a_meldCards == "" )
	{
		return;
	}

	// populating hte string stream with meldCard
	passedStringStream.str( std::string() );
	passedStringStream.clear();
	passedStringStream << a_meldCards;


	// processing the a_meldCards
	bool hasMoreMeld = true;
	while( hasMoreMeld )
	{
		// adding a new meld
		m_handCard.resize( m_handCard.size() + 1 );

		// holds if the end of Meld has reached or not
		bool startOfMeldFound = false;
		bool endOfMeldFound = false;
		// loop while we can extract a rank and suit
		while( passedStringStream >> extractdRankSuit )
		{
			// melds are in the format [ranksuit1 ranksuit2 ...]
			// so the extracted sting can be  [rankSuit, or rankSuit,
			// or rankSuit], or [rankSuit] in the case of [3h]

			// checking the length of the extractdRankSuit 
			if( extractdRankSuit.size() == 3 )
			{
				// chekcing it  the first char is [
				if( extractdRankSuit.front() == '[' )
				{
					startOfMeldFound = true;
					// removing the '[' from the extractedRankSuit
					extractdRankSuit = extractdRankSuit.substr( 1, 2 );
				}
				// chekcing it  the last char is ]
				else if( extractdRankSuit.back() == ']' )
				{
					endOfMeldFound = true;
					// chekcing it  the first char is [
					extractdRankSuit = extractdRankSuit.substr( 0, 2 );
				}
				else
				{
					std::cerr << "Invalid Extracted Rank and Suit in the a_meld" << std::endl;
					break;
				}
			}
			else if( extractdRankSuit.size() == 4 )
			{
				// this can be when meld is [3h]
				//chekcing if the first and last char 
				// are '[' and ']' respectivly
				if( extractdRankSuit.front() == '[' && extractdRankSuit.back() == ']' )
				{
					startOfMeldFound = true;
					endOfMeldFound = true;
					extractdRankSuit = extractdRankSuit.substr( 1, 2 );
				}
			}
			else if( extractdRankSuit.size() != 2 )
			{
				std::cerr << "Invalid Extracted Rank and Suit in the a_meld" << std::endl;
				break;
			}

			// creating a card and adding to the last meld
			m_handCard.back().push_back( new Card( extractdRankSuit ) );

			// checking if endOfMeld was found and more meld is left
			if( endOfMeldFound )
			{
				if( passedStringStream.peek() == EOF )
				{
					hasMoreMeld = false;
				}
				else
				{
					hasMoreMeld = true;
				}

				break;
			}

		}

		// chekcing if both no error occured
		if( !startOfMeldFound || !endOfMeldFound )
		{
			std::cerr << "Error while process a_meld" << std::endl;
			break;
		}
	}
}

/* *********************************************************************
Function Name: Hand
Purpose: To destruct a Hand object and to its dynamically allocated
			memory
Parameters: none
Return Value: none
Algorithm:
			1) for each vector in the m_handCard
				3)	for each card in the vector
					4) deallocate the card
Assistance Received: none
********************************************************************* */
Hand::~Hand()
{
	std::vector<std::vector<Card*>>::iterator currVecIte = m_handCard.begin();

	// copying the card data
	while( currVecIte != m_handCard.end() )
	{
		std::vector<Card*>::iterator currCardIte = ( *currVecIte ).begin();

		while( currCardIte != ( *currVecIte ).end() )
		{
			delete* currCardIte;
			++currCardIte;
		}

		++currVecIte;
	}
}

/* *********************************************************************
Function Name: Hand
Purpose: To create a new Hand object and copy the passed Hand object's
		member variables data into the newly created Hand object
Parameters:
			a_other, a constant object of Hand class passed by
				reference. It holds a hand object to be copied.
Return Value: none
Algorithm:
			1) copy the data of hasCanasta
			2) resize the m_handCard of this class to the size of
				a_other's m_handCard
			3) for each vector in the m_handCard of the passed hand object
				4)	for each card in the vector
					5) dyanmically create a card and push it back to
						this hand's vector
Assistance Received: none
********************************************************************* */
Hand::Hand( const Hand& a_other )
{
	this->m_hasCanasta = a_other.m_hasCanasta;

	m_handCard.resize( a_other.m_handCard.size() );

	std::vector<std::vector<Card*>>::iterator thisCurrVecIte = this->m_handCard.begin();
	std::vector<std::vector<Card*>>::const_iterator otherCurrVecIte = a_other.m_handCard.begin();

	// copying the card data
	while( otherCurrVecIte != a_other.m_handCard.end() )
	{
		std::vector<Card*>::const_iterator otherCurrCardIte = ( *otherCurrVecIte ).begin();

		while( otherCurrCardIte != ( *otherCurrVecIte ).end() )
		{
			( *thisCurrVecIte ).push_back( new Card( *( *otherCurrCardIte ) ) );
			++otherCurrCardIte;
		}

		++otherCurrVecIte;
		++thisCurrVecIte;
	}
}

/* *********************************************************************
Function Name: operator=
Purpose: To deep-copy the passed Hand object's member variables data into
		this hand object
Parameters:
			a_other, a constant object of hand class passed by reference.
				It holds a hand object that is used to assign this
				hand object.
Return Value: its own memory address
Algorithm:
			1) check for self assignment, if yes then return the
				pointer to self
			2) inialize a tempHand by using the copy constructor
			3) swap the m_handCard of the temp hand object with m_handCard of
				this object
Assistance Received: none
********************************************************************* */
Hand& Hand::operator=( const Hand& a_other )
{
	// checking for self assignment
	if( this == &a_other )
	{
		return *this;
	}

	// creating a copy of the passed hand object
	Hand temphand( a_other );

	// swapping m_stock
	std::swap( this->m_handCard, temphand.m_handCard );

	return *this;
}

/* *********************************************************************
Function Name: MeldHasWildCard
Purpose: To check if the meld at given position has atleast one wildcard
Parameters:
			a_meldIdx, a unsigned integer. It holds the index of the meld
				to check.
Return Value: true if the meld has atleast one wild card
Algorithm:
			1) loop over the cards at that index and check if any of them
				is a wildcard type
Assistance Received: none
********************************************************************* */
bool Hand::MeldHasWildCard( unsigned a_meldIdx ) const
{
	// checking if the atleast one card of the meld is a wild card
	for( unsigned cardIdx = 0; cardIdx < m_handCard.at( a_meldIdx ).size(); ++cardIdx )
	{
		if( m_handCard.at( a_meldIdx ).at( cardIdx )->GetCardType() == ENUM_CardType::CARDTYPE_wildCard )
		{
			return true;
		}
	}

	return false;
}

/* *********************************************************************
Function Name: UpdateCanasta
Purpose: to check all the meld for a conasta and update the m_hasCanasta
	accordingly
Parameters: none
Return Value: true if a changes was made t0 m_hasConasta; else false
Algorithm:
			1) loop over the melds
				2) check for canasta by using IsCanasta
					3) if yes update m_hasCanasta and return
Assistance Received: none
********************************************************************* */
bool Hand::UpdateCanasta()
{
	bool currCanasta = m_hasCanasta;

	// looping over the melds
	for( unsigned meldIdx = 1; meldIdx < m_handCard.size(); ++meldIdx )
	{
		if( IsCanasta( meldIdx ) )
		{
			m_hasCanasta = true;
			break;
		}
	}

	return currCanasta == m_hasCanasta;
}


/* *********************************************************************
Function Name: AddCardToHand
Purpose: to add a card to hand
Parameters: 
			a_cardToAdd, a constant object of hand class passed by value.
				It holds a hand object that is used to assign this
				hand object.
Return Value: true as it changes m_handCard
Algorithm:
			1) crete a new card using the passed parameters and push it
				back to actual hand
			2) return true to indicate a change was made to member
				variable
Assistance Received: none
********************************************************************* */
bool Hand::AddCardToHand( const Card a_cardToAdd )
{
	m_handCard.begin()->push_back( new Card( a_cardToAdd ) );
	return true;
}

/* *********************************************************************
Function Name: CanAddToMeld
Purpose: Tries to see if the passed card can be added to the meld or not
Parameters:
			 a_cardToAdd, a constant object of hand class passed by value.
				It holds a hand object that is used to assign this
				hand object.
Return Value: a pair of < bool, string >, < true, empty string > if the 
		card can be added to a meld . else  < false, message string >
Algorithm:
			1) if card is not a natural card return false
			2) else the card is a natural card
				) for each of meld vector, call AddCardToMeld()
				and pass the a_handCardIdx, and the meld index as
				parameters
			3) if meld was successfull update the hasCanasta by calling
				UpdateCanasta()
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Hand::CanAddToMeld( const Card a_cardToAdd ) const
{
	if( a_cardToAdd.GetCardType() != ENUM_CardType::CARDTYPE_natural )
	{
		return { false, "Card is  not a natural card" };
	}

	// looping over the meld to check if the card can be added to it
	for( unsigned currMeldIdx = 1; currMeldIdx < m_handCard.size(); ++currMeldIdx )
	{
		// checking if any of the meld's first card's rank is the same as 
		// the rank of the passed card
		if( m_handCard.at( currMeldIdx ).front()->GetRank() ==
			a_cardToAdd.GetRank() )
		{
			return { true, "" };
		}
	}

	return { false, "Card can not be melded" };
}

/* *********************************************************************
Function Name: AddNaturalCardToMeld
Purpose: To move the the card at index from actual hand and a already
	existing meld if possible
Parameters:
			a_handCardIdx, a unsigned integer. It holds the index of the
				the card at actual hand that need to be moved
			a_meldIdx, a unsigned integer. It holds the index of the
				meld to move the card to actual hand that need to be moved
Return Value: a pair of < bool, string >, < true, empty string > if the card was
				moved to a meld successfully. else  < false, message string >
Algorithm:
			1) if card is not a natural card return false
			2) else the card is a natural card
				call AddCardToMeld() and pass the a_handCardIdx, and the
				meld index as parameters
			3) if meld was successfull update the hasCanasta by calling
				UpdateCanasta()
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Hand::AddNaturalCardToMeld( unsigned a_handCardIdx, unsigned a_meldIdx )
{
	if( m_handCard.front().at( a_handCardIdx )->GetCardType() != ENUM_CardType::CARDTYPE_natural )
	{
		return { false, "Card at index " + std::to_string( a_handCardIdx ) + " is not a natural card" };
	}

	// holds the return value of AddCardToMeld
	std::pair<bool, std::string> returnVal;

	// trying to move the card to the meld
	returnVal = AddCardToMeld( a_handCardIdx, a_meldIdx );

	// if successfull
	if( returnVal.first )
	{
		// updating hasCanasta value
		UpdateCanasta();
	}

	return returnVal;
}

/* *********************************************************************
Function Name: AddWildCardToMeld
Purpose: To move the the wildcard at index from actual hand and a
	already existing meld if possible
Parameters:
			a_handCardIdx, a unsigned integer. It holds the index of the
				the card at actual hand that need to be moved
			a_meldIdx, a unsigned integer. It holds the index of the
				meld to move the card to actual hand that need to be moved
Return Value:
			a pair of < bool, string >, < true, empty string > if the card was
				moved to a meld successfully. else  < false, message string >
Algorithm:
			1) if card is not a wild card return false
			2) loop over the meld and count the number of wild card if it is 3
				return false
			3) call the addCardToMeld
			4) if meld was successfull update the hasCanasta by calling
				UpdateCanasta()return its value
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Hand::AddWildCardToMeld( unsigned a_handCardIdx, unsigned a_meldIdx )
{
	if( m_handCard.front().at( a_handCardIdx )->GetCardType() != ENUM_CardType::CARDTYPE_wildCard )
	{
		return { false, "Card at index " + std::to_string( a_handCardIdx ) + " is not a wild card" };
	}

	// counting the number of wildcard
	unsigned wildCardCount = 0;

	// looping over the meld to get the number of wild card in the meld
	for( unsigned cardIdx = 0; cardIdx < m_handCard.at( a_meldIdx ).size(); ++cardIdx )
	{
		if( m_handCard.at( a_meldIdx ).at( cardIdx )->GetCardType() == ENUM_CardType::CARDTYPE_wildCard )
		{
			++wildCardCount;
		}
	}

	if( wildCardCount == 3 )
	{
		return { false, "Cannot add to the meld, it already has 3 wildcards" };
	}

	// trying to move the card to the meld
	std::pair<bool, std::string> returnVal = AddCardToMeld( a_handCardIdx, a_meldIdx );

	// chekcing if the meld was a success
	if( returnVal.first )
	{
		// updating hasCanasta value
		UpdateCanasta();
	}

	return returnVal;
}


/* *********************************************************************
Function Name: AddRed3CardToMeld
Purpose: To move the the red 3 at index from actual hand and to a new
	meld if possible
Parameters:
			a_handCardIdx, a unsigned integer. It holds the index of the
				the card at actual hand that need to be moved
Return Value:
			a pair of < bool, string >, < true, empty string > if the card was
				moved to a meld successfully. else  < false, message string >
Algorithm:
			1) if card is not a red 3 return false
			2) insert the card at index 1 of the m_handCard
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Hand::AddRed3CardToMeld( unsigned a_handCardIdx )
{
	if( m_handCard.front().at( a_handCardIdx )->GetCardType() != ENUM_CardType::CARDTYPE_redThree )
	{
		return { false, "Card at index " + std::to_string( a_handCardIdx ) + " is not a red three card" };
	}

	// making a new meld at index 1 for the red 3
	m_handCard.insert( m_handCard.begin() + 1, std::vector<Card*> {} );

	// inserting the red 3 at index 1 of m_handCard as a new meld
	// removing the red 3 from actual hand
	// removing the card from the hand
	return AddCardToMeld( a_handCardIdx, 1 );
}

/* *********************************************************************
Function Name: MakeMeld
Purpose: To make a vaild meld
Parameters:
			a_handCardIdxList, a vector of unsigned integer. It holds
				the indexs of the card that are to be used to create a
				meld.
Return Value:
			a pair of < bool, string >, < true, empty string > if a meld
			was successfully made. else  < false, message string >
Algorithm:
			1) check the size of the passed vector if the passed vector
				is the less than 3 then return false
			2) declare two new vector of unsigned namely wildCardindexList,
				and naturalCardindexList
			3) create a new vector of const Card pointer named
				naturalCardPtrList
			4)	loop over the passed vector and check its card type
				5) if it is a natural card, add the card index to the
					naturalCardindexList and add the card's pointer to
					naturalCardPtrList
				6) if it is a wild card, add the card index to the
					wildCardindexList
				7) if it is a red three or black return false
			8) check if the wildCardindexList's size is more than 3,
					if yes return false
			9) check if the naturalCardindexList's size is less than 2,
					if yes return false
			10) check if all the natual cards have the same rank by using
				the all_of function, if false return false
			11) check if all the meld of the rank already exist in the
					hand, if true return false
			12) push back a new empty meld to m_handCard
			13) initialize a meldIndex and assign it the index of
				newly created meld
			14) sort the passed vector in decending order
			15) for all the card in the passed index add the card to
				newly created meld by using AddCardToMeld function.
Assistance Received: cppreference
********************************************************************* */
std::pair<bool, std::string> Hand::MakeMeld( std::vector<unsigned> a_handCardIdxList )
{
	// checking if the vector list has at lease 3 card index
	if( a_handCardIdxList.size() < 3 )
	{
		return { false, "Meld must have atleast three cards in it." };
	}

	// holds all of the wild cards's idx into another vectorlist that were passed
	std::vector<unsigned> wildCardindexList;

	// holds all of the natural cards's idx into another vectorlist that were passed
	std::vector<unsigned> naturalCardindexList;

	// holds all of the passed natural cards's contant pointer into another 
	// vectorlist. we use this to see if the rank of all natural cards to
	// meld are the same or not
	std::vector<const Card*> naturalCardPtrList;

	for( unsigned passedListIdx = 0; passedListIdx < a_handCardIdxList.size(); ++passedListIdx )
	{
		switch( m_handCard.front().at( a_handCardIdxList.at( passedListIdx ) )->GetCardType() )
		{

			case( ENUM_CardType::CARDTYPE_natural ):
			{
				// saving the passed index to the wildcard Index List
				naturalCardindexList.push_back( a_handCardIdxList.at( passedListIdx ) );

				// saving the natural card index and its pointer 
				naturalCardPtrList.push_back( m_handCard.front().at( naturalCardindexList.back() ) );
				break;
			}
			case( ENUM_CardType::CARDTYPE_wildCard ):
			{
				// saving the passed index to the wildcard Index List
				wildCardindexList.push_back( a_handCardIdxList.at( passedListIdx ) );
				break;
			}
			case( ENUM_CardType::CARDTYPE_redThree ):
			{
				return { false, "Meld can not have a Red 3" };
				break;
			}
			case( ENUM_CardType::CARDTYPE_blackThree ):
			{
				return { false, "Meld can not have a Black 3" };
				break;
			}
			default:
				break;
		}
	}

	// checking how many wild cards there were in the passed list
	if( wildCardindexList.size() > 3 )
	{
		return { false, "Meld can only have at most three wildcards in it." };
	}

	// checking how many natural cards there were in the passed list
	if( naturalCardindexList.size() < 2 )
	{
		return { false, "Meld should have atleat two natural card in it." };
	}

	// checking if all the natural cards have the same rank
	const char firstNaturalCardRank = naturalCardPtrList.front()->GetRank();
	bool areAllRankSame = std::all_of( naturalCardPtrList.begin(),
									   naturalCardPtrList.end(),
									   [firstNaturalCardRank]( const Card* a_card )
									   { return ( *a_card ).GetRank() == firstNaturalCardRank; } );
	if( !areAllRankSame )
	{
		return { false, "All the ranks of natural card in the meld are not the same." };
	}

	// chekcing if a meld for this rank already exist
	bool meldDoesNotExit = std::none_of( m_handCard.begin() + 1,
										 m_handCard.end(),
										 [firstNaturalCardRank]( const std::vector<Card*> a_meld )
										 { return a_meld.front()->GetRank() == firstNaturalCardRank; } );

	if( !meldDoesNotExit )
	{
		return { false, "Meld of the same rank already exist." };
	}

	// all the test were passed to creating a new meld 
	// so creating a new meld and adding the cards to the meld
	m_handCard.push_back( {} );

	unsigned meldIndex = m_handCard.size() - 1;

	// sort the a_handCardIdxList in desending order
	// we need to do this as AddCardToMeld funciton removes the card that
	// was added to the meld from the actual hand thus changing the order
	// of card in teh actual hand. 
	// so when we move card starting from the back of the acutal hand as 
	// removing the card at from the back does not affect the index of the 
	// of the card from at the start
	std::sort( a_handCardIdxList.rbegin(), a_handCardIdxList.rend() );


	// holds the return value of AddCardToMeld
	std::pair<bool, std::string> returnVal;

	// adding the card from the back
	for( unsigned passedListIdx = 0;
		 passedListIdx < a_handCardIdxList.size();
		 ++passedListIdx )
	{
		returnVal = AddCardToMeld( a_handCardIdxList.at( passedListIdx ), meldIndex );

		if( !returnVal.first )
		{
			break;
		}
	}

	// updating m_hasCanasta
	UpdateCanasta();

	return returnVal;
}

/* *********************************************************************
Function Name: SwapHandCardPos
Purpose: To swap out the actual hand card at the passed indexs
Parameters:
			a_handCardIdx1, a unsigned integer. It holds the index of the
				the card at actual hand that whose position is to be
				swapped with the a_handCardIdx2
			a_handCardIdx2, a unsigned integer. It holds the index of the
				another card at actual hand that whose position is to be
				swapped with the a_handCardIdx1
Return Value: true to indicate the swapping was successful
Algorithm:
			1) create a temp card pointer and assign it the pointer to the
				card at first vector of m_handCard at index a_handCardIdx1
			2) assign the element at index a_handCardIdx1 of the first
				vector of m_handCard  the element at index a_handCardIdx2
				of the first vector of m_handCard.
			3) assign the element at index a_handCardIdx2 of the first
				vector of m_handCard  the tempCard pointer

Assistance Received: none
********************************************************************* */
bool Hand::SwapHandCardPos( unsigned a_handCardIdx1, unsigned a_handCardIdx2 )
{
	Card* tempCardPtr = m_handCard.front().at( a_handCardIdx1 );
	m_handCard.front().at( a_handCardIdx1 ) = m_handCard.front().at( a_handCardIdx2 );
	m_handCard.front().at( a_handCardIdx2 ) = tempCardPtr;

	return true;
}

/* *********************************************************************
Function Name: TakeOutWildCard
Purpose: To take out a wild card from a meld. It dissolves the meld if
	neccessary
Parameters:
			a_meldIdx, a unsigned integer. It holds the index of the
				the meld whose wild card is to be takenout.
			a_meldcardIdx, a unsigned integer. It holds the index of the
				wildcard in the meld that needs to be taken out
Return Value:
			a pair of < bool, string >, < true, empty string > if
				wild card was taken out successfully . else
				< false, message string >
Algorithm:
			1) check if the card at the passed index is a wild card,
				if not return false.
			2) remove the wild card from meld and move it to the
				actual hand
			3) check if the meld's size is more than 3 if not
				dissolve the meld by moving all the card to the
				actual hand and remove the meld itself

Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Hand::TakeOutWildCard( unsigned a_meldcardIdx,
													unsigned a_meldIdx )
{
	// checking if the a_meldcardIdx is a wild card or not 
	if( m_handCard.at( a_meldIdx ).at( a_meldcardIdx )->GetCardType() !=
		ENUM_CardType::CARDTYPE_wildCard )
	{
		return { false, "Can not take out the card. It is not a wild card" };
	}

	// taking out the card and pushing it to actual hand and 
	// removing it form the meld
	m_handCard.front().push_back( m_handCard.at( a_meldIdx ).at( a_meldcardIdx ) );
	m_handCard.at( a_meldIdx ).at( a_meldcardIdx ) = nullptr;
	m_handCard.at( a_meldIdx ).erase( m_handCard.at( a_meldIdx ).begin() + a_meldcardIdx );

	// checking if the meld still has 3 cards in it, if not 
	// disolving the meld and moving the card to hand
	// 
	// we only have to make sure that it has 3 cards in it as 
	// when we created the meld we know that it has atleast
	// 2 natural cards in it.

	if( m_handCard.at( a_meldIdx ).size() < 3 )
	{
		// moving all the card to actual hand
		for( unsigned cardIdx = 0;
			 cardIdx < m_handCard.at( a_meldIdx ).size();
			 ++cardIdx )
		{
			m_handCard.front().push_back( m_handCard.at( a_meldIdx ).at( cardIdx ) );
			m_handCard.at( a_meldIdx ).at( cardIdx ) = nullptr;
		}
		// removing the empty meld
		m_handCard.erase( m_handCard.begin() + a_meldIdx );

		return { true,"disolvingTheMeld" };
	}


	return { true,"" };
}

/* *********************************************************************
Function Name: Discard
Purpose: to through a card to the discard pile
Parameters:
			a_handCardIdx, a unsigned integer. It holds the index of the
				card in the actual hand that needs to be discarded
Return Value: pointer to the dynamically allocated discarded card
Algorithm:
			1) cretate a temporary card ptr using the card at the
				passed index of the actual hand.
			2) delete and replace the card at the passed index of the
				actual hand with nullptr and remove the elemele by
				using erase()
			3) return the temporary card ptr
Assistance Received: none
********************************************************************* */
Card Hand::Discard( unsigned a_handCardIdx )
{
	// creating a temp card 
	Card tempCard( *m_handCard.front().at( a_handCardIdx ) );

	// deleting the card at the actual hand
	delete ( m_handCard.front().at( a_handCardIdx ) );
	m_handCard.front().at( a_handCardIdx ) = nullptr;

	// removing the deleted card from the actual hand
	m_handCard.front().erase( m_handCard.front().begin() + a_handCardIdx );

	return tempCard;
}

/* *********************************************************************
Function Name: PrintHand
Purpose: To print out the m_hand
Parameters: none
Return Value: none
Algorithm:
			1) iterate over m_hand at 0th index 10 at a time and print
				print the card by calling GetRankSuit()
			2) iterate over rest of the m_hand as meld and print
				each vectors of cards by calling GetRankSuit()
Assistance Received: none
********************************************************************* */
void Hand::PrintHand()
{
	// iterating over hand cards and calling GetRankSuit funciton
	std::cout << "Hand: " << std::endl;
	std::vector<Card*>::iterator currPtr = m_handCard.front().begin();
	while( currPtr != m_handCard.front().end() )
	{

		std::string toPrint = "";
		unsigned count;
		for( count = 0; count < 10; ++count )
		{
			// to prevent we do not go over the last element
			if( currPtr == m_handCard.front().end() )
			{
				break;
			}

			toPrint += ( *currPtr )->GetRankSuit();
			toPrint += " ";
			++currPtr;
		}
		std::cout << std::setw( 5 ) << "";
		std::cout << toPrint << std::endl;
	}

	std::cout << std::endl;

	// iterating over rest of the m_handCards and print the meld
	std::cout << "Melds: " << std::endl;
	std::vector<std::vector<Card*>>::iterator currMeldPtr = m_handCard.begin() + 1;
	while( currMeldPtr != m_handCard.end() )
	{
		std::cout << std::setw( 5 ) << "";
		std::vector<Card*>::iterator currPtr = currMeldPtr->begin();
		while( currPtr != currMeldPtr->end() )
		{
			std::cout << ( *currPtr )->GetRankSuit() << " ";
			++currPtr;

		}
		std::cout << std::endl;
		++currMeldPtr;
	}
	std::cout << std::endl;
}


/* *********************************************************************
Function Name: TallyPoints
Purpose: To tally up the point of the hand
Parameters: none
Return Value: tallyed up point, does not include go out point
Algorithm:
			1) iterate over m_hand at 0th index 10 at a time and print
				print the card by calling GetRankSuit()
			2) iterate over rest of the m_hand as meld and print
				each vectors of cards by calling GetRankSuit()
Assistance Received: none
********************************************************************* */
const int Hand::TallyPoints() const
{
	int totalPoint = 0;

	// adding the point in the meld
	for( unsigned meldIdx = 1; meldIdx < m_handCard.size(); ++meldIdx )
	{
		bool isAllNaturalCard = true;
		// adding up the points of each card in the meld
		for( unsigned cardIdx = 0;
			 cardIdx < m_handCard.at( meldIdx ).size();
			 ++cardIdx )
		{
			totalPoint += m_handCard.at( meldIdx ).at( cardIdx )->GetPoint();

			// checking if the card is a naturalcard
			if( m_handCard.at( meldIdx ).at( cardIdx )->GetCardType() !=
				ENUM_CardType::CARDTYPE_natural )
			{
				isAllNaturalCard = false;
			}
		}

		// checking if this meld was a conasta
		if( IsCanasta( meldIdx ) )
		{
			// chekcing if the meld was all natural cards
			if( isAllNaturalCard )
			{
				totalPoint += 500;
			}
			else
			{
				totalPoint += 300;
			}
		}
	}

	// subtracting the point  of the cards in the actual hand
	for( unsigned cardIdx = 0;
		 cardIdx < m_handCard.front().size();
		 ++cardIdx )
	{
		totalPoint -= m_handCard.front().at( cardIdx )->GetPoint();
	}

	return totalPoint;
}

/* *********************************************************************
Function Name: AddCardToMeld
Purpose: To move the the card at index from actual hand and a already
	existing meld if possible.
Parameters:
			a_handCardIdx, a unsigned integer. It holds the index of the
				the card at actual hand that need to be moved
			a_meldIdx, a unsigned integer. It holds the index of the
				meld to move the card to actual hand that need to be moved
Return Value: a pair of < bool, string >, < true, empty string > if the card was
				moved to a meld successfully. else  < false, mesage string >
Algorithm:
			1) for meld vector at a_meldIdx, get the first card and
					compare the rank. if they are the same then
					move the card to the meld, sort the meld and
					return true
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Hand::AddCardToMeld( unsigned a_handCardIdx, unsigned   a_meldIdx )
{
	// trying to move the card to the meld
	// a card can move to a meld if the meld is empty, 
	// or first card of the meld is a wild card this only happens 
	//		we are making a new meld and is safe to do as the
	//		card are already tested
	// or the rank of the first card in the meld is same as the 
	//		rank of the passed card,
	// or the passed card is a wild card
	if( m_handCard.at( a_meldIdx ).empty()
		|| ( m_handCard.at( a_meldIdx ).front()->GetCardType() ==
			 ENUM_CardType::CARDTYPE_wildCard )
		|| ( m_handCard.at( a_meldIdx ).front()->GetRank() ==
			 m_handCard.front().at( a_handCardIdx )->GetRank() )
		|| ( m_handCard.front().at( a_handCardIdx )->GetCardType() ==
			 ENUM_CardType::CARDTYPE_wildCard ) )
	{
		// moving the card to the meld
		m_handCard.at( a_meldIdx ).push_back( m_handCard.front().at( a_handCardIdx ) );

		// removing the card from the hand
		m_handCard.front().at( a_handCardIdx ) == nullptr;
		m_handCard.front().erase( m_handCard.front().begin() + a_handCardIdx );

		SortMeld( a_meldIdx );
		return { true, "" };
	}

	return { false, "Card can not be added to the meld" };
}

/* *********************************************************************
Function Name: SortMeld
Purpose: To desendingly sort the meld passed by a_meldIdx
Parameters: a_meldIdx, a unsigned integer. It holds the index of the
				meld to move the card to actual hand that need to be moved
Return Value: none
Algorithm:
			call the sort algorithm from stl library
Assistance Received: cplusplus
********************************************************************* */
std::pair<bool, std::string> Hand::SortMeld( unsigned a_meldIdx )
{
	// validating the passed meld index
	if( a_meldIdx >= m_handCard.size() )
	{
		return { false,"Invalid meld index" };
	}

	std::sort( m_handCard.at( a_meldIdx ).begin(),
			   m_handCard.at( a_meldIdx ).end(),
			   []( Card* a_first, Card* a_second ) {return ( ( *a_first ) > ( *a_second ) ); } );

	return { true, "" };

}
