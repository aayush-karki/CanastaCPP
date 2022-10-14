/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: To construct a Player object and to populate its member variables.
Parameters: none
Return Value: none
Algorithm:
		1) call default constructor for m_playerHand
		2) set the m_totalPoints to 0
Assistance Received: none
********************************************************************* */
Player::Player()
	: m_playerHand(), m_totalPoints( 0 ),
	m_isStartOfTurn( true ), m_showBeforeTurnMenu( true )
{}

/* *********************************************************************
Function Name: Player
Purpose: To construct a Player object and to populate its member variables
		m_playerHand is populated using the passed parameter.
Parameters:
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
Player::Player( std::string a_handCards, std::string a_meldCards ) :
	m_playerHand( a_handCards, a_meldCards ), m_totalPoints( 0 ),
	m_isStartOfTurn( true ), m_showBeforeTurnMenu( true )
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
	m_showBeforeTurnMenu( a_other.m_showBeforeTurnMenu )
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

	return *this;
}

/* *********************************************************************
Function Name: SetTotalPoint
Purpose: Tries to add the card at passed index to a already existing
	meld.
Parameters:
			a_totalPoint, an integer. It holds the new total points
				of the player.
Return Value:
			bool to indicate m_totalPoints were successfully saved
Algorithm: none
Assistance Received: none
********************************************************************* */
bool Player::SetTotalPoint( int a_totalPoint )
{
	m_totalPoints = a_totalPoint;
	return true;
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
void Player::PrintPlayer()
{
	m_playerHand.PrintHand();
	std::cout << "\t" << "Player's Round Score: " << std::setw( 5 ) << TallyHandPoint() << std::endl;
	std::cout << "\t" << "Player's Total Score: " << std::setw( 5 ) << m_totalPoints << std::endl << std::endl;
}

/* *********************************************************************
Function Name: BeforeTurnStartControl
Purpose: Contains the controller for before a turn starts 
	and asks the user to chose from "Save the game", "Take a turn" , 
	"Ask for Help", or "Quit the game and go to main menu"
Parameters: none
Return Value:
			unsigned value. If the return is the selected menu item index
Algorithm: none
Assistance Received: none
********************************************************************* */
unsigned Player::BeforeTurnStartControl()
{
	unsigned userInputInt;
	bool validInput = true;
	do
	{
		// now Player have the following choices:
		// 1) Save the game
		// 2) Take a turn
		// 3) Ask for Help
		// 4) Quit the game and go to main menu
		std::cout << "Menu:" << std::endl;
		std::cout << "\t1) Save the game" << std::endl;
		std::cout << "\t2) Take a turn" << std::endl;
		std::cout << "\t3) Ask for Help" << std::endl;
		std::cout << "\t4) Quit the game and go to main menu" << std::endl;
		std::cout << std::endl;

		if( !validInput )
		{
			Message::AddMessage( "Invalid Input!!" );
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

			if( userInputInt >= 1 && userInputInt <= 4 )
			{
				return  userInputInt;
			}
		}

		validInput = false;

	} while( !validInput );


	//// doing what user chose
	//switch( userInputInt )
	//{
	//	case 1:
	//	{
	//		// 1) Save the game
	//		// TODO Call the save function
	//		std::cout << "Save the game selected" << std::endl;

	//		break;
	//	}
	//	case 2:
	//	{
	//		// 2) Take a turn
	//		//  when taking a turn player
	//		// if it is the start of the turn player have 2 choices
	//		//		a) draw a card from deck
	//		//		b) pick up the discard pile
	//		// else it is not the start of the round so they have 5 choices
	//		//		a) add a card in hand to meld 
	//		//		b) discard a card from hand
	//		//		b) make a new meld
	//				c) ask for help
	//		//		d) sort // maybe auto sort ?
	//				e) swap the hand
	//		// 
	//		//m_playerList.at( (unsigned)m_playerTurn )
	//		if( m_isStartOfTurn )
	//		{
	//			//bool Player
	//		}
	//		break;
	//	}
	//	case 3:
	//	{
	//		// 3) Ask for Help
	//		std::cout << "ask for help selected" << std::endl;

	//		break;
	//	}
	//	case 4:
	//	{
	//		// 4) Quit the game and go to main menu
	//		std::cout << "quit game and go to main menu selected" << std::endl;
	//		return { true, 4 };
	//		break;
	//	}
	//	default:
	//	{
	//		std::cerr << "This should never be printed." << std::endl;
	//		std::cerr << "\tplayer choice menu default" << std::endl;
	//		return { false, -1 };
	//		break;
	//	}
	//}

	//// if take a turn was pressed then returns true
	//return { userInputInt != 4, -1 };
}

/* *********************************************************************
Function Name: PlayerTurnController
Purpose: Contains the logic for start of the turn asks user for what to
	do
Parameters: none
Return Value:
			pair of <integer ,  std::vector<unsigned>>. The first interger 
			indicates where this was--that is beforeTurnStartLogic, 
			turnStartLlogic, or afterTurnStartLogic. the second is vector
			of unsinged integer whose first elemetn is always the sub menu
			index and every thing after that is what the m
Algorithm: none
Assistance Received: none
********************************************************************* */
std::pair<unsigned, std::vector<unsigned>> Player::PlayerTurnController( const Player* a_otherPlayer,
																		const std::stack<Card> a_discardPile )
{
	
	std::pair<unsigned, std::vector<unsigned>> playerResponse = {10,  std::vector<unsigned>()};

	if( m_isStartOfTurn )
	{
		playerResponse.first = BeforeTurnStartControl();

		// checking if the player responded with 2 then take a turn was selected
		// then in the next loop before turn start control should not be displayed
		m_isStartOfTurn = ( playerResponse.first != 2 );
	}



	return playerResponse;
}
