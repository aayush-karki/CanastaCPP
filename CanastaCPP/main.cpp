/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include <iostream>
#include "CanastaGame.h"

/* *********************************************************************
Function Name: main
Purpose: Entry point to the game application
Parameters: none
Return Value: 0 to indicate run with no errors
Algorithm:
		1) Declare a object of CanastaGame class
		2) Call its StartGame Function
Assistance Received: none
********************************************************************* */
int main()
{
	CanastaGame gameApp();

	std::vector<Card*> myCards;

	myCards.push_back( new Card( 'J', '1' ) );
	myCards.push_back( new Card( 'J', '2' ) );
	myCards.push_back( new Card( 'k', 'd' ) );
	myCards.push_back( new Card( '2', 'c' ) );
	myCards.push_back( new Card( '3', 'd' ) );
	myCards.push_back( new Card( '3', 's' ) );

	for( auto currPtr = myCards.begin(); currPtr != myCards.end(); ++currPtr )
	{
		( *currPtr )->Debug();
	}

	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " == " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) == *( myCards[ 0 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " == " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) == *( myCards[ 1 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " != " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) != *( myCards[ 0 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " != " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) != *( myCards[ 1 ] ) ) << std::endl << std::endl;

	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " <  " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) < *( myCards[ 1 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " <  " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) < *( myCards[ 0 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " <= " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) <= *( myCards[ 1 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " <= " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) <= *( myCards[ 0 ] ) ) << std::endl << std::endl;

	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " > " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) > *( myCards[ 1 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " > " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) > *( myCards[ 0 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " >= " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) >= *( myCards[ 0 ] ) ) << std::endl;
	std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " >= " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) >= *( myCards[ 1 ] ) ) << std::endl << std::endl;

	//std::cout << "copying last element of the vector" << std:: endl;
	//Card* copyCard = new Card( *( *( --( myCards.end() ) ) ) );
	//copyCard->Debug();

	//std::cout << "assginming last element of the vector" << std::endl;
	//Card assignCard;
	//assignCard = *copyCard;

	//assignCard.Debug();

	//Deck myDeck;
	//myDeck.PrintDeck();
	//myDeck.Shuffel();
	//myDeck.PrintDeck();

	//myDeck.DealCard();

	//myDeck.PrintDeck();

	return 0;
}


/* *********************************************************************
Function Name: main
Purpose: Entry point to the game application
Parameters:
			grades[], an array passed by value. It holds individual grades
			size, an integer. It refers to the number of students in the class
Return Value: The average grade in the class, a real value
Algorithm:
			1) Add all the grades
	   2) Divide the sum by the number of students in class to calculate the average
Assistance Received: none
********************************************************************* */