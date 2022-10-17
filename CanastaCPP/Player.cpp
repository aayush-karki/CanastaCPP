/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: default construct a Player object and to populate its member
		variables m_playerHand is populated using the passed parameter.
Parameters:
			a_totalScore, a unsinged integer containing the player's
				total score.
			a_handCards, a string containing the rank and suit of cards.
				Each card is seperated by blank space.
			a_meldCards, a string containing the rank and suit of cards
				in the m_stock. Each card is seperated by blank space
				and each meld is inside '[' and ']'
Return Value: none
Algorithm:
			1) call constructor for m_playerHand and pass the
				a_handCards and a_meldCards as parameters
			2) set the m_totalPoints to 0
Assistance Received: cplusplus
********************************************************************* */
Player::Player( unsigned a_totalScore,
				std::string a_handCards,
				std::string a_meldCards ) :
	m_playerHand( a_handCards, a_meldCards ),
	m_totalPoints( a_totalScore ),
	m_isStartOfTurn( true ),
	m_showBeforeTurnMenu( true ),
	m_wentOut( false )
{}

/* *********************************************************************
Function Name: Player
Purpose: To create a new Player object and copy the passed Player object's
		member variables data into the newly created Player object
Parameters:
			a_other, a constant object of Player class passed by
				reference. It holds a Player object to be copied.
Return Value: none
Algorithm:
			1) Copy the passed Player's hand by calling the hand's copy
				constructor
			2) copy the m_totalPoint
Assistance Received: none
********************************************************************* */
Player::Player( const Player& a_other ) :
	m_playerHand( a_other.m_playerHand ),
	m_totalPoints( a_other.m_totalPoints ),
	m_isStartOfTurn( a_other.m_isStartOfTurn ),
	m_showBeforeTurnMenu( a_other.m_showBeforeTurnMenu ),
	m_wentOut( a_other.m_wentOut )
{}

/* *********************************************************************
Function Name: operator=
Purpose: To deep-copy the passed Player object's member variables data into
		this Player object
Parameters:
			a_other, a constant object of player class passed by reference.
				It holds a player object that is used to assign this
				player object.
Return Value: its own memory address
Algorithm:
			1) check for self assignment, if yes then return the
				pointer to self
			2) use the hand assignment operator to deep copy a_other's
				m_playerHand into this player's m_playerHand
			3) copy the m_totalPoint
Assistance Received: none
********************************************************************* */
Player& Player::operator=( const Player& a_other )
{
	// checking for self assignment
	if( this == &a_other )
	{
		return *this;
	}

	// coypying of the passed player's hand
	this->m_playerHand = a_other.m_playerHand;
	this->m_isStartOfTurn = a_other.m_isStartOfTurn;
	this->m_showBeforeTurnMenu = a_other.m_showBeforeTurnMenu;
	this->m_totalPoints = a_other.GetTotalPoint();
	this->m_wentOut = a_other.m_wentOut;

	return *this;
}

/* *********************************************************************
Function Name: PlayerTurnController
Purpose: Contains the logic for start of the turn asks user for what to
	do
Parameters: none
Return Value:
			pair of <integer ,  std::vector<unsigned>>. The first interger
			indicates where this was--that is beforeTurnStartLogic == 1,
			turnStartLlogic == 2, or afterTurnStartLogic == 3 or 10 for
			invalid input. the second is vector of unsinged integer whose
			first element is always the sub menu index or 10 for invalid
			input and every thing after that is what the it
			sub menus's funciton needs
Algorithm: none
Assistance Received: none
********************************************************************* */
std::pair<unsigned, std::vector<unsigned>> Player::PlayerTurnController( const std::vector<std::vector<Card>> a_otherPlayerMeld,
																		 const std::vector<Card> a_discardPile )
{
	std::pair<unsigned, std::vector<unsigned>> playerResponse = { 10,  std::vector<unsigned>() };

	// before turn menu with function to save, take a turn
	if( m_showBeforeTurnMenu )
	{
		return BeforeTurnStartControl();
	}
	else if( m_isStartOfTurn )
	{
		return TurnStartControl( a_discardPile );
	}

	return TurnContinueControl( a_otherPlayerMeld, a_discardPile );
}

