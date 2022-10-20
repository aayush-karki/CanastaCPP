/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Round.h"
#include "FileAccess.h"

// TODO (REFACTOR): Try to use Try catch blocks in the code
// TODO (REFACTOR): Use smart pointers instead of regular pointers

class CanastaGame
{
public:
	// default contructor
	CanastaGame();

	// default destructor
	~CanastaGame();

	// copy constructor 
	CanastaGame( const CanastaGame& a_other );

	// assignment operator
	CanastaGame& operator=( const CanastaGame& a_other );

	// contains the main loop for the game
	void RunGame();

private:

	// holds the actual game logics and component
	Round* m_round;

	// holds boolean value to quit the game
	bool m_exit;

	// holds boolean value show main menu or not
	bool m_showMainMenu;

	// holds the file acess object that allows to open from file
	FileAccess m_fileObj;

	//std::string m_saveFileName;

	// clears the round
	void ClearScreen();

	// prtins the title of the game
	void PrintGameTitle();

	// asks for player's input given the main menu prompt
	std::pair<bool, unsigned> MainMenuController();

	// executes the selected main menu
	bool MainMenuLogic( unsigned a_userChoice );

	// saves the game to file
	bool SaveToFile();

	// loads the game from file
	bool LoadFormFile();
};
