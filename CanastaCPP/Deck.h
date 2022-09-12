/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include "Card.h"

class Deck
{
public:
	// default constructor
	Deck();

	// default destructor
	~Deck();

	// copy constructor
	Deck( const Deck& a_other );

	// assignment constructor
	Deck& operator = ( const Deck& a_other );

	// getter functions
	const std::vector<Card*> GetStock() const { return m_stock; }
	const std::vector<Card*> GetDealt() const { return m_dealt;}

private:
	
	// m_rankList lists all the rank of card in a standard deck
	// of card and J for Joker
	const std::string m_rankList = "a23456789xjqkJ";

	// m_suitList lists all the suit of card in a standard deck
	// of card and 1 and 2 for Joker
	// s = spade, c = club, h = heart, and d = diamond
	const std::string m_suitList = "schd12";

	// stack of undelt cards
	std::vector<Card*> m_stock;

	// stack of delt cards, dealt cards are moved to here for later use
	std::vector<Card*> m_dealt;
};