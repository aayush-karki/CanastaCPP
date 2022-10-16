/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Round.h"

/* *********************************************************************
Function Name: Round
Purpose: To construct a Round object and to populate its member variables.
Parameters:
			a_currRoundNum, unsigned integer representing the current
				round number.
			a_playerTurn, ENUM_PlayerTurn represting whose turn it is right
				now.
			a_compTotalScore, a unsinged integer containing the comp's
				total score.
			a_compActualHand, a string containing the rank and suit of
				cards which represents comp's actual hand card. Each card
				is seperated by blank space.
			a_compMelds, a string containing the rank and suit of cards
				which represents comp's meld. Each card is seperated by
				blank space and each meld is inside '[' and ']'
			a_humanTotalScore, a unsinged integer containing the human's
				total score.
			a_humanActualHand, a string containing the rank and suit of
				cards which represents human's actual hand card. Each card
				is seperated by blank space.
			a_humanMelds, a string containing the rank and suit of cards
				which represents human's meld. Each card is seperated by
				blank space and each meld is inside '[' and ']'
			a_stockCards, a string containing the rank and suit of
				cards which represents stock in the deck. Each card
				is seperated by blank space. And the first rankSuit pair
				represent the card that is going to be dealt next.
			a_discardPile, a string containing the rank and suit of
				cards which represents discarded pile. Each card
				is seperated by blank space. And the first rankSuit pair
				represent the most recently discarded card
Return Value: none
Algorithm:
		1) set m_currRoundNum to 1
		2) set the m_roundOver to false
		3) set m_playerTurn to ENUM_PlayerTurn::TURN_uninitialized
		4) set initialize m_deck
		5) dynamically create 2 new player and add it to m_playerList
		6) populate the discard pile
Assistance Received: none
********************************************************************* */
Round::Round( unsigned a_currRoundNum,
			  ENUM_PlayerTurn a_playerTurn,
			  unsigned a_compTotalScore,
			  std::string a_compActualHand,
			  std::string a_compMelds,
			  unsigned a_humanTotalScore,
			  std::string a_humanActualHand,
			  std::string a_humanMelds,
			  std::string a_stockCards,
			  std::string a_discardPile ) :
	m_currRoundNum( a_currRoundNum ),
	m_roundOver( false ),
	m_roundStart( true ),
	m_playerTurn( a_playerTurn ),
	m_deck( a_stockCards )
{
	// initializing 2 players
	m_playerList.push_back( new Player( a_compTotalScore,
										a_compActualHand,
										a_compMelds ) );
	m_playerList.push_back( new Player( a_humanTotalScore,
										a_humanActualHand,
										a_humanMelds ) );

	// initialize the discard Pile
	std::stringstream passedStringStream( a_discardPile );
	std::string extractdRankSuit = "";

	// populaitng the vector at 0th index of m_handCard
	// as the 0th vector is the place where the hand card are placed

	// populating the a tempDiscardPile
	m_discardPile.reserve( a_discardPile.size() / 3 + 5 );
	while( passedStringStream >> extractdRankSuit )
	{
		// validaitng the size of the extracted string
		if( extractdRankSuit.size() != 2 )
		{
			std::cerr << "Extracted Rank and Suit in the m_handCards is not length 2" << std::endl;
			continue;
		}

		m_discardPile.insert( m_discardPile.begin(), Card( extractdRankSuit ) );
	}

}

/* *********************************************************************
Function Name: Round
Purpose: To destruct a Round object and to its dynamically allocated
			memory
Parameters: none
Return Value: none
Algorithm:
			1) loop over m_playerList and delete each element
Assistance Received: none
********************************************************************* */
Round::~Round()
{
	for( unsigned idx = 0; idx < m_playerList.size(); ++idx )
	{
		delete  m_playerList.at( idx );
	}
}

/* *********************************************************************
Function Name: Round
Purpose: To create a new Round object and copy the passed Round object's
		member variables data into the newly created Round object
Parameters:
			a_other, a constant object of Round class passed by
				reference. It holds the Round object to be copied.
Return Value: none
Algorithm:
			1) assigns each of the member of the passed Round object
				to the correspnding member variable of this object
Assistance Received: none
********************************************************************* */
Round::Round( const Round& a_other ) :
	m_currRoundNum( a_other.m_currRoundNum ),
	m_roundOver( a_other.m_roundOver ),
	m_roundStart( a_other.m_roundStart ),
	m_playerTurn( a_other.m_playerTurn ),
	m_deck( a_other.m_deck )
{
	// copying the player list
	m_playerList.push_back( new Player( *a_other.m_playerList.at( 0 ) ) );
	m_playerList.push_back( new Player( *a_other.m_playerList.at( 1 ) ) );
}

