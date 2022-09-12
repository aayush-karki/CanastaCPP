/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <vector>
#include <stack>
#include "Player.h"
#include "Deck.h"
#include "Card.h"

class Round
{
public:

private:
	unsigned m_currRoundNum;

	bool m_roundOver;

	// m_playerTurn holds 0 or 1;
	// if = 0, then it is player 1 turn. Player1 is human.
	unsigned m_playerTurn;

	// m_playerListholds the list of player playing the game, 
	// contains 2 player object both of them are object of  
	// classes that are derived form player class.
	std::vector<Player*> m_playerList;

	// m_deck holds deck object used for the game, contains 
	// 2 decks in it with each containing 52 standard card 
	// plus 2 jokers for a total of 108 cards. 
	Deck m_deck;

	// m_discardPile holds cards that are discarded by players,
	// additional player can pick up the whole discarded pile if
	// the last added to the pile help them in making a meld.
	std::stack<Card> m_discardPile;

};

