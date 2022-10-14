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
	 m_round(nullptr)
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
	std::pair<bool,unsigned> playerMainMenuChoice;

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
			if( !playerMainMenuChoice.first  )
			{
				continue;
			}
		}

		// at this point game is seted up whether by loading a saved 
		// file or by creating a new game. So continue playing the 
		// game

		// continue to play the game 
		m_showMainMenu = !m_round->ContinueRound();

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
			m_showMainMenu = false;
			return { true, userInputInt };
		}
	}
	else
	{
		Message::AddMessage( "Invalid Input!!" );
		return { false, 5 };
	}
}

/* *********************************************************************
Function Name: MainMenuLogic
Purpose: Contains the logic for main menu
Parameters:
		a_userChoice, unsinged interger. Holds the user choice for 
			the menu
Return Value:
			boolean value. false if the user quit the game or user input an invalid 
				filename; else ture.
Algorithm:
		Todo fix me
		1) if the userChoice is 3 set m_exit to true and return flase
		2) get the input from user and validate it
		3) if the user input is valid then set the state of
			showMainMenu choice to false and return true and user input
			else return false and 5
		4) if user entered '1' then ask for the file name to save
			the game into and then delete m_round and create a new round
		5) if user entered '2' then ask for the file name to load
			the game from. Read the data saved in the file and
			then load the data into m_round
		6) else exit the program

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

		// save the current round to the file
		SaveToFile();
		return true;
	}
	// 2) load a game
	else
	{
		// opening of the a file
		if( !m_fileObj.CreateFile( userFileName ) )
		{
			// opening of the file failed
			m_showMainMenu = true;
			return false;
		}

		// TODO call the load function
		LoadFormFile();
		// TODO deleme me and replace me by creating a round by using the data from the file
		delete m_round;
		m_round = new Round();
		return true;
	}

	// if quit was pressed then returns false
	return false;
	
}

/* *********************************************************************
Function Name: SaveToFile
Purpose: Saves the file to the file
Parameters: none
Return Value:
			boolean value. false if the save was unsuccessfull; else true
Algorithm:
		1) print the option, and the prompt
		2) get the input from user and validate it
		3) if the user input is valid then set the state of
			showMainMenu choice to false and return true and user input
			else return false and 5
Assistance Received: none
********************************************************************* */
bool CanastaGame::SaveToFile()
{
	// remove all the content from the file
	m_fileObj.RemoveAllContent();

	// saving the current round
	if( !m_fileObj.WriteOneLineToFile( "Round: " + std::to_string( m_round->GetCurrRoundNum()) + "\n") )
	{
		return false;
	}
	
	// saving the computer information
	//if( !m_fileObj.WriteOneLineToFile( "Computer:\n\tScore: " + std::to_string( m_round->Get() ) + "\n" ) )
	{
		return false;
	}


	return true;;
}

bool CanastaGame::LoadFormFile()
{
	return false;
}
