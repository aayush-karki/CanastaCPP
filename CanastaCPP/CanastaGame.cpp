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
	m_exit( false ), m_showMainMenu( true ),
	m_saveFile( "" )
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
	created CanastaGame object
Parameters:
			a_other, a constant object of CanastaGame class passed by
				reference. It holds the CanastaGame object to be
				copied.
Return Value: none
Algorithm:
			1) assigns each of the member of the passed CanastaGame
				object to the correspnding member variable of this
				object
Assistance Received: none
********************************************************************* */
CanastaGame::CanastaGame( const CanastaGame& a_other ) :
	m_exit( a_other.m_exit ),
	m_showMainMenu( a_other.m_showMainMenu ),
	m_saveFile( a_other.m_saveFile )
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
				to assign this CanastaGame object.
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

	// copying the data
	this->m_exit = a_other.m_exit;
	this->m_showMainMenu = a_other.m_showMainMenu;
	this->m_saveFile = a_other.m_saveFile;

	this->m_round = new Round( *( a_other.m_round ) );


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
	while( !m_exit )
	{
		// checking to see if we need to show main menu or not
		if( m_showMainMenu )
		{
			// executing the logic for main menu and checking 
			// if quit was pressed
			if( !MainMenu() )
			{
				// ignore every thing and repeat the loop
				// as exit was pressed. So it ends the program
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

	ClearScreen();
	std::cout << "Thank you for Playing Canasta!!" << std::endl;
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
void CanastaGame::PrintGameTitle()
{
	m_round->PrintGameTitle();
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
	m_round->ClearScreen();
}

/* *********************************************************************
Function Name: PrintRound
Purpose: To print out the game with round information
Parameters: none
Return Value: none
Algorithm:
			1) Call PrintGameTitle()
			2) Call m_round's PrintHand function
Assistance Received: none
********************************************************************* */
void CanastaGame::PrintGame()
{
	// printing the round
	m_round->PrintRound();
}

/* *********************************************************************
Function Name: MainMenu
Purpose: Contains the logic for main menu
Parameters: none
Return Value:
			boolean value. If the return is false than quit was
				selected; else other option was selected
Algorithm:
		1)until a valid intput
			2) print the game, the option, and the prompt
			3) get the input from user and validate it
		4) if user entered '1' then ask for the file name to save
			the game into and then delete m_round and create a new round
		5) if user entered '2' then ask for the file name to load
			the game from. Read the data saved in the file and
			then load the data into m_round
		6) else exit the program
Assistance Received: cplusplus forum
********************************************************************* */
bool CanastaGame::MainMenu()
{
	int userInputInt;
	bool validInput = true;
	do
	{
		// main menu have 3 options:
		// 1) start a new game,
		// 2) load a game
		// 3) quit
		PrintGameTitle();
		std::cout << "Main Menu:" << std::endl;
		std::cout << "\t1) Start a new game" << std::endl;
		std::cout << "\t2) Load a game" << std::endl;
		std::cout << "\t3) Quit program" << std::endl;
		std::cout << std::endl;

		if( !validInput )
		{
			std::cout << "Invalid Input!!" << std::endl;
		}
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
				validInput = true;
				continue;
			}
		}

		validInput = false;

	} while( !validInput );

	// doing what user chosse
	if( userInputInt == 1 )
	{
		// 1) start a new game,
		// TODO ask the player to enter a save file name

		// creating a new round
		delete m_round;
		m_round = new Round();
		m_round->StartNewRound();
	}
	else if( userInputInt == 2 )
	{
		// 2) load a game
		// TODO load a game main menu option
		//		ask the player to enter a load file name
		//		maybe create a getFileNameFromUser funciton
		//		

		// TODO deleme me and replace me by 
		//		creating a round by using the data from the file
		delete m_round;
		m_round = new Round();

	}
	else
	{
		// 3) quit
		m_exit = true;
	}

	// main menu should no longer be shown
	m_showMainMenu = false;

	// if quit was pressed then returns false
	return userInputInt != 3;
}