/* *********************************************************************
Function Name: BeforeTurnStartControl
Purpose: Contains the controller for before a turn starts
	and asks the user to chose from "Save the game", "Take a turn" ,
	or "Quit the game and go to main menu"
Parameters: none
Return Value:
			pair of <integer ,  std::vector<unsigned>>. The first interger
			indicates this was--that is beforeTurnStartLogic so it is
			always 1. the second is vector of unsinged integer of size 1 and
			the the vector's first element is the sub menu index.
Algorithm:
		1) prompt the user
		2) get user input and validate it
		3) if invalid return {10,{10}} else return {1, {userInput}}
Assistance Received: none
********************************************************************* */
std::pair<unsigned, std::vector<unsigned>> Player::BeforeTurnStartControl()
{

	// now Player have the following choices:
	// 1) Save the game -> enter 1
	// 2) Take a turn -> enter 2
	// 3) Quit the game and go to main menu -> enter 3
	std::cout << "Menu:" << std::endl;
	std::cout << "\t1) Save the game -> enter 1" << std::endl;
	std::cout << "\t2) Take a turn -> enter 2" << std::endl;
	std::cout << "\t3) Quit the game and go to main menu -> enter 3" << std::endl;
	std::cout << std::endl;

	std::cout << "Enter a corresponding number: ";

	// used to get the userInput
	std::string userInputStr;
	std::getline( std::cin, userInputStr );

	// validaing the userInput
	// a valid user input is 1, or 2, or 3
	int vadiatedNum = ValidateNumber( userInputStr, 1, 3 );

	if( vadiatedNum < 0 )
	{
		// invalid input
		Message::AddMessage( "Invalid Input!!" );
		return { 10, {10} };
	}
	return { 1, {( unsigned )vadiatedNum} };

}

/* *********************************************************************
Function Name: TurnStartControl
Purpose: Contains the controller for turn starts. this is executed when
		two is selected from beforeTurnStartControl. It asks  user to
		chose from "draw a card from deck", "pick up the discard pile",
		"Ask for Help",	"show discard pile", or
		"show stock card (for debugging)"
Parameters:
			a_discardPile, a const vector of cards that contains the
				discard pile
Return Value:
			pair of <integer ,  std::vector<unsigned>>. The first interger
			indicates this was--that is TurnStartconstrol so it is
			always 2. the second is vector of unsinged integer of size 1 and
			the the vector's first element is the sub menu index.
Algorithm:
		1) prompt the user
		2) get user input and validate it
		3) if invalid return {10,{10}} else return {2, {userInput}}
Assistance Received: none
********************************************************************* */
std::pair<unsigned, std::vector<unsigned>> Player::TurnStartControl( const std::vector<Card> a_discardPile )
{
	// (2) Take a turn was pressed

	// at the start of the turn, player have 5 choices:
	//	1) ask for help -> enter 1
	//	2) draw a card from deck -> enter 2
	//	3) pick up the discard pile -> enter 3
	//	4) show discard pile -> enter 4
	//	5) show stock card (for debugging) -> enter 5

	std::cout << "Taking a turn:" << std::endl;
	std::cout << "\t1) Ask for help -> enter 1" << std::endl;
	std::cout << "\t2) Draw a card from deck -> enter 2" << std::endl;
	std::cout << "\t3) Pick up the discard pile -> enter 3" << std::endl;
	std::cout << "\t4) Show discard pile -> enter 4" << std::endl;
	std::cout << "\t5) Show stock card (for debugging) -> enter 5" << std::endl;
	std::cout << std::endl;


	std::cout << "Enter a corresponding number: ";

	// used to get the userInput
	std::string userInputStr;
	std::getline( std::cin, userInputStr );

	// validaing the userInput
	// a valid user input is 1, or 2, or 3, or 4, or 5
	int vadiatedNum = ValidateNumber( userInputStr, 1, 5 );

	if( vadiatedNum < 0 )
	{
		// invalid input
		Message::AddMessage( "Invalid Input!!" );
		return { 10, {10} };
	}
	return { 2, {( unsigned )vadiatedNum} };
}

