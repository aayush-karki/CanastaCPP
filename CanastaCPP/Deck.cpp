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
			1) initialize a struct ST_ValidRankSuit and name it
				validRankSuit
			2) repeate twice
				3) for first 4 char in m_suitList
					4) for first 13 char in stmm_rankList
						5) create a new Card object
						6) push the newly created card object to m_stock
				7) create 2 new card object for J1 and J2
Assistance Received: none
********************************************************************* */
Deck::Deck()
{
	ST_ValidRankSuit validRankSuit;

	// creating the deck of cards
	for( unsigned currDeckNum = 0; currDeckNum < 2; ++currDeckNum )
	{
		for( unsigned currSuitIdx = 0; currSuitIdx < 4; ++currSuitIdx )
		{
			for( unsigned currRankIdx = 0; currRankIdx < 13; ++currRankIdx )
			{
				m_stock.push_back( new Card( validRankSuit.stm_rankList.at( currRankIdx ),
											 validRankSuit.stm_suitList.at( currSuitIdx ) ) );
			}
		}

		// creating a card for joker1 and joker2 and adding it to the m_stock
		m_stock.push_back( new Card( validRankSuit.stm_rankList.at( 13 ),
									 validRankSuit.stm_suitList.at( 4 ) ) );
		m_stock.push_back( new Card( validRankSuit.stm_rankList.at( 13 ),
									 validRankSuit.stm_suitList.at( 5 ) ) );
	}
}

/* *********************************************************************
Function Name: Deck
Purpose: To construct a Deck object and to populate its member variables.
			m_stock is populated using the passed parameter. while the
			remaining cards not in the passed string are kept in m_dealt.
Parameters:
			a_stock, a string containing the rank and suit of cards in the
				m_stock. Each card is seperated by blank space
Return Value: none
Algorithm:
			1) Initialize a new deck called tempDeck
			2) Initialize a new vector of string RankSuitList
			3) extract the ranksuit from each card of tempDeck and add
				it to the back of RankSuitList
			4) initialize a string stream with the passed string as
				parameter called passedStringStream
			5) initialize a string called streamExtractdRankSuit
				and assign it a value of ""
			6) initialize a unsinged interger called totalSwappedNum
				and assign it a value of 0
			while(  a ranksuit can be extracted form passedStringStream
				into the streamExtractdRankSuit )
			{
				7) initialize a unsinged interger called firstUnswappedIdx
					and assign it a value of RankSuitList.size() - 1 -
					totalSwappedNum
				8) use std::find() to find the position of the ranksuit
					in RankSuitList using the streamExtractdRankSuit
					starting form start of the list to (end of
					RankSuitList's - totalSwappedNum) and
					save its return to returedIte
				9) use std::distance to get the distance between the
					found iterator and the begin() and save it to
					rankSuitIdx
				10) For RankSuitList swap the string at the index
					indicated by rankSuitIdx with the string at index
					firstUnswappedIdx
				11) For the m_stock of tempDeck swap the card at the
					index indicated by rankSuitIdx with the string at index
					firstUnswappedIdx
				12) increment the totalSwappedNum
			}
			13) for totalSwappedNum times
				14) deal tempDeck
			15) swap the m_stock of tempDeck with the m_dealt of this deck
			16) swap the m_dealt of tempDeck with the m_stock of this deck
Assistance Received: none
********************************************************************* */
Deck::Deck( std::string a_stock )
{
	// initailizing the temp deck
	Deck tempDeck;

	// extracting the card of the temp deck
	// this extracted card is in the same order of as the deck
	// so to find at what pos our stock card is in the deck we 
	// use this extracted ranksuit.
	std::vector<std::string> RankSuitList;
	std::vector<Card*>::iterator currStockCardPtr = tempDeck.m_stock.begin();

	while( currStockCardPtr != tempDeck.m_stock.end() )
	{
		RankSuitList.push_back( ( *currStockCardPtr )->GetRankSuit() );
		++currStockCardPtr;
	}

	// rearraning the cards in the m_stock of the tempDeck to match the
	// order of cards in the passed a_stock
	std::stringstream passedStringStream( a_stock );
	std::string extractdRankSuit = "";
	unsigned totalSwappedNum = 0;

	while( passedStringStream >> extractdRankSuit )
	{
		// finding the index of first unswapped element from the back
		unsigned firstUnswappedIdx = RankSuitList.size() - 1 - totalSwappedNum;

		// finding the position fo the extractdRankSuit
		// in the extractedRankSuitList
		std::vector<std::string>::iterator returedIte =
			std::find( RankSuitList.begin(),
					   RankSuitList.end() - totalSwappedNum,
					   extractdRankSuit );

		// chekcing if the returedIte is not an error
		// this should not be the case as we had validated it before 
		// todo: make this try catch
		if( returedIte == RankSuitList.end() )
		{
			std::cerr << "Extracted Rank and Suit not in the unswapped list!!!!!"
				<< std::endl;
			continue;
		}

		// gettng the index of the rank and suit in the vector
		int rankSuitIdx = std::distance( RankSuitList.begin(), returedIte );

		// swapping the string
		std::string tempRankSuit = RankSuitList.at( firstUnswappedIdx );
		RankSuitList.at( firstUnswappedIdx ) = RankSuitList.at( rankSuitIdx );
		RankSuitList.at( rankSuitIdx ) = tempRankSuit;

		// swapping the card
		Card* tempCard = tempDeck.m_stock.at( firstUnswappedIdx );
		tempDeck.m_stock.at( firstUnswappedIdx ) = tempDeck.m_stock.at( rankSuitIdx );
		tempDeck.m_stock.at( rankSuitIdx ) = tempCard;

		// incrementing the totalSwappedNum as we just swapped a element
		++totalSwappedNum;
	}

	// dealing the card for tempDeck firstUnswappedIdx times
	// so that the dealt card list matches out pass m_stock
	for( unsigned toatlCardDealt = 0; toatlCardDealt < totalSwappedNum; ++toatlCardDealt )
	{
		tempDeck.DealCard();
	}

	// swapping the m_stock of tempCard with m_dealt of this deck
	std::swap( tempDeck.m_stock, this->m_dealt );

	// swapping the m_dealt of tempCard with m_stock of this deck
	std::swap( tempDeck.m_dealt, this->m_stock );
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
	while( currPtr != m_dealt.end() )
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
			a_other, a constant object of Deck class passed by
				reference. It holds the Deck object to be copied.
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
	const std::vector<Card*> tempStock = a_other.GetStock();

	for( std::vector<Card*>::const_iterator currPtr = tempStock.begin();
		 currPtr != tempStock.end();
		 ++currPtr )
	{
		m_stock.push_back( new Card( ( *currPtr )->GetRankSuit() ) );
	}

	// copying the data from m_stock of the passed deck to this deck
	// dynamically created a Card
	const std::vector<Card*> tempDealt = a_other.GetDealt();
	for( std::vector<Card*>::const_iterator currPtr = tempDealt.begin();
		 currPtr != tempDealt.end();
		 ++currPtr )
	{
		m_dealt.push_back( new Card( ( *currPtr )->GetRankSuit() ) );
	}
}

