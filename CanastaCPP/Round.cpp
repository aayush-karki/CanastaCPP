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
		2) set the m_playerWentOut to false
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
	m_playerWentOut( false ),
	m_roundStart( false ),
	m_playerTurn( a_playerTurn ),
	m_deck( a_stockCards ),
	m_lastCardR3Drwan( false ),
	m_endCausedCusDiscardPile( false )
{
	// initializing 2 players
	m_playerList.push_back( new Computer( a_compTotalScore,
										  a_compActualHand,
										  a_compMelds ) );
	m_playerList.push_back( new Human( a_humanTotalScore,
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

		m_discardPile.push_back( Card( extractdRankSuit ) );
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
	m_playerWentOut( a_other.m_playerWentOut ),
	m_roundStart( a_other.m_roundStart ),
	m_playerTurn( a_other.m_playerTurn ),
	m_deck( a_other.m_deck ),
	m_lastCardR3Drwan( a_other.m_lastCardR3Drwan ),
	m_endCausedCusDiscardPile( a_other.m_endCausedCusDiscardPile )
{
	// copying the player list
	m_playerList.push_back( new Computer( *( ( Computer* )a_other.m_playerList.at( 0 ) ) ) );
	m_playerList.push_back( new Human( *( ( Human* )a_other.m_playerList.at( 1 ) ) ) );
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
	this->m_playerWentOut = a_other.m_playerWentOut;
	this->m_roundStart = a_other.m_roundStart;
	this->m_lastCardR3Drwan = a_other.m_lastCardR3Drwan;
	this->m_endCausedCusDiscardPile = a_other.m_endCausedCusDiscardPile;
	this->m_playerTurn = a_other.m_playerTurn;
	this->m_deck = a_other.m_deck;

	// copying the player list
	m_playerList.push_back( new Computer( *( ( Computer* )a_other.m_playerList.at( 0 ) ) ) );
	m_playerList.push_back( new Human( *( ( Human* )a_other.m_playerList.at( 1 ) ) ) );

	return *this;
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
		<< std::setfill( ' ' ) << std::endl;

	// printing current player 
	std::cout << "Current Player: " <<
		( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" )
		<< std::endl << std::endl;
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

	// resetting player's hand
	for( unsigned currPlayerIdx = 0; currPlayerIdx < m_playerList.size(); ++currPlayerIdx )
	{
		m_playerList.at( currPlayerIdx )->ResetPlayerForNewRound();
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

	//m_playerTurn = ENUM_PlayerTurn::TURN_uninitialized;

	/* 
		TODO (Feature): take the below out into its own function for a consistent MVC approch.
			where it will be executed if the the m_playerTurn is set to uninialized 
	*/

	// round setup is complete 
	// seeing who goes first
	if( m_playerList.front()->GetTotalPoint() > m_playerList.back()->GetTotalPoint() )
	{
		// computer has more points so it goes first
		m_playerTurn = ENUM_PlayerTurn::TURN_computer;
		Message::AddMessage( "Computer has more points! So computer starts first" );
	}
	else if( m_playerList.back()->GetTotalPoint() > m_playerList.front()->GetTotalPoint() )
	{
		// human has more points so it goes first
		m_playerTurn = ENUM_PlayerTurn::TURN_human;
		Message::AddMessage( "Human has more points! So human starts first" );
	}
	else
	{
		// its a tie. Toss a coin
		std::string userInput;
		bool invalidInput = true;
		do
		{
			// clearing the window
			ClearScreen();

			// printing the game tile
			PrintGameTitle();

			// printing the round
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

	// new round created to round start should be false;
	m_roundStart = false;

	return true;
}

/* *********************************************************************
Function Name: ContinueRound
Purpose: Continues the round
Parameters: none
Return Value:
			pair of boolean value, boolean value. if first of the pair is
				true exit to main menu was pressed else it was not.
				if second of the pair is true save the game was pressed
				else it was not
Algorithm:
			1) Call TurnStartLogic function
Assistance Received: none
********************************************************************* */
std::pair<bool, bool> Round::ContinueRound()
{
	PrintRound();

	// printing any messages
	Message::PrintMessages();

	// clearing the messages
	Message::ClearMessages();

	if( m_playerTurn == ENUM_PlayerTurn::TURN_computer && !m_roundStart )
	{
		std::cout << "It is computer turn entry anything to procced a step: ";
		std::string garbage;
		std::getline( std::cin, garbage );
	}

	// check if the round is over 
	// 
	// round can end in three way
	// if one of the payers goes out -> indicated by m_playerWentOut
	// if last card drawn form the stock pile is read 3
	// if stock is empty and neight Player can use the top card of 
	//		discard pile in a meld
	if( ( m_playerWentOut || m_lastCardR3Drwan || m_endCausedCusDiscardPile
		  || ( m_deck.GetStock().empty() && GetCurrPlayerPtr()->GetTurnStartFlag() ) )
		&& !m_roundStart )
	{
		std::vector<std::string> playerNameList = { "Computer","Human" };

		// checking if the discard pile can be picked up if the stock the stock is empty
		if( !m_playerWentOut && !m_lastCardR3Drwan && m_deck.GetStock().empty() )
		{
			// checking for currClayer for current turn
			Computer tempComputer( *( ( Computer* )GetCurrPlayerPtr() ) );

			if( tempComputer.CanPickUpDiscardPile( m_discardPile ) )
			{
				// forcing the current player to pick up the discard pile
				TurnStartLogic( 2 );
				std::string message = " Stock is empty!\n";
				message += ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Computer" : "Human";
				message += " can pick up the discarded pile. So picking up the discard pile.";
				Message::AddMessage( message );
				return { false,false };
			}

			// checking for OtherPlayer for current turn
			Computer tempOtherPlayer( *( ( Computer* )GetOtherPlayerPtr() ) );

			if( tempOtherPlayer.CanPickUpDiscardPile( m_discardPile ) )
			{
				// setting curr player to other
				m_playerTurn = ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? ENUM_PlayerTurn::TURN_human : ENUM_PlayerTurn::TURN_computer;

				// forcing the new current player to pick up the discard pile
				TurnStartLogic( 2 );
				std::string message = " Stock is empty!\n";
				message += ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Computer" : "Human";
				message += " can pick up the discarded pile. So picking up the discard pile.";
				Message::AddMessage( message );

				return { false,false };
			}

			std::string message = "Stock is empty!\n";
			message += ( "Neither Human or Computer can pick up the discarded pile. So Ending the game." );
			Message::AddMessage( message );
			Message::AddMessage( "" );

		}

		// chekcing if the player wentout or not
		for( unsigned playerIdx = 0; playerIdx < m_playerList.size(); ++playerIdx )
		{
			if( m_playerList.at( playerIdx )->GetPlayerWentOutStatus() )
			{
				Message::AddMessage( playerNameList.at( playerIdx ) + " has gone out, and finished the round!" );
				Message::AddMessage( "" );
			}
		}
		// calculating the player's earned points for this round and total points
		std::vector<int> playersEarnedPoints = { 0,0 };
		for( unsigned playerIdx = 0; playerIdx < m_playerList.size(); ++playerIdx )
		{

			// calculating the round and total points
			playersEarnedPoints.at( playerIdx ) = m_playerList.at( playerIdx )->TallyHandPoint();
			m_playerList.at( playerIdx )->AddToTotalPoints( playersEarnedPoints.at( playerIdx ) );

			// printing the round points and total point that players earned in this round
			Message::AddMessage( playerNameList.at( playerIdx ) + "'s earned "
								 + std::to_string( playersEarnedPoints.at( playerIdx ) )
								 + " this round." );
			Message::AddMessage( playerNameList.at( playerIdx ) + "'s total earned points is "
								 + std::to_string( m_playerList.at( playerIdx )->GetTotalPoint() ) );
		}

		m_roundStart = true;

		// returning back that exit menu was not pressed and save was not pressed
		return { false, false };
	}

	// this block of code is executed only when the the round is over 
	// and prompting the player if they would like to continue or not
	// 
	if( m_roundStart )
	{
		// asking the player if they would like to play another round or not
		std::cout << "Would you like to play another round? (y/n) : ";

		// used to get the userInput
		std::string userInputStr;
		std::getline( std::cin, userInputStr );

		// validaing the userInput
		// a valid user input is 'y' or 'n'

		if( userInputStr.size() != 1 || ( std::tolower( userInputStr.at( 0 ) ) != 'y'
										  && std::tolower( userInputStr.at( 0 ) ) != 'n' ) )
		{
			// invalid input
			Message::AddMessage( "Invalid Input!!" );

			return { false, false };
		}

		// input was valid

		if( std::tolower( userInputStr.at( 0 ) ) == 'n' )
		{
			// no was pressed
			// quiting and printing winner
			Message::AddMessage( "Player chose not to continue playing!" );
			Message::AddMessage( "Computer's total earned points is "
								 + std::to_string( m_playerList.front()->GetTotalPoint() ) );
			Message::AddMessage( "Human's total earned points is "
								 + std::to_string( m_playerList.back()->GetTotalPoint() ) );

			Message::AddMessage( "" );
			if( m_playerList.front()->GetTotalPoint() > m_playerList.back()->GetTotalPoint() )
			{
				Message::AddMessage( "It was a tie!" );
			}
			else
			{
				std::string winner = "Winner of the game is ";
				winner += ( ( m_playerList.front()->GetTotalPoint() > m_playerList.back()->GetTotalPoint() ) ? "Comuputer" : "Human" );

				Message::AddMessage( winner );
			}
			return { true, false };
		}

		// yes was pressed

		// starting new round
		StartNewRound();
		++m_currRoundNum;


		Message::AddMessage( "New Round Started" );

		// resetting the flags
		m_playerWentOut = false;
		m_roundStart = false;
		m_lastCardR3Drwan = false;
		m_endCausedCusDiscardPile = false;
		return { false, false };

	}

	// starting the turn
	std::pair<unsigned, std::vector<unsigned>> currPlayerChoice;
	Player* currPlayerptr = m_playerList.at( ( unsigned )m_playerTurn );
	currPlayerChoice = currPlayerptr->PlayerTurnController( currPlayerptr->GetMelds(), m_discardPile );

	// logic for what to execute depending on which menu currently is 
	// displayed and what the choice was made

	switch( currPlayerChoice.first )
	{
		// playerChice.first == 1, beforeTurnStartcontrol was executed
		case 1:
		{
			// logic for sub menus of before turn start control
			return BeforeTurnLogic( currPlayerChoice.second.front() );
		}
		case 2:
		{
			// logic for sub menus of before turn start control
			TurnStartLogic( currPlayerChoice.second.front() );
			break;
		}
		case 3:
		{
			// logic for sub menus of before turn start control
			TurnContinueLogic( currPlayerChoice.second );
			break;
		}
		// error code
		case 10:
		{
			// do nothing as the game will loop over
			break;
		}

		default:
		{
			break;
		}

	}

	// main menu was not pressed so first is false
	// save was not pressed so second is false
	return { false, false };
}


/* *********************************************************************
Function Name: EmptyDiscardPile
Purpose: empties the discard pile
Parameters: none
Return Value: returns true to indicate that the vector was empited
Algorithm:
			1) for all the card in the discard pile pop it out
Assistance Received: none
********************************************************************* */
bool Round::EmptyDiscardPile()
{
	// poping out the whole stack
	m_discardPile.clear();

	return m_discardPile.empty();
}

/* *********************************************************************
Function Name: BeforeTurnLogic
Purpose: Contains the logic for Before Turn menu
Parameters:
		a_userChoice, unsinged interger. Holds the user choice for
			the menu
Return Value:
			pair of boolean value, boolean value. if first of the pair is
				true exit to main menu was pressed else it was not.
				if second of the pair is true save the game was pressed
				else it was not
Algorithm:
		1) if the userChoice is 1 return {false,true}
		2) if the userChoice is 2 then set the beforTurnMenuFlage to false
			and return {false,false}
		3) if the userChoice is 3 return {true,false}
Assistance Received: none
********************************************************************* */
std::pair<bool, bool> Round::BeforeTurnLogic( unsigned a_userChoice )
{
	// at the strat of the turn, player have 5 choices:
	// 1) Save the game -> enter 1
	// 2) Take a turn -> enter 2
	// 3) Quit the game and go to main menu -> enter 3

	// sub menus of before turn start menu
	switch( a_userChoice )
	{
		// save the game
		case 1:
		{
			return { false, true };
		}
		// take a turn was pressed
		case 2:
		{
			m_playerList.at( ( unsigned )m_playerTurn )->SetPlayerBeforeTurnMenuFlag( false );
			break;
		}
		// quit the game and go to main menu was pressed
		case 3:
		{
			return { true, false };
		}
		default:
		{
			// this should never run
			break;
		}
	}
	return { false, false };
}

/* *********************************************************************
Function Name: TurnStartLogic
Purpose: Contains the logic for Turn start menu
Parameters:
		a_userChoice, unsinged interger. Holds the user choice for
			the menu
Return Value:
			boolean value. it indicates whether a change was made to the
				the player or not
Algorithm:
		1) if the userChoice is 1  return false
		2) if the userChoice is 2 then deal a card untill the user gets
			non red three card
			and return {false,false}
		3) if the userChoice is 3 then check if the playercan pick up
			make a meld using the top of the discard pile and set
			turnStart flag to false and return true
		4)		if no then return false
		5)		if yes then add all the card in discard pile to the
				player hand, clear the discard pile and set turnStart
				flag to false and return true
		6) if the userChoice is 4 the print the discard pule and return
			false
		7) if the userChoice is 5 the print the stock and return false
Assistance Received: none
********************************************************************* */
bool Round::TurnStartLogic( unsigned a_userChoice )
{
	// at the strat of the turn, player have 5 choices:
	//	1) ask for help -> enter 1
	//	2) draw a card from deck -> enter 2
	//	3) pick up the discard pile -> enter 3
	//	4) show discard pile -> enter 4
	//	5) show stock card (for debugging) -> enter 5

	Player* currPlayerptr = m_playerList.at( ( unsigned )m_playerTurn );
	// sub menus of turn start menu
	switch( a_userChoice )
	{
		// ask for help
		case 1:
		{
			Message::AddMessage( "Asking computer for help!" );
			Computer tempComp( *( ( Computer* )currPlayerptr ) );

			auto message = tempComp.TurnStartHelp( m_discardPile );

			Message::AddMessage( message.second );

			return false;
		}
		// draw a card from deck
		case 2:
		{
			// deal a card untill player gets a non red three card
			bool dealtCardResult = false;
			while( !dealtCardResult )
			{
				Card dealtCard = m_deck.DealCard();
				dealtCardResult = currPlayerptr->AddCardToHand( dealtCard );

				// concoting message to display
				std::string dealtMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
				dealtMessage += " drew ";
				dealtMessage += dealtCard.GetRankSuit();
				Message::AddMessage( dealtMessage );

				// checkin if the stock is empty and last dealt card was red three
				if( m_deck.GetStock().empty() && !dealtCardResult )
				{
					m_lastCardR3Drwan = true;
				}
			}

			// setting the turn start flag to false
			currPlayerptr->SetTurnStartFlag( false );
			break;
		}
		// pick up the discard pile
		case 3:
		{
			// player can not pick up the discard pile if the 
			// the top card can not be used to be melded

			// see if we can meld the top of the discard pile into any
			// of the alredy existing melds
			if( currPlayerptr->CanAddToMeld( m_discardPile.front() ).first == -1 )
			{

				if( !currPlayerptr->CanPickUpDiscardPile( m_discardPile ) )
				{
					std::string pickedupMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
					// we can not meld the stack so our only option is to draw
					Message::AddMessage( pickedupMessage + " can not pick up discard pile" );
					return false;
				}
			}

			std::string discardCard = Card::ConvertVecToString10PerLine( m_discardPile );

			// adding all the card of the discard pile to the player
			for( unsigned discardIdx = 0; discardIdx < m_discardPile.size(); ++discardIdx )
			{
				currPlayerptr->AddCardToHand( m_discardPile.at( discardIdx ) );
			}

			// clearing the discard pile
			EmptyDiscardPile();

			std::string pickedupMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
			// concoting message to display
			pickedupMessage += " picked up following cards from the discard pile\n";
			pickedupMessage += discardCard;
			Message::AddMessage( pickedupMessage );

			// setting the turn start flag to false
			currPlayerptr->SetTurnStartFlag( false );
			break;
		}
		// show discard pile
		case 4:
		{
			Message::AddMessage( "Discard Pile:" );
			Message::AddMessage( Card::ConvertVecToString10PerLine( m_discardPile ) );
			return false;
		}
		// show stock card (for debugging)
		case 5:
		{
			Message::AddMessage( "Stock:" );
			Message::AddMessage( Card::ConvertVecToString10PerLine( m_deck.GetStock() ) );
			return false;
		}
		default:
		{
			// this should never run
			break;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: TurnStartLogic
Purpose: Contains the logic for Turn start menu
Parameters:
		a_userChoice, unsinged interger. Holds the user choice for
			the menu
Return Value:
			boolean value. it indicates whether a change was made to the
				the player or not
Algorithm:
		1) if the userChoice is 1 return {false,true}
		2) if the userChoice is 2 then set the beforTurnMenuFlage to false
			and return {false,false}
		3) if the userChoice is 3 return {true,false}
Assistance Received: none
********************************************************************* */
bool Round::TurnContinueLogic( std::vector<unsigned> a_userChoiceVec )
{
	// else it is not the start of the round so they have 5 choices
	//	1) Ask for help -> enter 1
	//	2) Add a card in hand to meld -> enter 2 <actualHandCardIdx> <meldIdx>
	//	3) Discard a card from hand -> enter 3 <actualHandCardIdx>
	//	4) Go out -> enter 4
	//	5) Make a new meld -> enter 5 <actualHandCardIdx> <actualHandCardIdx> <actualHandCardIdx> ...
	//	6) Show discard pile -> enter 6
	//	7) Show stock card (for debugging) -> enter 7
	//	8) Take out wild card From meld -> enter 8 <meldCardIdx> <meldIdx>

	Player* currPlayerptr = m_playerList.at( ( unsigned )m_playerTurn );
	// sub menus of turn continue menu
	switch( a_userChoiceVec.front() )
	{
		// Ask for help
		case 1:
		{
			Message::AddMessage( "Asking computer for help!" );
			Computer tempComp( *( ( Computer* )currPlayerptr ) );

			auto message = tempComp.TurnContinueHelp( GetOtherPlayerPtr()->GetMelds(), m_discardPile );

			Message::AddMessage( message.second );

			return false;
		}
		// Add a card in hand to meld
		case 2:
		{
			// trying to adding the card to a meld
			Card cardToMeld = currPlayerptr->GetActualHand().at( a_userChoiceVec.at( 1 ) );
			std::pair<bool, std::string> result = currPlayerptr->AddToMeld( a_userChoiceVec.at( 1 ), a_userChoiceVec.at( 2 ) );

			// if the first is false then error
			if( !result.first )
			{

				return false;
			}

			// concoting message to display
			std::string displayMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
			displayMessage += " added " + cardToMeld.GetRankSuit() + " to a meld";
			Message::AddMessage( displayMessage );
			return true;
		}
		// Discard a card from hand
		case 3:
		{
			// discarding and adding the discarded card to discard pile
			AddToDiscardPile( currPlayerptr->Discard( a_userChoiceVec.at( 1 ) ) );

			// concoting message to display
			std::string displayMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
			displayMessage += " Disacrded " + GetDiscardPileTopRankSuit();
			Message::AddMessage( displayMessage );

			// checking if the curr playercan go out
			if( currPlayerptr->CanGoOut() )
			{
				currPlayerptr->SetPlayerWentOutStatus( true );
				m_playerWentOut = true;

				// concoting message to display
				displayMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );

				displayMessage += " Goes out";
				Message::AddMessage( displayMessage );
			}


			// curr player discarded so its next players turn
			m_playerTurn = ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ? ENUM_PlayerTurn::TURN_human : ENUM_PlayerTurn::TURN_computer );


			// clearing the menu flag
			currPlayerptr->SetPlayerBeforeTurnMenuFlag( true );
			currPlayerptr->SetTurnStartFlag( true );

			return true;

		}
		// Go out
		case 4:
		{
			// checking if the curr player can go out
			// concoting message to display
			std::string displayMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );

			if( !currPlayerptr->CanGoOut() )
			{
				displayMessage += " Can not Go out";
				Message::AddMessage( displayMessage );
				return false;
			}

			currPlayerptr->SetPlayerWentOutStatus( true );
			m_playerWentOut = true;

			displayMessage += " Goes out";
			Message::AddMessage( displayMessage );

			return true;
		}
		// Make a new meld
		case 5:
		{

			// removing the menu idx form the user input
			std::vector<unsigned> cardIdx = a_userChoiceVec;
			cardIdx.erase( cardIdx.begin() );

			// trying to create a new meld
			std::pair<bool, std::string> result = currPlayerptr->MakeNewMeld( cardIdx );

			// if the first is false then error
			if( !result.first )
			{
				Message::AddMessage( result.second );
				return false;
			}
			Card cardToMeld = currPlayerptr->GetMelds().back().front();

			// concoting message to display
			std::string displayMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
			displayMessage += " made a new meld of " + cardToMeld.GetRankSuit();
			Message::AddMessage( displayMessage );
			return true;
		}
		// show discard pile
		case 6:
		{
			Message::AddMessage( "Discard Pile:" );
			Message::AddMessage( Card::ConvertVecToString10PerLine( m_discardPile ) );
			return false;
		}
		// show stock card (for debugging)
		case 7:
		{
			Message::AddMessage( "Stock:" );
			Message::AddMessage( Card::ConvertVecToString10PerLine( m_deck.GetStock() ) );
			return false;
		}
		// Take out wild card From meld
		case 8:
		{
			// trying to take out a wild card
			Card wildCard = currPlayerptr->GetActualHand().at( a_userChoiceVec.at( 1 ) );
			std::pair<bool, std::string> result = currPlayerptr->TakeOutWildCard( a_userChoiceVec.at( 1 ), a_userChoiceVec.at( 2 ) );

			// if the first is false then error
			if( !result.first )
			{
				Message::AddMessage( result.second );

				return false;
			}

			// concoting message to display
			std::string displayMessage = ( ( m_playerTurn == ENUM_PlayerTurn::TURN_computer ) ? "Comuputer" : "Human" );
			displayMessage += " took out " + wildCard.GetRankSuit() + " from the meld";
			Message::AddMessage( displayMessage );

			// checking if the meld was desolved or not 
			if( !result.second.empty() )
			{
				Message::AddMessage( result.second );
			}

			return true;
		}
		default:
		{
			// this should never run
			break;
		}
	}

	return false;
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
		Print1DiscardAnd1Stock( GetDiscardPileTopCard().GetRankSuit(), "NA" );
	}
	//when discard pile has 1 card and stock has 1 card
	else if( m_discardPile.size() == 1 && m_deck.GetStock().size() == 1 )
	{
		Print1DiscardAnd1Stock( GetDiscardPileTopCard().GetRankSuit(), "**" );
	}
	// when discard pile has 1 card and stock more than 1 card
	else if( m_discardPile.size() == 1 && m_deck.GetStock().size() > 1 )
	{
		Print1DiscardAnd2Stock( GetDiscardPileTopCard().GetRankSuit(), "**" );

	}
	// when discard pile has mroe than 1 card and stock is empty
	else if( m_discardPile.size() > 1 && m_deck.IsStockEmpty() == true )
	{
		Print2DiscardAnd1Stock( GetDiscardPileTopCard().GetRankSuit(), "NA" );
	}
	//when discard pile has more than 1 card and stock has 1 card
	else if( m_discardPile.size() > 1 && m_deck.GetStock().size() == 1 )
	{
		Print2DiscardAnd1Stock( GetDiscardPileTopCard().GetRankSuit(), "**" );
	}
	// when discard pile has more than 1 card and stock more than 1 card
	else if( m_discardPile.size() > 1 && m_deck.GetStock().size() > 1 )
	{
		Print2DiscardAnd2Stock( GetDiscardPileTopCard().GetRankSuit(), "**" );
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