/* *********************************************************************
Function Name: TurnContinueControl
Purpose: Contains the controller for turn to continue.aftere the player
		has either drawn a card or picked up the discard pile.
		It asks  user to chose from "draw a card from deck", 
		"pick up the discard pile", "Ask for Help",	
		"show discard pile", "show stock card (for debugging)",
		or "take out card from meld"
Parameters:
			a_discardPile, a const vector of cards that contains the
				discard pile
Return Value:
			pair of <integer ,  std::vector<unsigned>>. The first
			interger indicates this was--that is TurnStartconstrol 
			so it is always 3. the second is vector of unsinged 
			integer the the vector's first element is the sub menu 
			index. rest of the element depends on the submenu chosen
Algorithm:
		1) prompt the user
		2) get user input
		3) parse the userinput and store it as a vector of string
		4) declare a vectore of insigned named validVec
		4) if the first parsed userInput is >=1 and <= 8 then it 
			is valid store it validVec ; else return code
		5) if the first parsed userInput is 1, or 4, 
			or 6, or 7 then check if there are no other user input
			in the parsed vector then return {3, validVec}; else
			return error code
		6) if the first parsed userInput is 3 then check if the 
			parsed vec has one more input and validate it as card
			index in actual hand and return {3,validvec}; else 
			return error code
		7) if the first parsed userInput is 2 then check if the
			parsed vec has two more input and validate them with 
			first being card in actual hand and second being meld
			index and return {3,validvec}; else return error code
		8) if the first parsed userInput is 5 then check if the
			parsed vec size is more than 4 inputs and validate 
			them with all of them being card idx in actual hand 
			and return {3,validvec}; else return error code
		9)  if the first parsed userInput is 8 then check if the
			parsed vec size has 2 more inputs and validate 
			them with first being card idx in meld and second 
			being meld idx and return {3,validvec}; else return error code
Assistance Received: none
********************************************************************* */
std::pair<unsigned, std::vector<unsigned>> Player::TurnContinueControl( const std::vector<std::vector<Card>> a_otherPlayerMeld,
																		const std::vector<Card> a_discardPile )
{
	// player has drawns a card or picked up the discard pile

	// now player have 6 choices until they discard or go out:
	// else it is not the start of the round so they have 5 choices
	//	1) Ask for help -> enter 1
	//	2) Add a card in hand to meld -> enter 2 <actualHandCardIdx> <meldIdx>
	//	3) Discard a card from hand -> enter 3 <actualHandCardIdx>
	//	4) Go out -> enter 4
	//	5) Make a new meld -> enter 5 <actualHandCardIdx> <actualHandCardIdx> <actualHandCardIdx> ...
	//	6) Show discard pile -> enter 6
	//	7) Show stock card (for debugging) -> enter 7
	//	8) Take out wild card From meld -> enter 8 <meldCardIdx> <meldIdx>

	std::cout << "Taking a turn:" << std::endl;
	std::cout << "\t1) Ask for help -> enter 1" << std::endl;
	std::cout << "\t2) Add a card in hand to meld -> enter 2 < actualHandCardIdx > < meldIdx>" << std::endl;
	std::cout << "\t3) Discard a card from hand -> enter 3 < actualHandCardIdx >" << std::endl;
	std::cout << "\t4) Go out -> enter 4" << std::endl;
	std::cout << "\t5) Make a new meld -> enter 5 < actualHandCardIdx > <actualHandCardIdx> <actualHandCardIdx> ..." << std::endl;
	std::cout << "\t6) Show discard pile -> enter 6" << std::endl;
	std::cout << "\t7) Show stock card( for debugging ) -> enter 7" << std::endl;
	std::cout << "\t8) Take out wild card From meld -> enter 8 < meldCardIdx > <meldIdx>" << std::endl;

	std::cout << std::endl;

	std::cout << "Enter a corresponding number: ";

	// used to get the userInput
	std::string userInputStr;
	std::getline( std::cin, userInputStr );

	// extracting user input
	std::vector<std::string> extractedUserInputStrVec;
	extractedUserInputStrVec.reserve( userInputStr.size() / 2 + 2 );

	std::string extractedStr = "";
	std::stringstream passedStringStream( userInputStr );

	// extracting each indivisual string
	while( passedStringStream >> extractedStr )
	{
		extractedUserInputStrVec.push_back( extractedStr );
	}

	// validaing the userInput
	// 1) a first valid user input is 1, or 2, or 3, or 4, 
	//		 or 5, or 6, or 7, or 8
	// 2) then if it is 1, or 4, or 6, or 7 there should
	//		 not be any other number after it
	// 3) if it is 3 then it should have one number after 
	//		it that represents the card in actual hand
	// 4) if it is 2 then it should have 2 number after
	//		it, these 2 number represents the card idx
	//		in actual hand and meld idx in the hand
	// 5) if it is 5 then it should have atlease 3 number 
	//		after it, these number represents the 
	//		card idx in actual hands
	// 6) if it is 8 then it should have 2 number after
	//		it, these 2 number represents the card idx
	//		in meld and the and meld idx in the hand
	// holds the parsed user input if they are valid
	std::vector<unsigned> validUserInputVec;
	validUserInputVec.reserve( userInputStr.size() / 2 + 2 );

	// validating 1) -> a first valid user input
	//		   is 1, or 2, or 3, or 4, or 5, or 6, or 7, or 8
	int vadiatedNum = ValidateNumber( extractedUserInputStrVec.front(), 1, 8 );

	if( vadiatedNum < 0 )
	{
		// invalid input
		Message::AddMessage( "Invalid menu chosen!!" );
		return { 10, {10} };
	}
	validUserInputVec.push_back( vadiatedNum );

	// validating 2) -> then if it is 1, or 4, or 6, or 7 
	//		 there should not be any other number after it
	if( validUserInputVec.front() == 1 || validUserInputVec.front() == 4
		|| validUserInputVec.front() == 6 || validUserInputVec.front() == 7 )
	{
		if( extractedUserInputStrVec.size() == 1 )
		{
			// valid input
			return { 3,validUserInputVec };
		}
		else
		{
			// invalid input
			Message::AddMessage( "Invalid number of input argument for the chosen menu!!" );
			return { 10, {10} };
		}
	}

	// validating 3) -> if it is 3 then it should have one number after 
	//		it that represents the card in actual hand
	if( validUserInputVec.front() == 3 )
	{
		if( extractedUserInputStrVec.size() == 2 )
		{
			// the max idx that it can be is the actual hand size - 1
			vadiatedNum = ValidateNumber( extractedUserInputStrVec.back(), 0, m_playerHand.GetActualHand().size() - 1 );

			if( vadiatedNum < 0 )
			{
				// invalid input
				Message::AddMessage( "Invalid actual hand index!!" );
				return { 10, {10} };
			}
			validUserInputVec.push_back( vadiatedNum );

			// valid input
			return { 3,validUserInputVec };
		}
		else
		{
			// invalid input
			Message::AddMessage( "Invalid number of input argument for the chosen menu!!" );
			return { 10, {10} };
		}
	}

	// validating 4) -> if it is 2 then it should have 2 number after
	//		it, these 2 number represents the card idx
	//		in actual hand and meld idx in the hand
	if( validUserInputVec.front() == 2 )
	{
		if( extractedUserInputStrVec.size() == 3 )
		{
			// validating the actualCardIdx  which is the second number
			// the max idx that it can be is the actual hand size - 1
			vadiatedNum = ValidateNumber( extractedUserInputStrVec.at( 1 ), 0, m_playerHand.GetTotalHandCardNum() - 1 );

			if( vadiatedNum < 0 )
			{
				// invalid input
				Message::AddMessage( "Invalid actual hand index!!" );
				return { 10, {10} };
			}
			validUserInputVec.push_back( vadiatedNum );

			// validating the meldIdx which is the last number
			// the max idx that it can be is the hand size - 1
			vadiatedNum = ValidateNumber( extractedUserInputStrVec.back(), 0, m_playerHand.GetTotalMeldNum() );

			if( vadiatedNum < 0 )
			{
				// invalid input
				Message::AddMessage( "Invalid meld index!!" );
				return { 10, {10} };
			}
			validUserInputVec.push_back( vadiatedNum );

			// valid input
			return { 3,validUserInputVec };
		}
		else
		{
			// invalid input
			Message::AddMessage( "Invalid number of input argument for the chosen menu!!" );
			return { 10, {10} };
		}
	}

	// validating 5) -> if it is 5 then it should have atlease 3 number 
	//		after it, these number represents the card idx in actual hands
	if( validUserInputVec.front() == 5 )
	{
		if( extractedUserInputStrVec.size() >= 4 )
		{
			// validating all the passed the actualCardIndes

			for( unsigned strVecidx = 1; strVecidx < extractedUserInputStrVec.size(); ++strVecidx )
			{
				// the max idx that it can be is the actual hand size - 1
				vadiatedNum = ValidateNumber( extractedUserInputStrVec.at( strVecidx ), 0, m_playerHand.GetTotalHandCardNum() - 1 );

				if( vadiatedNum < 0 )
				{
					// invalid input
					Message::AddMessage( "Invalid actual hand index!!" );
					return { 10, {10} };
				}
				validUserInputVec.push_back( vadiatedNum );
			}

			// valid input
			return { 3,validUserInputVec };
		}
		else
		{
			// invalid input
			Message::AddMessage( "Invalid number of input argument for the chosen menu!!" );
			return { 10, {10} };
		}
	}

	// validating 6) -> if it is 2 then it should have 2 number after
	//		it, these 2 number represents the card idx
	//		in meld and meld idx in the hand
	if( validUserInputVec.front() == 8 )
	{
		if( extractedUserInputStrVec.size() == 3 )
		{

			// validating the meldIdx which is the last number
			// the max idx that it can be is the hand size - 1
			unsigned validatedMeldIdx = ValidateNumber( extractedUserInputStrVec.back(), 0, m_playerHand.GetTotalMeldNum() );

			if( validatedMeldIdx < 0 )
			{
				// invalid input
				Message::AddMessage( "Invalid meld index!!" );
				return { 10, {10} };
			}

			// validating the actualCardIdx  which is the second number
			// the max idx that it can be is the actual hand size - 1
			vadiatedNum = ValidateNumber( extractedUserInputStrVec.at( 1 ), 0, m_playerHand.GetMelds().at( validatedMeldIdx - 1).size() - 1 );

			if( vadiatedNum < 0 )
			{
				// invalid input
				Message::AddMessage( "Invalid actual hand index!!" );
				return { 10, {10} };
			}

			// adding the numbes in the same order
			validUserInputVec.push_back( vadiatedNum );
			validUserInputVec.push_back( validatedMeldIdx );
			// valid input
			return { 3,validUserInputVec };
		}
		else
		{
			// invalid input
			Message::AddMessage( "Invalid number of input argument for the chosen menu!!" );
			return { 10, {10} };
		}
	}

	// invalid input
	Message::AddMessage( "Invalid Input!!" );
	return { 10, {10} };

}