/* *********************************************************************
Function Name: operator=, assignment operator
Purpose: To copy the passed Round object's member variables data into
		this Round object
Parameters:
			a_other, a constant object of Round class passed by reference.
				It holds a Round object that is used to assign this
				Round object.
Return Value: its own memory address
Algorithm:
			1) check for self assignment if yes return itself
			2) assigns each of the member of the passed Round object
				to the correspnding member variable of this object
			3) return its own memory address
Assistance Received: none
********************************************************************* */
Round& Round::operator=( const Round& a_other )
{
	// checking for self assigmnet 
	if( this == &a_other )
	{
		return *this;
	}

	// copying the data
	this->m_currRoundNum = a_other.m_currRoundNum;
	this->m_roundOver = a_other.m_roundOver;
	this->m_roundStart = a_other.m_roundStart;
	this->m_playerTurn = a_other.m_playerTurn;
	this->m_deck = a_other.m_deck;

	// copying the player list
	for( unsigned idx = 0; idx < a_other.m_playerList.size(); ++idx )
	{
		this->m_playerList.push_back( new Player( *( a_other.m_playerList.at( idx ) ) ) );
	}

	return *this;
}

/* *********************************************************************
Function Name: EmptyDiscardPile
Purpose: empties the discard stack
Parameters: none
Return Value: returns true to indicate that the stack was empited
Algorithm:
			1) for all the card in the discard pile pop it out
Assistance Received: none
********************************************************************* */
bool Round::EmptyDiscardPile()
{
	// poping out the whole stack
	m_discardPile.empty();

	return m_discardPile.empty();
}

/* *********************************************************************
Function Name: ClearScreen
Purpose: Clears the terminal screen
Parameters: none
Return Value: none
Algorithm: none
Assistance Received: cplusplus forum
********************************************************************* */
void Round::ClearScreen()
{
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "\x1B[2J\x1B[H";
}

/* *********************************************************************
Function Name: PrintGameTitle
Purpose: To print out the game title. It is goning to be the top most
	thing in game frame
Parameters: none
Return Value: none
Algorithm:
			1) Prints out the Game title
Assistance Received: none
********************************************************************* */
void Round::PrintGameTitle()
{
	// as this is the top most thing in the frame 
	// clearing the screen
	ClearScreen();

	// printing game title
	std::cout << std::setw( 50 ) << std::setfill( 'x' ) << "" << std::endl;
	std::cout << std::setw( 25 ) << "    Canasta" << " Game    " <<
		std::setw( 16 ) << "" << std::endl;
	std::cout << std::setw( 50 ) << "" << std::setfill( ' ' ) << std::endl
		<< std::endl;
}

/* *********************************************************************
Function Name: PrintRound
Purpose: To print out the round information
Parameters: none
Return Value: none
Algorithm:
			1) Print Round number
			2) Call m_playerHand1's PrintHand function
			3) print discard pile and stock pile
			4) Call m_playerHand2's PrintHand function
Assistance Received: none
********************************************************************* */
void Round::PrintRound()
{
	// clearing the window
	ClearScreen();

	// printing the game tile
	PrintGameTitle();

	// printing round number
	std::cout << std::setw( 50 ) << std::setfill( '-' ) << ""
		<< std::setfill( ' ' ) << std::endl;
	std::cout << std::setw( 28 ) << "Round: " << m_currRoundNum << std::endl;
	std::cout << std::setw( 50 ) << std::setfill( '-' ) << ""
		<< std::setfill( ' ' ) << std::endl;

	// printing player 1 details
	std::cout << "Computer:" << std::endl;
	m_playerList.front()->PrintPlayer();

	// printing the discard and stock pile
	std::cout << std::setw( 30 ) << std::setfill( '-' ) << ""
		<< std::setfill( ' ' ) << std::endl;

	PrintDiscardAndStock();

	std::cout << std::setw( 20 ) << "" << std::setw( 30 )
		<< std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	// printing player 2 details
	std::cout << "Player:" << std::endl;
	m_playerList.back()->PrintPlayer();
	std::cout << std::setw( 50 ) << std::setfill( '-' ) << ""
		<< std::setfill( ' ' ) << std::endl << std::endl;

	// printing any messages
	Message::PrintMessages();

	// clearing the messages
	Message::ClearMessages();
}

