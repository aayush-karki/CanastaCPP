/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "CanastaGame.h"

/* *********************************************************************
Function Name: CanastaGame
Purpose: To construct a Round CanastaGame and to populate its
	member variables.
Parameters: none
Return Value: none
Algorithm:
		1) Inialze the member function
		2) dynamically create a round object
Assistance Received: none
********************************************************************* */
CanastaGame::CanastaGame() :
	m_exit( false ), m_showMainMenu( true ), m_fileObj(),
	m_round( nullptr )
{
	m_round = new Round();
}

/* *********************************************************************
Function Name: Round
Purpose: To destruct a CanastaGame object and its dynamically created
	member variables
Parameters: none
Return Value: none
Algorithm:
			1) delete m_round
Assistance Received: none
********************************************************************* */
CanastaGame::~CanastaGame()
{
	delete m_round;
}

/* *********************************************************************
Function Name: CanastaGame
Purpose: To create a new CanastaGame object and copy the passed
			CanastaGame object's member variables data into the newly
			created CanastaGame object. It does not copy the FileAceess
			member variable of the passed object, but calls its default
			constructor.
Parameters:
			a_other, a constant object of CanastaGame class passed by
				reference. It holds the CanastaGame object to be
				copied.
Return Value: none
Algorithm:
			1) assigns each of the member of the passed CanastaGame
				object to the correspnding member variable of this
				object
			2) create a fileObject
Assistance Received: none
********************************************************************* */
CanastaGame::CanastaGame( const CanastaGame& a_other ) :
	m_exit( false ), m_showMainMenu( true ), m_fileObj(),
	m_round( nullptr )
{
	this->m_round = new Round( *( a_other.m_round ) );
}

/* *********************************************************************
Function Name: operator=, assignment operator
Purpose: To copy the passed CanastaGame object's member variables
		data into this CanastaGame object
Parameters:
			a_other, a constant object of CanastaGame class passed by
				reference. It holds a CanastaGame object that is used
				to assign this CanastaGame object. It does not copy the
				FileAceess member variable of the passed object.
Return Value: its own memory address
Algorithm:
			1) check for self assignment if yes return itself
			2) assigns each of the member of the passed CanastaGame
				object to the correspnding member variable of this object
			3) return its own memory address
Assistance Received: none
********************************************************************* */
CanastaGame& CanastaGame::operator=( const CanastaGame& a_other )
{
	// checking for self assigmnet 
	if( this == &a_other )
	{
		return *this;
	}

	this->m_exit = false;
	this->m_showMainMenu = true;

	delete this->m_round;

	// copying the data
	this->m_round = new Round( *( a_other.m_round ) );

	// close the file if it is open 
	m_fileObj.CloseFile();


	return *this;
}

/* *********************************************************************
Function Name: RunGame
Purpose: runs the game. It contains the main loop for the game
Parameters: none
Return Value: none
Algorithm: none
Assistance Received: cplusplus forum
********************************************************************* */
void CanastaGame::RunGame()
{
	// starting the game
	// this is going to run till player eixts
	std::pair<bool, unsigned> playerMainMenuChoice;

	while( !m_exit )
	{
		PrintGameTitle();

		// checking to see if we need to show main menu or not
		if( m_showMainMenu )
		{
			// print messages if any
			Message::PrintMessages();
			Message::ClearMessages();

			// executing the logic for main menu and checking 
			// if quit was pressed
			playerMainMenuChoice = MainMenuController();

			// do not execute the rest of the loop if the player input is 
			if( !playerMainMenuChoice.first )
			{
				continue;
			}

			// executing the menu logic
			// if it is false then either player pressed quit or
			// player input was invalid either way we turn on the 
			// main menu
			if( !MainMenuLogic( playerMainMenuChoice.second ) )
			{
				m_showMainMenu = true;
				continue;
			}
		}

		// at this point game is seted up whether by loading a saved 
		// file or by creating a new game. So continue playing the 
		// game

		// continue to play the game
		std::pair<bool, bool> contRoundReturnVal;
		contRoundReturnVal = m_round->ContinueRound();

		// checking if exits to main menu was pressed
		m_showMainMenu = contRoundReturnVal.first;

		// if save game was pressed
		if( contRoundReturnVal.second )
		{
			SaveToFile();
		}

		// now we know that player took the turn 
		// so player can either 
		// 1) pick up the discard pile if they can use the top 
		//		card in the discard pile to make a meld or add
		//		to exiting meld
		// 2) draw a card from the stock pile
	}

	PrintGameTitle();

	std::cout << "Thank you for Playing Canasta!!" << std::endl;
}

/* *********************************************************************
Function Name: PrintGameTitle
Purpose: To print out the game title. It is goning to be the top most
	thing in game frame
Parameters: none
Return Value: none
Algorithm:
			1) clear the screen and Prints out the Game title
Assistance Received: none
********************************************************************* */
void CanastaGame::PrintGameTitle()
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
Function Name: ClearScreen
Purpose: Clears the terminal screen
Parameters: none
Return Value: none
Algorithm: none
Assistance Received: cplusplus forum
********************************************************************* */
void CanastaGame::ClearScreen()
{
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "\x1B[2J\x1B[H";
}