/* *********************************************************************
Function Name: AddToMeld
Purpose: Tries to add the card at passed index to a already existing
	meld.
Parameters:
			a_handCardIdx, a unsigned integer. It holds the index of the
				the card at actual hand that need to be moved
Return Value:
			a pair of < bool, string >, < true, empty string > if the card was
				moved to a meld successfully. else  < false, message string >
Algorithm:
			1) Get the passed card type and call the appropriate add to meld
				funciton
Assistance Received: none
********************************************************************* */
std::pair<bool, std::string> Player::AddToMeld( unsigned a_handCardIdx,
												unsigned a_meldIdx )
{
	switch( m_playerHand.GetCardAtIdx( 0, a_handCardIdx ).GetCardType() )
	{
		case ( ENUM_CardType::CARDTYPE_natural ):
		{
			return m_playerHand.AddNaturalCardToMeld( a_handCardIdx, a_meldIdx );
		}
		case ( ENUM_CardType::CARDTYPE_wildCard ):
		{
			return m_playerHand.AddWildCardToMeld( a_handCardIdx, a_meldIdx );
		}
		case ( ENUM_CardType::CARDTYPE_redThree ):
		{
			return m_playerHand.AddRed3CardToMeld( a_handCardIdx );
		}
		case ( ENUM_CardType::CARDTYPE_blackThree ):
		{
			return { false, "Cannot meld a Black 3" };
		}
		default:
		{
			return { false, "Card Type not found." };
		}
	}
}