/* *********************************************************************
Function Name: operator=
Purpose: To deep-copy the passed deck object's member variables data into
		this deck object
Parameters:
			a_other, a constant object of deck class passed by
				reference. It holds a deck object that is used to assign
				this deck object.
Return Value: its own memory address
Algorithm:
			1) check for self assignment, if yes then return the
				pointer to self
			2) inialize a tempDeck by using the copy constructor
			3) swap the m_stock of the temp deck object with m_stock of
				this object
			4) swap the m_dealt of the temp deck object with m_dealt of
				this object
Assistance Received: none
********************************************************************* */
Deck& Deck::operator=( const Deck& a_other )
{
	// checking for self assignment
	if( this == &a_other )
	{
		return *this;
	}

	// creating a copy of the passed deck object
	Deck tempDeck( a_other );

	// swapping m_stock
	std::swap( this->m_stock, tempDeck.m_stock );
	std::swap( this->m_dealt, tempDeck.m_dealt );
}

/* *********************************************************************
Function Name: GetStockString
Purpose: Getter function to get the stock in the string format
Parameters: none
Return Value:
			const string, containing the rank and suit of
				cards which represents stock in the deck. Each card
				is seperated by blank space. And the first rankSuit pair
				represent the card that is going to be dealt next.
Algorithm:
			1) create a string
			2)	for each card in the stock add that to the back of s
				tring created in step 1
Assistance Received: none
********************************************************************* */
const std::string Deck::GetStockString() const
{
	// if the are no card in the stock return ""
	if( m_stock.empty() )
	{
		return "";
	}

	// creating actual hand
	std::string stockStr = "";
	for( unsigned cardIdx = 0; cardIdx < m_stock.size(); ++cardIdx )
	{
		// adding cards to the string
		stockStr += m_stock.at( cardIdx )->GetRankSuit() + " ";
	}

	// removing the last " "
	std::string actualHandStrNoLastSpace = "";

	for( unsigned strIdx = 0; strIdx < stockStr.size() - 1; ++strIdx )
	{
		actualHandStrNoLastSpace += stockStr.at( strIdx );
	}

	std::cout << actualHandStrNoLastSpace << ":::::" <<std::endl;
	return actualHandStrNoLastSpace;
}

