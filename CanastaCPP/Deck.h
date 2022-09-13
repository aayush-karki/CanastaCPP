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

	// constructor when passing string containing the cards of m_stock
	Deck(std::string a_stock);

	// default destructor
	~Deck();

	// copy constructor
	Deck( const Deck& a_other );

	// assignment constructor
	Deck& operator = ( const Deck& a_other );

	// getter functions
	const std::vector<Card*> GetStock() const { return m_stock; }
	const std::vector<Card*> GetDealt() const { return m_dealt;}

	// returns true if m_stock is empty
	bool IsStockEmpty() { return m_stock.empty(); }

	// moves a card from m_stock to m_deal and returns a copy of that card
	const Card DealCard();

	// prints the deck
	void PrintDeck();

private:
	// shuffels the cards in m_stock
	void Shuffel();

	// moves cards in dealt pile to stock pile
	void ConsodilateDeck();

private:
	
	// m_rankList lists all the rank of card in a standard deck
	// of card and J for Joker
	const std::string m_rankList = "23456789xjqkaJ";

	// m_suitList lists all the suit of card in a standard deck
	// of card and 1 and 2 for Joker
	// s = spade, c = club, h = heart, and d = diamond
	const std::string m_suitList = "schd12";

	// stack of undelt cards
	std::vector<Card*> m_stock;

	// stack of delt cards, dealt cards are moved to here for later use
	std::vector<Card*> m_dealt;
};