/* *********************************************************************
Function Name: PickUpDiscardPile
Purpose: Adds all the card in to the actual hand of the player
Parameters:
			a_discardPile, a stack of card passed by value. It hold all
				the cards discarded by both player that needs to be
				added to this player's actual hand
Return Value:
			true to indicate that discard pile was successfully added to
				player's actual hand
Algorithm:
			1) loop over the stack and add each card to hand
				2) if error break;
Assistance Received: none
********************************************************************* */
bool Player::PickUpDiscardPile( std::stack<Card> a_discardPile )
{
	std::pair< bool, std::string > result;

	while( !a_discardPile.empty() )
	{
		if( !m_playerHand.AddCardToHand( a_discardPile.top() ) )
		{
			break;
		}

		a_discardPile.pop();
	}

	return a_discardPile.empty();
}

/* *********************************************************************
Function Name: PrintHand
Purpose: To print out the m_hand and scored
Parameters: none
Return Value: none
Algorithm:
			1) Call m_playerHand's PrintHand function
			2) Print this round score and total score
Assistance Received: none
********************************************************************* */
void Player::PrintPlayer() const
{
	m_playerHand.PrintHand();
	std::cout << "\t" << "Player's Round Score: " << std::setw( 5 ) << TallyHandPoint() << std::endl;
	std::cout << "\t" << "Player's Total Score: " << std::setw( 5 ) << m_totalPoints << std::endl << std::endl;
}