/* *********************************************************************
Function Name: DealCard
Purpose: to return a card from m_stock and move it from m_stock
	to m_dealt
Parameters: none
Return Value: a Card that was in the end of m_stock, returns by value
Algorithm:
			1) moves the card at the end of m_stock to m_dealt
			2) return the card
Assistance Received: none
********************************************************************* */
const Card Deck::DealCard()
{
	// we do not need to deallocate the card from stock as we are 
	// pushing it to dealt
	m_dealt.push_back( m_stock.at( 0 ) );
	m_stock.at( 0 ) = nullptr;
	m_stock.erase( m_stock.begin() );

	return *( m_dealt.back() );
}

/* *********************************************************************
Function Name: PrintDeck
Purpose: To print out the m_stock and m_dealt
Parameters: none
Return Value: none
Algorithm:
			1) print m_stock 10 at a time
			2) print m_dealt 10 at a time
Assistance Received: none
********************************************************************* */
void Deck::PrintDeck()
{
	// iterating over m_stock and calling GetRankSuit funciton
	std::cout << "m_stock: " << std::endl;
	std::vector<Card*>::iterator currPtr = m_stock.begin();
	while( currPtr != m_stock.end() )
	{

		std::string toPrint = "";
		unsigned count;
		for( count = 0; count < 10; ++count )
		{
			// to prevent we do not go over the last element
			if( currPtr == m_stock.end() )
			{
				break;
			}

			toPrint += ( *currPtr )->GetRankSuit();
			toPrint += " ";
			++currPtr;
		}
		std::cout << toPrint << std::endl;
	}
	std::cout << std::endl;
	std::cout << "total nubmer of cards in m_stock: " << m_stock.size() <<
		std::endl << std::endl;
	// iterating over m_dealt and calling GetRankSuit funciton
	std::cout << "m_dealt: " << std::endl;
	currPtr = m_dealt.begin();
	while( currPtr != m_dealt.end() )
	{
		std::string toPrint = "";
		unsigned count;
		for( count = 0; count < 10; ++count )
		{
			// to prevent we do not go over the last element
			if( currPtr == m_dealt.end() )
			{
				break;
			}

			toPrint += ( *currPtr )->GetRankSuit();
			toPrint += " ";
			++currPtr;
		}
		std::cout << toPrint << std::endl;
	}
	std::cout << std::endl;

	std::cout << "total nubmer of cards in m_dealt: " << m_dealt.size() <<
		std::endl << std::endl;
}

/* *********************************************************************
Function Name: Shuffel
Purpose: To randomly shuffle the order of cards in m_stock
Parameters: none
Return Value: true to indicate successful shuffel
Algorithm:
			1) Call ConsodilateDeck fuinction to move card in m_dealt to
				m_stock
			2) call random_shuffle function from standard library
Assistance Received: cppreference
********************************************************************* */
bool Deck::Shuffel()
{
	// moving all the card in m_dealt to m_stock
	ConsodilateDeck();

	// TODO use a std::chrono::system_clock::now().time_since_epoch().count(); insted of 1 for seed
	std::shuffle( m_stock.begin(), m_stock.end(), std::default_random_engine( 1 ) );

	return true;
}

/* *********************************************************************
Function Name: ConsodilateDeck
Purpose: To move all the card in m_dealt to m_stock
Parameters: none
Return Value: true to indicate successful deck consodilatiion
Algorithm:
			1) for all the element in m_dealt
				2) push_back that element to m_stock
				3) set m_dealt.at that element to nullptr
Assistance Received: none
********************************************************************* */

bool Deck::ConsodilateDeck()
{
	// moving all the card in m_dealt to m_stock
	std::vector<Card*>::iterator currPtr = m_dealt.begin();
	while( currPtr != m_dealt.end() )
	{
		m_stock.push_back( *currPtr );
		*currPtr = nullptr;
		++currPtr;
	}

	m_dealt.clear();

	return true;
}
