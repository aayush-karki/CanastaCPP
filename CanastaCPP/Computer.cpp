/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Computer.h"

/* *********************************************************************
Function Name: operator=
Purpose: To deep-copy the passed Computer object's member variables data into
		this Computer object
Parameters:
			a_other, a constant object of Computer class passed by reference.
				It holds a Computer object that is used to assign this
				Computer object.
Return Value: its own memory address
Algorithm:
			1) call player's assignemnt operator
			3) copy the m_totalPoint
Assistance Received: none
********************************************************************* */
Computer& Computer::operator=( const Computer& a_other )
{
	// checking for self assignment
	if( this == &a_other )
	{
		return *this;
	}

	Player::operator=( a_other );

	return *this;
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
		1) call the turn start Help and retunr the result
Assistance Received: none
********************************************************************* */
std::pair<unsigned, std::vector<unsigned>> Computer::TurnStartControl( const std::vector<Card>& a_discardPile )
{
	// (2) Take a turn was pressed

	// at the start of the turn, computer has 2 choices:
	//	1) draw a card from deck -> enter 2
	//	2) pick up the discard pile -> enter 3

	auto startResult = TurnStartHelp( a_discardPile );
	Message::AddMessage( "Computer: " + startResult.second );
	Message::AddMessage( "" );

	return startResult.first;
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
std::pair<unsigned, std::vector<unsigned>> Computer::TurnContinueControl( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																		  const std::vector<Card>& a_discardPile )
{
	// player has drawns a card or picked up the discard pile

	// now computer can make 1 of 5 choices until they discard or go out:
	// else it is not the start of the round so they have 5 choices
	//	2) Add a card in hand to meld -> enter 2 <actualHandCardIdx> <meldIdx>
	//	3) Discard a card from hand -> enter 3 <actualHandCardIdx>
	//	4) Go out -> enter 4
	//	5) Make a new meld -> enter 5 <actualHandCardIdx> <actualHandCardIdx> <actualHandCardIdx> ...
	//	8) Take out wild card From meld -> enter 8 <meldCardIdx> <meldIdx>


	auto startResult = TurnContinueHelp( a_otherPlayerMeld, a_discardPile );
	Message::AddMessage( "Computer: " + startResult.second );
	Message::AddMessage( "" );

	return startResult.first;

}

/* *********************************************************************
Function Name: TurnStartHelp
Purpose: Decides what to do in the turn start menu. It choses between
		to pick up the discard pile and drawing
Parameters:
			a_discardPile, a const vector of cards that contains the
				discard pile
Return Value:
			<pair of <pair of <integer ,  std::vector<unsigned>>, string>.
			The inside pair contains the current submenu index which is 2
			and the choice. The out side pair's second contains the
			reasoning behind its choice.
Algorithm:
		1) if the top of the discard pile is frozen then draw from stock
		2) if the top of the discard pile can not be used to make a meld
			then draw from the stock
		3) create a temporary copy of this player
		4) simulate picking up the discard pile and make as much meld as
			possible.
		5) if the number of canasta increases after step (4) then pick up
			the pile
		6) if the number of points is less after setp (4) then draw from
			stock
		7) if the the number of points increases by 4 when the size of
			discard pile is <= 5 then pick up the pile
		8) if the the number of points increases by 1 when the size of
			discard pile is > 5 then pick up the pile
		9) draw a card
Assistance Received: none
********************************************************************* */
std::pair<std::pair<unsigned, std::vector<unsigned>>, std::string> Computer::TurnStartHelp( const std::vector<Card>& a_discardPile )
{
	// at the start of the turn, computer has 2 choices:
	//	1) draw a card from deck -> enter 2
	//	2) pick up the discard pile -> enter 3

	// chekcing if hte pile is frozen
	if( a_discardPile.front().GetCardType() != ENUM_CardType::CARDTYPE_natural )
	{
		// we can not pick up the pile as it is frozen
		return { {2,{2}}, "Can not pick up the pile as it is frozen. So draw card from the stock." };
	}

	bool canPickup = CanPickUpDiscardPile( a_discardPile );

	if( !canPickup )
	{
		// we can not meld the stack so our only option is to draw
		return { {2,{2}}, "Can not use top of the discard pile to make a meld. So draw a card from the stock." };
	}

	// creating a temp computer and making it pick up the discard pile
	// and doing as much meld as we can
	Computer tempComputer( *this );

	// simulation picking up the pile
	tempComputer.PickUpDiscardPile( a_discardPile );

	// keeping track of if we can make a canasta
	unsigned preCanastaCount = 0;
	for( unsigned meldIdx = 0; meldIdx < tempComputer.GetMelds().size(); ++meldIdx )
	{
		// counting the number of casansta
		if( tempComputer.GetMelds().at( meldIdx ).size() >= 7 )
		{
			++preCanastaCount;
		}
	}

	// looping over the card in the hand and seeing if we can meld any thing
	// if yes the meld it
	for( unsigned handIdx = 0; handIdx < tempComputer.GetActualHand().size(); ++handIdx )
	{
		// check for meld 
		auto canMeldResult = tempComputer.CanAddToMeld( tempComputer.GetActualHand().at( handIdx ) );

		// if meldable then meld it
		if( canMeldResult.first != -1 )
		{
			tempComputer.AddToMeld( handIdx, canMeldResult.first );
		}
	}

	// chekcin if a canasta was made
	unsigned postCanastaCount = 0;
	for( unsigned meldIdx = 0; meldIdx < tempComputer.GetMelds().size(); ++meldIdx )
	{
		// counting the number of casansta
		if( tempComputer.GetMelds().at( meldIdx ).size() >= 7 )
		{
			++postCanastaCount;
		}
	}

	// pick up the pile if the number of canasta was increased
	if( postCanastaCount > preCanastaCount )
	{
		return { {2,{3}}, "If the discard pile is picked up, by the end of the turn the number of canasta in the hand increases." };
	}

	// now we compare how much point did we gain or lost
	if( TallyHandPoint() >= tempComputer.TallyHandPoint() )
	{
		return { {2,{2}}, "Draw from the stock as if discard pile is picked up, it will decrease the current hand points." };
	}

	// we know that the hand point will end up increasing 
	// but by how much. what is the average gain in point?
	if( a_discardPile.size() <= 5 && ( tempComputer.TallyHandPoint() - TallyHandPoint() ) / a_discardPile.size() > 4 )
	{
		return { {2,{3}}, "If the discard pile is picked up, by the end of the turn on average each card will add 4 points." };
	}

	if( a_discardPile.size() > 5 && ( tempComputer.TallyHandPoint() - TallyHandPoint() ) / a_discardPile.size() > 1 )
	{
		return { {2,{3}}, "If the discard pile is picked up, by the end of the turn on average each card will add 1 points." };
	}

	return { {2,{2}}, "Draw from the stock as there is nothing special about the discard pile for now." };
}

/* *********************************************************************
Function Name: TurnContinueHelp
Purpose: Decides what to do in the turn continue menu. It choses between
		to pick up the discard pile and drawing
Parameters:
			a_discardPile, a const vector of cards that contains the
				discard pile
Return Value:
			<pair of <pair of <integer ,  std::vector<unsigned>>, string>.
			The inside pair contains the current submenu index which is 3
			and the choice. The out side pair's second contains the
			reasoning behind its choice.
Algorithm:
		1) if the top of the discard pile is frozen then draw from stock
		2) if the top of the discard pile can not be used to make a meld
			then draw from the stock
		3) create a temporary copy of this player
		4) simulate picking up the discard pile and make as much meld as
			possible.
		5) if the number of canasta increases after step (4) then pick up
			the pile
		6) if the number of points is less after setp (4) then draw from
			stock
		7) if the the number of points increases by 4 when the size of
			discard pile is <= 5 then pick up the pile
		8) if the the number of points increases by 1 when the size of
			discard pile is > 5 then pick up the pile
		9) draw a card
Assistance Received: none
********************************************************************* */
std::pair<std::pair<unsigned, std::vector<unsigned>>, std::string> Computer::TurnContinueHelp( const std::vector<std::vector<Card>>& a_otherPlayerMeld,
																							   const std::vector<Card>& a_discardPile )
{
	// TODO (BUG): this whole fuction is deeply bugged and Ai is pretty bad see other TODO comments.

	// now player have 6 choices until they discard or go out:
	// else it is not the start of the round so they have 5 choices
	//	4) Go out -> enter 4
	//	2) Add a card in hand to meld -> enter 2 <actualHandCardIdx> <meldIdx>
	//	5) Make a new meld no wildcard-> enter 5 <actualHandCardIdx> <actualHandCardIdx> <actualHandCardIdx> ...
	//	5) Make a new meld yes windcard-> enter 5 <actualHandCardIdx> <actualHandCardIdx> <actualHandCardIdx> ...
	//	8) Take out wild card From meld -> enter 8 <meldCardIdx> <meldIdx>
	//	3) Discard a card from hand -> enter 3 <actualHandCardIdx>

	// check if the player can go out
	if( CanGoOut() )
	{
		return { {3,{4}}, "Can go out and finish the round" };
	}

	// TODO (BUG): The program crashs if the hand is empty and computer cannot go out nor discard

	// looping over the card in the hand and seeing if we can meld any thing
	// if yes the meld it
	for( unsigned handIdx = 0; handIdx < GetActualHand().size(); ++handIdx )
	{
		// check for meld 
		auto canMeldResult = CanAddToMeld( GetActualHand().at( handIdx ) );

		// if meldable then return saying meld
		if( canMeldResult.first != -1 )
		{
			return { {3,{2,handIdx}}, "Can meld the card at index " + std::to_string( handIdx ) + " to the meld at index " + std::to_string( canMeldResult.first ) };
		}
	}

	// divinging out cards at hand according to its rank
	std::vector<std::vector<Card>> sameRankHandCardList = GetDividedAcualHandCardList();

	// checking if we have a wildcard
	bool hasWildCard = ( sameRankHandCardList.back().front().GetCardType() == ENUM_CardType::CARDTYPE_wildCard );

	// checking if the there is any rank that has 3 cards in them or has 2 card and we have a wild card at hand
	for( unsigned sameRankCardIdx = 0; sameRankCardIdx < sameRankHandCardList.size(); ++sameRankCardIdx )
	{

		if( sameRankHandCardList.at( sameRankCardIdx ).size() >= 3
			|| ( sameRankHandCardList.at( sameRankCardIdx ).size() == 2 && hasWildCard ) )
		{
			// only procede if we are dealing with natural card
			if( sameRankHandCardList.at( sameRankCardIdx ).front().GetCardType() != ENUM_CardType::CARDTYPE_natural )
			{
				continue;
			}

			// calculating the indexs 
			unsigned idxOfFirstCard = 0;

			for( unsigned newSameRankCardListIdx = 0; newSameRankCardListIdx < sameRankCardIdx; ++newSameRankCardListIdx )
			{
				idxOfFirstCard += sameRankHandCardList.at( newSameRankCardListIdx ).size();
			}

			std::string allIndex = "";
			std::vector<unsigned> result;
			result.reserve( sameRankHandCardList.at( sameRankCardIdx ).size() + 1 );
			result.push_back( 5 );

			if( sameRankHandCardList.at( sameRankCardIdx ).size() == 2 )
			{
				// pushing back the index of wildcar
				allIndex = std::to_string( GetActualHand().size() - 1 ) + " ";
				result.push_back( GetActualHand().size() - 1 );

			}

			for( unsigned thisListIdx = 0; thisListIdx < sameRankHandCardList.at( sameRankCardIdx ).size(); ++thisListIdx )
			{
				allIndex += std::to_string( idxOfFirstCard + thisListIdx ) + " ";
				result.push_back( idxOfFirstCard + thisListIdx );
			}


			return { {3, result}, "Can make a new meld with the cards at indexs--" + allIndex };
		}
	}

	hasWildCard = false;
	unsigned wildCardMeldIdx = 0;
	const std::vector<std::vector<Card>> melds = GetMelds();
	// if a meld is more than 3 and it has a wild card then test for any 2 cards of same rank in actual hand

	// checking for any wildcards in a meld where teh meld size is more than 3
	// if yes we can safly take the wild card out
	for( unsigned meldIdx = 0; meldIdx < melds.size(); ++meldIdx )
	{
		if( melds.at( meldIdx ).size() > 3
			&& melds.at( meldIdx ).back().GetCardType() == ENUM_CardType::CARDTYPE_wildCard )
		{
			hasWildCard = true;
			wildCardMeldIdx = meldIdx + 1;
			break;
		}
	}

	// checking if we have any ranks with 2 cards in them
	if( hasWildCard )
	{
		for( unsigned sameRankCardIdx = 0; sameRankCardIdx < sameRankHandCardList.size(); ++sameRankCardIdx )
		{
			if( sameRankHandCardList.at( sameRankCardIdx ).size() == 2 &&
				sameRankHandCardList.at( sameRankCardIdx ).front().GetCardType() != ENUM_CardType::CARDTYPE_wildCard )
			{
				// calculating the indexs 
				unsigned idxOfFirstCard = 0;

				for( unsigned newSameRankCardListIdx = 0; newSameRankCardListIdx < sameRankCardIdx; ++newSameRankCardListIdx )
				{
					idxOfFirstCard += sameRankHandCardList.at( newSameRankCardListIdx ).size();
				}

				// to get the index
				idxOfFirstCard;
				std::string allIndex = "";
				std::vector<unsigned> result;
				result.reserve( sameRankHandCardList.at( sameRankCardIdx ).size() + 1 );

				// adding sub menu code
				result.push_back( 8 );

				// adding the card index in the meld
				unsigned wildCardIdx = melds.at( wildCardMeldIdx ).size() - 1;
				result.push_back( wildCardIdx );
				// adding the meld Idx
				result.push_back( wildCardMeldIdx );

				for( unsigned thisListIdx = 0; thisListIdx < sameRankHandCardList.at( sameRankCardIdx ).size(); ++thisListIdx )
				{
					allIndex += std::to_string( idxOfFirstCard + thisListIdx ) + " ";
				}

				std::string message = "Take out the wild card at index " + std::to_string( wildCardIdx );
				message += " from the meld at index " + std::to_string( wildCardMeldIdx );
				message += "\noAnd, this wildcard and the cards at index " + allIndex + "from the actual hand";
				message += "can be melded into a new one";

				return { {3, result}, message };
			}
		}
	}

	// we can be sure that there are no 2 cards with same rank and have a wild card in the hand 
	// so add the wild cards to the melds with largest size 
	// checking if we have a wildcard in hand 
	hasWildCard = ( sameRankHandCardList.back().front().GetCardType() == ENUM_CardType::CARDTYPE_wildCard );

	/*
		TODO (BUG): curretnly For making a meld, the Ai recommend to add into a wildcard into a meld which alread has 3 wildcards in it.
			So in the Ai decision it need to consider if the meld already has a 3 wildcard or not.
			If the meld has 3 wildcards in it it should not recommend adding a wild card into it.
			One way to do this would be as the wild card is added to the largest meld. choses the next largest meld.
			again this needs to consider what if there are no other melds other than the meld which has 3 wild card in it.
	*/

	unsigned largestMeldIdxToAddWC = 0;

	if( hasWildCard )
	{
		Card wildCard = sameRankHandCardList.back().front();
		// checking if we can add a wild card to a meld and tracking the largest valid meld
		for( unsigned meldIdx = 0; meldIdx < GetMelds().size(); ++meldIdx )
		{
			Computer tempComp( *this );

			// trying to add the wild card to each meld
			auto melds = tempComp.GetMelds();
			auto actualHand = tempComp.GetActualHand();

			auto addResult = tempComp.AddToMeld( actualHand.size() - 1, meldIdx + 1 );

			if( ( addResult.first ) )
			{
				// success
				//compare the length
				if( melds.at( meldIdx ).size() - 1 > melds.at( largestMeldIdxToAddWC ).size() )
				{
					largestMeldIdxToAddWC = meldIdx;
				}
			}
		}
		std::vector<unsigned> result;
		result.push_back( 2 );
		result.push_back( GetActualHand().size() - 1 );
		result.push_back( largestMeldIdxToAddWC + 1 );

		std::string message = "Add the the wild card at index " + std::to_string( GetActualHand().size() - 1 );
		message += " to the meld at index " + std::to_string( largestMeldIdxToAddWC + 1 );
		message += "\nThis allows for mamimum chances of getting a canasta";

		return { {3, result}, message };
	}

	// discarding a card
	// for now discard a card that we have only one of
	for( unsigned sameRankCardIdx = 0; sameRankCardIdx < sameRankHandCardList.size(); ++sameRankCardIdx )
	{
		if( sameRankHandCardList.at( sameRankCardIdx ).size() == 1 )
		{
			// calculating the indexs 
			unsigned idxOfFirstCard = 0;

			for( unsigned newSameRankCardListIdx = 0; newSameRankCardListIdx < sameRankCardIdx; ++newSameRankCardListIdx )
			{
				idxOfFirstCard += sameRankHandCardList.at( newSameRankCardListIdx ).size();
			}

			// to get the index
			idxOfFirstCard;

			return { {3, {3,idxOfFirstCard }}, "Discard the card at index: " + std::to_string( idxOfFirstCard ) + " as card that is largest single card" };

		}
	}

	return { {3, {3, 0}}, "Discard a card that is largest" };

}