/* *********************************************************************
Function Name: ResetPlayerForNewRound
Purpose: Resets playe's hand and flag to prepare for new round
Parameters: none
Return Value:
			bool to indicate a successfull reset
Algorithm:
			1) empty player hand
			2) reset all the flags
Assistance Received: none
********************************************************************* */
bool Player::ResetPlayerForNewRound()
{
	// clearing player's hand
	EmptyHand();

	m_isStartOfTurn = true;
	m_showBeforeTurnMenu = true;
	m_wentOut = false;
	m_isStartOfTurn = true;

	return true;

}


/* *********************************************************************
Function Name: ValidateNumber
Purpose: validate that rhe passed string is a number that is
		between lowerLimit and upperLimit inclusively. if yes
		return the integer else -1
Parameters:
			a_numToValidate, a string containing the number that is to
				be validated
			a_inclusiveLowerBound, unsigned integer. lower bound that the
				passed number can be. It includes itself.
			a_inclusiveUpperBound, unsigned integer. upper bound that the
				passed number can be. It includes itself .
Return Value:
			interger. if the passed number is valid then it returns the
				number as a interger. else returns -1
Algorithm:
		1) if the size of the passed string is <= size of the
			passed a_inclusiveUpperBound and for every char in passed
			string check it is a digit
		2)		then convert passed string to interger
		3)		if the converted number is between passed lower
					and upper bound return the number
		4)		else return -1
Assistance Received: none
********************************************************************* */
int Player::ValidateNumber( std::string a_numToValidate,
							unsigned a_inclusiveLowerBound,
							unsigned a_inclusiveUpperBound )
{
	// chekcing if the every char in the passed string is a digit or not
	if( a_numToValidate.size() <= std::to_string( a_inclusiveUpperBound ).size()
		&& std::all_of( a_numToValidate.begin(), a_numToValidate.end(), []( char c ){return std::isdigit( c ); } ) )
	{

		// chcecking if the a_inclusiveLowerBound <= user input <= a_inclusiveUpperBound
		unsigned userInputInt = 0;
		std::stringstream strStream( a_numToValidate );
		strStream >> userInputInt;

		if( userInputInt >= a_inclusiveLowerBound && userInputInt <= a_inclusiveUpperBound )
		{
			return userInputInt;
		}
	}

	return -1;
}
