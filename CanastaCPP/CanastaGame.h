/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Round.h"

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

	std::string m_saveFile;

	// clears the round
	void ClearScreen();

	// prtins the title of the game
	void PrintGameTitle();

	// prints the game
	void PrintGame();

	// holds logic for main menu
	bool MainMenu();

};

// TODO more the turn start logic in to round class as it is the logic for the 
//		the round. and every thing we need is in the round
// TODO move the print Game Title in to the round class and move the clear screen
//		into the round class
// TODO when inside the round class player should not be able to quit the game.
//		instead they should be able to come back to main menu
// 
//
