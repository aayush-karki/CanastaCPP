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

	myCards.push_back( new Card( '4', 's' ) );
	myCards.push_back( new Card( 'k', 'd' ) );
	myCards.push_back( new Card( '2', 'c' ) );
	myCards.push_back( new Card( 'J', '1' ) );
	myCards.push_back( new Card( '3', 'd' ) );
	myCards.push_back( new Card( '3', 's' ) );

	for( auto currPtr = myCards.begin(); currPtr != myCards.end(); ++currPtr )
	{
		std::cout << "my card rank: " << ( *currPtr )->GetRank() << std::endl;
		std::cout << "my card suit: " << ( *currPtr )->GetSuit() << std::endl;
		std::cout << "my card point: " << ( *currPtr )->GetPoint() << std::endl;

		switch( ( *currPtr )->GetCardType() )
		{
			case ( ENUM_CardType::CARDTYPE_natural ):
			{
				std::cout << "my card type: CARDTYPE_natural" << std::endl;
				break;
			}
			case ( ENUM_CardType::CARDTYPE_wildCard ):
			{
				std::cout << "my card type: CARDTYPE_wildCard" << std::endl;
				break;
			}
			case ( ENUM_CardType::CARDTYPE_redThree ):
			{
				std::cout << "my card type: CARDTYPE_redThree" << std::endl;
				break;
			}
			case ( ENUM_CardType::CARDTYPE_blackThree ):
			{
				std::cout << "my card type: CARDTYPE_blackThree" << std::endl;
				break;
			}
			default:
				std::cout << "my card type: error" << std::endl;

				break;
		}

		std::cout << "my card print function: " << ( *currPtr )->GetRankSuit() << std::endl << std::endl;

	}
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