/* *********************************************************************
Function Name: StartNewRound
Purpose: Sets up a new round
Parameters: none
Return Value: true if a new round was setup
Algorithm:
			1) Print Round number
			2) Call m_playerHand1's PrintHand function
			3) print discard pile and stock pile
			4) Call m_playerHand2's PrintHand function
Assistance Received: none
********************************************************************* */
bool Round::StartNewRound()
{
	// resetting the round

	// empty discarded pile 
	EmptyDiscardPile();

	// clearing both player's hand
	for( unsigned currPlayerIdx = 0; currPlayerIdx < m_playerList.size(); ++currPlayerIdx )
	{
		m_playerList.at( currPlayerIdx )->EmptyHand();
	}

	// consolodating deck
	m_deck.ConsodilateDeck();

	// suffeling the deck
	m_deck.Shuffel();

	// dealing 15 cards to each player
	for( unsigned currPlayerIdx = 0; currPlayerIdx < m_playerList.size(); ++currPlayerIdx )
	{
		for( unsigned cardInHandNum = 0; cardInHandNum < 15; ++cardInHandNum )
		{
			// deal a card untill player gets a non red three card
			while( !m_playerList.at( currPlayerIdx )->AddCardToHand( m_deck.DealCard() ) )
			{
			}
		}
	}

	// next dealt card is added to the discard pile to start the pile
	// keep adding a card to the pile until a natural or a black three is found
	bool wildOrRedThree = true;
	do
	{
		Card dealtCard = m_deck.DealCard();

		if( dealtCard.GetCardType() == ENUM_CardType::CARDTYPE_natural ||
			dealtCard.GetCardType() == ENUM_CardType::CARDTYPE_blackThree )
		{
			wildOrRedThree = false;
		}

		// adding to discard pile
		m_discardPile.push_back( dealtCard );

	} while( wildOrRedThree );

	// round setup is complete 
	// seeing who goes first
	if( m_playerList.front()->GetTotalPoint() > m_playerList.back()->GetTotalPoint() )
	{
		// computer has more points so it goes first
		m_playerTurn = ENUM_PlayerTurn::TURN_computer;
	}
	else if( m_playerList.back()->GetTotalPoint() > m_playerList.front()->GetTotalPoint() )
	{
		// human has more points so it goes first
		m_playerTurn = ENUM_PlayerTurn::TURN_human;
	}
	else
	{
		// its a tie. Toss a coin
		std::string userInput;
		bool invalidInput = true;
		do
		{
			PrintRound();

			std::cout << "Tossing a coin to decide who starts the Round." << std::endl;
			std::cout << "Guess whether it is head or tails." << std::endl << std::endl;;
			std::cout << "Enter h for head or t for tail: ";


			std::getline( std::cin, userInput );

			if( userInput.size() == 1 && ( std::tolower( userInput.at( 0 ) ) == 'h' || std::tolower( userInput.at( 0 ) ) == 't' ) )
			{
				invalidInput = false;
			}
			else
			{
				Message::AddMessage( "Invalid Input!! Try Again!!" );
			}
		} while( invalidInput );

		// tossing a coin
		if( std::tolower( userInput.at( 0 ) ) == TossACoin() )
		{
			m_playerTurn = ENUM_PlayerTurn::TURN_human;
			Message::AddMessage( "You guess correctly! You start first" );
		}
		else
		{
			m_playerTurn = ENUM_PlayerTurn::TURN_computer;
			Message::AddMessage( "You guess incorrectly! Computer starts first" );
		}
	}

	return false;
}

/* *********************************************************************
Function Name: ContinueRound
Purpose: Continues the round
Parameters: none
Return Value: false if player chose to go back to main menu
Algorithm:
			1) Call TurnStartLogic function
Assistance Received: none
********************************************************************* */
bool Round::ContinueRound()
{
	PrintRound();

	// starting the turn
	std::pair<unsigned, std::vector<unsigned>> playerChoice;
	playerChoice = m_playerList.at( ( unsigned )m_playerTurn )->PlayerTurnController( m_playerList.at( ( unsigned )m_playerTurn ), m_discardPile );

	// logic for what to execute depending on what the choice was 
	// 
	//if( !playerChoice.first )
	//{
	//	// go back to main menu was pressed so
	//	// returning
	//	return false;
	//}

	return true;
}