/* *********************************************************************
Function Name: MainMenuController
Purpose: Contains the controller for main menu
Parameters: none
Return Value:
			pair of <boolean value, unsigned integer>. first value hold
				if the player input was valid or not. second value hold
				the player input if valid else it holds 5 a garbage value
Algorithm:
		1) print the option, and the prompt
		2) get the input from user and validate it
		3) if the user input is valid then set the state of
			showMainMenu choice to false and return true and user input
			else return false and 5
Assistance Received: none
********************************************************************* */
std::pair<bool, unsigned> CanastaGame::MainMenuController()
{
	int userInputInt;

	// main menu have 3 options:
	// 1) start a new game,
	// 2) load a game
	// 3) quit

	std::cout << "Main Menu:" << std::endl;
	std::cout << "\t1) Start a new game" << std::endl;
	std::cout << "\t2) Load a game" << std::endl;
	std::cout << "\t3) Quit program" << std::endl;
	std::cout << std::endl;

	std::cout << "Enter a corresponding number: ";

	// used to get the userInput
	std::string userInputStr;
	std::getline( std::cin, userInputStr );

	// validaing the userInput
	// a valid user input is 1, or 2, or 3

	if( userInputStr.size() == 1 && std::isdigit( userInputStr.at( 0 ) ) )
	{

		// chcecking if the user input is 1 or 2 or 3
		userInputInt = std::stoi( userInputStr );

		if( userInputInt >= 1 && userInputInt <= 3 )
		{
			return { true, userInputInt };
		}
	}

	Message::AddMessage( "Invalid Input!!" );
	return { false, 5 };

}

/* *********************************************************************
Function Name: MainMenuLogic
Purpose: Contains the logic for main menu
Parameters:
		a_userChoice, unsinged interger. Holds the user choice for
			the menu
Return Value:
			boolean value. false if the user quit the game or user input
				an invalid filename; else ture.
Algorithm:
		1) if the userChoice is 3 set m_exit to true and return false
		2) get the file name from the user.
		3) if user entered '1' then ask for the file name to save
			the game into and then delete m_round and create a new round
		4) if user entered '2' then ask for the file name to load
			the game from. Read the data saved in the file and
			then load the data into m_round
Assistance Received: none
********************************************************************* */
bool CanastaGame::MainMenuLogic( unsigned a_userChoice )
{
	// 3) quit
	if( a_userChoice == 3 )
	{
		m_exit = true;
		return false;
	}

	PrintGameTitle();

	std::cout << "Enter the file name: ";

	// used to get the userInput
	std::string userFileName;
	std::getline( std::cin, userFileName );

	// 1) start a new game,
	if( a_userChoice == 1 )
	{
		// creating a file
		if( !m_fileObj.CreateFile( userFileName ) )
		{
			// creating the file failed
			m_showMainMenu = true;
			return false;
		}

		// creating a new round
		delete m_round;
		m_round = new Round();
		m_round->StartNewRound();

		// opening of the a file
		if( !SaveToFile() )
		{
			// file failed to save failed
			m_showMainMenu = true;
			m_fileObj.CloseFile();
			Message::AddMessage( "Failed to save to file" );
			return false;
		}
	}
	// 2) load a game
	else
	{
		// opening of the a file
		if( !m_fileObj.OpenFile( userFileName ) || !LoadFormFile() )
		{
			// opening or loading of the file failed
			m_showMainMenu = true;
			Message::AddMessage( "Failed to load game from file" );
			return false;
		}

	}

	m_showMainMenu = false;
	return true;
}


/* *********************************************************************
Function Name: SaveToFile
Purpose: Saves the file to the file
Parameters: none
Return Value:
			boolean value. false if the save was unsuccessfull; else true
Algorithm:
		1) create a string
		2) add all the data to save to the string
		3) write the data to the file
Assistance Received: none
********************************************************************* */
bool CanastaGame::SaveToFile()
{
	std::string gameData = "";
	// saving the current round
	gameData += "Round: " + std::to_string( m_round->GetCurrRoundNum() ) + "\n\n";

	// saving the computer information
	const Player* playerPtr = m_round->GetComputerPlayerPtr();
	gameData += "Computer:\n";
	gameData += "\tScore: " + std::to_string( playerPtr->GetTotalPoint() ) + "\n";
	gameData += "\tHand: " + playerPtr->GetActualHandString() + "\n";
	gameData += "\tMelds: " + playerPtr->GetMeldsString() + "\n\n";

	// saving the human information
	playerPtr = m_round->GetHumanPlayerPtr();
	gameData += "Human:\n";
	gameData += "\tScore: " + std::to_string( playerPtr->GetTotalPoint() ) + "\n";
	gameData += "\tHand: " + playerPtr->GetActualHandString() + "\n";
	gameData += "\tMelds: " + playerPtr->GetMeldsString() + "\n\n";

	// saving the stock information
	gameData += "Stock: " + m_round->GetStockString() + "\n";
	gameData += "Discard: " + m_round->GetDiscardedPile() + "\n\n";

	gameData += "Next Player: ";

	switch( m_round->GetPlayerTurn() )
	{
		case ENUM_PlayerTurn::TURN_computer:
			gameData += "Computer";
			break;
		case ENUM_PlayerTurn::TURN_human:
			gameData += "Human";
			break;
		default:
			// this should never happen 
			gameData += "Uninitialized";
			break;
	}

	// remove all the content from the file
	m_fileObj.RemoveAllContent();

	if( !m_fileObj.WriteOneLineToFile( gameData ) )
	{
		return false;
	}

	Message::AddMessage( "Game successfully saved!" );
	return true;;
}

