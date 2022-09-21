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

	//std::vector<Card*> myCards;

	//myCards.push_back( new Card( 'J', '1' ) );
	//myCards.push_back( new Card( 'J', '2' ) );
	//myCards.push_back( new Card( 'k', 'd' ) );
	//myCards.push_back( new Card( '2', 'c' ) );
	//myCards.push_back( new Card( '3', 'd' ) );
	//myCards.push_back( new Card( '3', 's' ) );

	//for( auto currPtr = myCards.begin(); currPtr != myCards.end(); ++currPtr )
	//{
	//	( *currPtr )->Debug();
	//}

	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " == " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) == *( myCards[ 0 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " == " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) == *( myCards[ 1 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " != " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) != *( myCards[ 0 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " != " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) != *( myCards[ 1 ] ) ) << std::endl << std::endl;

	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " <  " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) < *( myCards[ 1 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " <  " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) < *( myCards[ 0 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " <= " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) <= *( myCards[ 1 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " <= " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) <= *( myCards[ 0 ] ) ) << std::endl << std::endl;

	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " > " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) > *( myCards[ 1 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " > " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) > *( myCards[ 0 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 1 ]->GetRankSuit() << " >= " << myCards[ 0 ]->GetRankSuit() << " " << ( *( myCards[ 1 ] ) >= *( myCards[ 0 ] ) ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " >= " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) >= *( myCards[ 1 ] ) ) << std::endl << std::endl;

	////std::cout << "copying last element of the vector" << std:: endl;
	////Card* copyCard = new Card( *( *( --( myCards.end() ) ) ) );
	////copyCard->Debug();

	////std::cout << "assginming last element of the vector" << std::endl;
	////Card assignCard;
	////assignCard = *copyCard;

	////assignCard.Debug();

	//Deck myDeck;
	//myDeck.PrintDeck();
	////myDeck.Shuffel();
	////myDeck.PrintDeck();

	//myDeck.DealCard();

	//myDeck.PrintDeck();

	//Deck myDeck1( "6S 7D 2H 9S 3C 8H J2 2C KS XH QD 6C XC KD" );
	//myDeck1.PrintDeck();

	//Hand myhand( "2S QC QS 2C QC 3H", "[3H]" );
	//myhand.PrintHand();

	//Hand myhand2( myhand );
	//myhand2.PrintHand();

	//Hand myhand3;
	//myhand3 = myhand;
	//myhand3.PrintHand();

	//myhand3.AddCardToHand( Card( "QH" ) );
	//myhand3.PrintHand();

	//myhand3.AddRed3CardToMeld( 5  );
	//myhand3.MakeMeld( { 0, 1, 2, 3 } );

	//myhand3.PrintHand();

	//myhand3.AddCardToHand( Card( "J1" ) );

	//myhand3.AddWildCardToMeld( myhand3.GetTotalHandCardNum() - 1, myhand3.GetTotalMeldNum());
	//myhand3.PrintHand();
	//std::cout << myhand3.TallyPoints() << std::endl;

	//myhand3.SwapHandCardPos( 0,1 );
	//myhand3.PrintHand();
	//myhand3.TakeOutWildCard( 3, myhand3.GetTotalMeldNum());
	//myhand3.PrintHand();
	//myhand3.TakeOutWildCard( 3, myhand3.GetTotalMeldNum() );
	//myhand3.PrintHand();
	//myhand3.TakeOutWildCard( 2, myhand3.GetTotalMeldNum() );
	//myhand3.PrintHand();

	//std::cout << myhand3.TallyPoints() << std::endl;
	//myhand3.Discard(0);


	//std::cout << myhand3.TallyPoints() << std::endl;


	//Hand myHand4("J1 AS KS QS JS XS 9S 8S 7S 6S 5S 4S 3S 2S", "");
	//
	//myHand4.PrintHand();

	Player myPlayer( "2S QC QS 2C QC 3H", "[3H]" );
	//myPlayer.PrintPlayer();

	Player myPlayer1( myPlayer );
	myPlayer1.PrintPlayer();

	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	Player myPlayer2;
	//myPlayer2.PrintPlayer();

	myPlayer2 = myPlayer1;
	myPlayer2.SetTotalPoint( 200 );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	myPlayer2.AddCardToHand( Card( "QH" ) );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	myPlayer2.AddToMeld( 5, 0 );
	myPlayer2.MakeNewMeld( { 0, 1, 2, 3 } );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	myPlayer2.AddToMeld( 0, 3 );
	myPlayer2.PickUpDiscardPile( std::stack<Card>( { Card( "QC" ),Card( "QS" ) } ) );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	myPlayer2.SwapHandCardPos( 0, 1 );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	myPlayer2.Discard( 0 );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	myPlayer2.TakeOutWildCard( 3, 3 );
	myPlayer2.PrintPlayer();
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;
	myPlayer2.AddToMeld( 0, 3 );
	myPlayer2.AddToMeld( 0, 3 );
	myPlayer2.AddToMeld( 0, 3 );
	myPlayer2.PrintPlayer();


	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;

	std::cout << std::boolalpha << myPlayer2.CanAddToMeld( Card( "QS" ) ).first << std::endl;
	std::cout << std::boolalpha << myPlayer2.CanAddToMeld( Card( "KS" ) ).first << std::endl;


	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;
	//std::cout << std::boolalpha << myCards[ 0 ]->GetRankSuit() << " != " << myCards[ 1 ]->GetRankSuit() << " " << ( *( myCards[ 0 ] ) != *( myCards[ 1 ] ) ) << std::endl << std::endl;
	std::cout << std::boolalpha << myPlayer2.CanGoOut() << std::endl;
	std::cout << std::setw( 20 ) << std::setfill( '-' ) << "" << std::setfill( ' ' ) << std::endl;
	/*
	myhand3.PrintHand();

	myhand3.AddRed3CardToMeld( 5 );

	myhand3.PrintHand();

	myhand3.AddCardToHand( Card( "J1" ) );

	myhand3.AddWildCardToMeld( myhand3.GetTotalHandCardNum() - 1, myhand3.GetTotalMeldNum() );
	myhand3.PrintHand();
	std::cout << myhand3.TallyPoints() << std::endl;

	myhand3.SwapHandCardPos( 0, 1 );
	myhand3.PrintHand();
	myhand3.TakeOutWildCard( 3, myhand3.GetTotalMeldNum() );
	myhand3.PrintHand();
	myhand3.TakeOutWildCard( 3, myhand3.GetTotalMeldNum() );
	myhand3.PrintHand();
	myhand3.TakeOutWildCard( 2, myhand3.GetTotalMeldNum() );
	myhand3.PrintHand();

	std::cout << myhand3.TallyPoints() << std::endl;
	myhand3.Discard( 0 );


	std::cout << myhand3.TallyPoints() << std::endl;*/


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