/* *********************************************************************
Function Name: PrintDiscardAndStock
Purpose: To print out the discard and stock pile
Parameters: none
Return Value: none
Algorithm:
			1) Print Round number
			2) Call m_playerHand1's PrintHand function
			3) print discard pile and stock pile
			4) Call m_playerHand2's PrintHand function
Assistance Received: none
********************************************************************* */
void Round::PrintDiscardAndStock()
{
	// when discard pile is empty and stock is empty
	if( m_discardPile.size() == 0 && m_deck.IsStockEmpty() == true )
	{
		Print1DiscardAnd1Stock( "NA", "NA" );
	}
	// when discard pile is empty and stock has 1 card
	else if( m_discardPile.size() == 0 && m_deck.GetStock().size() == 1 )
	{
		Print1DiscardAnd1Stock( "NA", "**" );
	}
	// when discard pile is empty and stock more than 1 card
	else if( m_discardPile.size() == 0 && m_deck.GetStock().size() > 1 )
	{
		Print1DiscardAnd2Stock( "NA", "**" );
	}
	// when discard pile has 1 card and stock is empty
	else if( m_discardPile.size() == 1 && m_deck.IsStockEmpty() == true )
	{
		Print1DiscardAnd1Stock( m_discardPile.back().GetRankSuit(), "NA" );
	}
	//when discard pile has 1 card and stock has 1 card
	else if( m_discardPile.size() == 1 && m_deck.GetStock().size() == 1 )
	{
		Print1DiscardAnd1Stock( m_discardPile.back().GetRankSuit(), "**" );
	}
	// when discard pile has 1 card and stock more than 1 card
	else if( m_discardPile.size() == 1 && m_deck.GetStock().size() > 1 )
	{
		Print1DiscardAnd2Stock( m_discardPile.back().GetRankSuit(), "**" );

	}
	// when discard pile has mroe than 1 card and stock is empty
	else if( m_discardPile.size() > 1 && m_deck.IsStockEmpty() == true )
	{
		Print2DiscardAnd1Stock( m_discardPile.back().GetRankSuit(), "NA" );
	}
	//when discard pile has more than 1 card and stock has 1 card
	else if( m_discardPile.size() > 1 && m_deck.GetStock().size() == 1 )
	{
		Print2DiscardAnd1Stock( m_discardPile.back().GetRankSuit(), "**" );
	}
	// when discard pile has more than 1 card and stock more than 1 card
	else if( m_discardPile.size() > 1 && m_deck.GetStock().size() > 1 )
	{
		Print2DiscardAnd2Stock( m_discardPile.back().GetRankSuit(), "**" );
	}
	std::cout << "\t" << "Discard Pile" << std::setw( 5 ) << "" << "Stock Pile" << std::endl;
}

/* *********************************************************************
Function Name: Print1DiscardAnd1Stock
Purpose: To print out the discard and stock pile when there is
	1 or less number of discard card and 1 or less number of
	stock cards in case there are no card instock pile show NA
Parameters:
			a_discardCard, a constant string passed by value.
				It holds the rank and suit of top card in the
				discard pile. If the discard pile is empty
				then pass "NA"
			a_handCard, a constant string passed by value.
				It holds the "**" if the stock pile is not empty.
				else If the discard pile is empty
				then holds "NA"
Return Value: none
Algorithm:
			1) print the cards
Assistance Received: none
********************************************************************* */
void Round::Print1DiscardAnd1Stock( const std::string a_discardCard,
									const std::string a_handCard )
{
	std::cout << "\t" << " ---- " << std::setw( 10 ) << "" << " ---- " << std::endl;
	std::cout << "\t" << "|    |" << std::setw( 10 ) << "" << "|    |" << std::endl;
	std::cout << "\t" << "| " << a_discardCard << " |" << std::setw( 10 ) << "" << "| " << a_handCard << " |" << std::endl;
	std::cout << "\t" << "|    |" << std::setw( 10 ) << "" << "|    |" << std::endl;
	std::cout << "\t" << " ---- " << std::setw( 10 ) << "" << " ---- " << std::endl;
}