/* *********************************************************************
Function Name: LoadFormFile
Purpose: loads the game from the file
Parameters: none
Return Value:
			boolean value. false if the load was unsuccessfull; else true
Algorithm:
		1) create a string
		2) add all the data to save to the string
		3) write the data to the file
Assistance Received: none
********************************************************************* */
bool CanastaGame::LoadFormFile()
{
	std::vector<std::string> dataLineList;
	dataLineList.reserve( 18 );

	// the 10 data tha we want to get in order are:
	// 1) round number
	// 2) computer score
	// 3) computer hand
	// 4) computer meld
	// 5) human score
	// 6) human hand
	// 7) human meld
	// 8) stock
	// 9) discard pile
	// 10) next player

	//// getting the data
	//for( unsigned dataidx = 0; dataidx < datalinelist.size(); ++dataidx )
	//{
	//	// get the next line untill it get non empty line
	//	std::string nextline = "";
	//	while( nextline == "" )
	//	{
	//		if( !m_fileobj.getnextline( nextline ) )
	//		{
	//			message::addmessage( "corrupted file!" );
	//			return false;
	//		}

	//		// ignoring "computer:" and "human:" line
	//		if( nextline == "computer:" || nextline == "human:" )
	//		{
	//			nextline = "";
	//			continue;
	//		}
	//	}

	//	// adding the non empty line to the datalist
	//	datalinelist.at( dataidx ) = nextline;
	//}

	// get the next line untill it get non empty line
	std::string nextLine = "";
	while( !m_fileObj.CheckEOF() )
	{
		if( !m_fileObj.GetNextLine( nextLine ) )
		{
			Message::AddMessage( "Corrupted File!" );
			return false;
		}
		dataLineList.push_back( nextLine );
	}

	// removinging all lines with only space
	for( int idx = dataLineList.size() - 1; idx >= 0; --idx )
	{
		std::stringstream streamBuffer( dataLineList.at( idx ) );

		std::string extractedStr = "";

		streamBuffer >> extractedStr;
		if( extractedStr.empty() || extractedStr == "Computer:" || extractedStr=="Human:" )
		{
			dataLineList.erase( dataLineList.begin() + idx );
		}
	}


	// for all the lines remove the text before ':'
	for( unsigned dataIdx = 0; dataIdx < dataLineList.size(); ++dataIdx )
	{
		// finding the positoin of ':'
		std::size_t colonPos = dataLineList.at( dataIdx ).find_first_of( ':' );

		// if ':' not found it can only be corrupted file
		if( colonPos == std::string::npos )
		{
			Message::AddMessage( "Corrupted file!" );
			return false;
		}
		// copying everything after the : + 1 as imediatly after it is a space
		dataLineList.at( dataIdx ) = dataLineList.at( dataIdx ).substr( colonPos + 2 );
	}

	// extracting all numerical data into their respective data type
	// the first data is the round 
	unsigned roundNum = 0;
	std::stringstream stringBuffer( dataLineList.front() );
	stringBuffer >> roundNum;

	// computer score is the second data
	unsigned computerScore = 0;
	stringBuffer << dataLineList.at( 1 );
	stringBuffer >> computerScore;

	// human score is the fifth data
	unsigned humanScore = 0;
	stringBuffer << dataLineList.at( 4 );
	stringBuffer >> humanScore;

	// next player turn is the last data
	ENUM_PlayerTurn playerTurn;

	if( dataLineList.back() == "Human" )
	{
		playerTurn = ENUM_PlayerTurn::TURN_human;
	}
	else if( dataLineList.back() == "Computer" )
	{
		playerTurn = ENUM_PlayerTurn::TURN_computer;
	}
	else
	{
		// this should never run 
		playerTurn = ENUM_PlayerTurn::TURN_uninitialized;
	}

	// initializing the game
	delete m_round;
	m_round = new Round( roundNum,
						 playerTurn,
						 computerScore,
						 dataLineList.at( 2 ),
						 dataLineList.at( 3 ),
						 humanScore,
						 dataLineList.at( 5 ),
						 dataLineList.at( 6 ),
						 dataLineList.at( 7 ),
						 dataLineList.at( 8 ) );

	return true;
}