/* *********************************************************************
Function Name: Print2DiscardAnd1Stock
Purpose: To print out the discard and stock pile when there is
	more than 1 discard card and 1 or less number of
	stock cards in case there are no card instock pile show NA
Parameters:
			a_discardCard, a constant string passed by value.
				It holds the rank and suit of top card in the
				discard pile.
			a_handCard, a constant string passed by value.
				It holds the "**" if the stock pile is not empty.
				else If the discard pile is empty
				then holds "NA"
Return Value: none
Algorithm:
			1) print the cards
Assistance Received: none
********************************************************************* */
void Round::Print2DiscardAnd1Stock( const std::string a_discardCard,
									const std::string a_handCard )
{
	std::cout << "\t" << " ---- " << std::setw( 10 ) << "" << " ---- " << std::endl;
	std::cout << "\t" << "|    |-" << std::setw( 9 ) << "" << "|    |" << std::endl;
	std::cout << "\t" << "| " << a_discardCard << " | |" << std::setw( 8 ) << "" << "| " << a_handCard << " |" << std::endl;
	std::cout << "\t" << "|    | |" << std::setw( 8 ) << "" << "|    |" << std::endl;
	std::cout << "\t" << " ----  |" << std::setw( 8 ) << "" << " ---- " << std::endl;
	std::cout << "\t" << "  -----" << std::endl;
}

/* *********************************************************************
Function Name: Print1DiscardAnd2Stock
Purpose: To print out the discard and stock pile when there is
	1 or less number of discard card and more than 1
	stock cards in case there are no card in discard pile show NA
Parameters:
			a_discardCard, a constant string passed by value.
				It holds the rank and suit of top card in the
				discard pile. If the discard pile is empty
				then pass "NA"
			a_handCard, a constant string passed by value.
				It holds the "**" if the stock pile is not empty.
				else If the discard pile is empty
				then holds "NA"
Return Value: none
Algorithm:
			1) print the cards
Assistance Received: none
********************************************************************* */
void Round::Print1DiscardAnd2Stock( const std::string a_discardCard,
									const std::string a_handCard )
{
	std::cout << "\t" << " ---- " << std::setw( 10 ) << "" << " ---- " << std::endl;
	std::cout << "\t" << "|    |" << std::setw( 10 ) << "" << "|    |-" << std::endl;
	std::cout << "\t" << "| " << a_discardCard << " |" << std::setw( 10 ) << "" << "| " << a_handCard << " | |" << std::endl;
	std::cout << "\t" << "|    |" << std::setw( 10 ) << "" << "|    | |" << std::endl;
	std::cout << "\t" << " ---- " << std::setw( 10 ) << "" << " ----  |" << std::endl;
	std::cout << "\t" << "      " << std::setw( 10 ) << "" << "   ---- " << std::endl;
}

/* *********************************************************************
Function Name: Print2DiscardAnd2Stock
Purpose: To print out the discard and stock pile when there is
	more than 1 discarded card and more than 1 stock cards in case
	there are no card in discard pile show NA
Parameters:
			a_discardCard, a constant string passed by value.
				It holds the rank and suit of top card in the
				discard pile. If the discard pile is empty
				then pass "NA"
			a_handCard, a constant string passed by value.
				It holds the "**" if the stock pile is not empty.
				else If the discard pile is empty
				then holds "NA"
Return Value: none
Algorithm:
			1) print the cards
Assistance Received: none
********************************************************************* */
void Round::Print2DiscardAnd2Stock( const std::string a_discardCard,
									const std::string a_handCard )
{
	std::cout << "\t" << " ---- " << std::setw( 10 ) << "" << " ---- " << std::endl;
	std::cout << "\t" << "|    |-" << std::setw( 9 ) << "" << "|    |-" << std::endl;
	std::cout << "\t" << "| " << a_discardCard << " | |" << std::setw( 8 ) << "" << "| " << a_handCard << " | |" << std::endl;
	std::cout << "\t" << "|    | |" << std::setw( 8 ) << "" << "|    | |" << std::endl;
	std::cout << "\t" << " ----  |" << std::setw( 8 ) << "" << " ----  |" << std::endl;
	std::cout << "\t" << "  -----" << std::setw( 10 ) << "" << " -----" << std::endl;
}