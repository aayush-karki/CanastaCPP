# Canasta In CPP
Canasta ("basket" in Spanish) is a card game played by 2 players.

## The Objective
The objective of this game is to score the most points after all the rounds.

## The Players
In this implemantaion of canasta, a player ( user ) playes against computer.

## The Decks
Two decks are used. Each deck contains the standard 52 cards plus 2 Jokers. So, a total of 108 cards are used. 

The cards themselves are of three types:
- Natural cards: Cards A, K, Q, J, 10, 9, 8, 7, 6, 5, 4.
- Wild cards: Deuces (2) and Jokers - these can be used as any rank except as 3.
- Threes:
  - Red 3s (Heart, Diamond) are bonus cards. They can never be part of any meld. They cannot be discarded.
  - Black 3s (Spades, Clubs) can be part of a meld containing only black 3s (and no wildcards). They can also be used to freeze the discard pile. 

## Layout 
The game layout consists of a hand for each player, a stock pile and a discard pile.

## A Round

### Round Set Up
A round is set up as follows:
- The two decks are shuffled together.
- 15 cards are dealt to each player.
  - For each red 3 dealt to a player, the player picks up a replacemeent card from the stock pile. 
- The next card is placed face up on the table to form the discard pile.
  - If the next card happens to be a wild card or red 3, additional cards are drawn from the stock and added to the discard pile till a natural card or black 3 is at the top of the discard pile. 
- The remaining cards are left in the stock pile, face down. 

### Determining Player Order
After set up, the first player on the first turn is determined as follows:
- On the first round, a coin is tossed and the human player is asked to call the toss. If the call is correct, the human player plays first. Otherwise, computer plays first.
- On subsequent rounds, the player with the most points from previous rounds plays first. If there is a tie in points, the first player is determined using the mechanism described above for the first round. 

### Round End Condition
The two players take turns until:
- One of the players "goes out".
- The last card from the stock pile drawn by a player is a red 3 (since no replacement card is available to continue the turn).
- The stock pile is empty and neither player can use the top card of the discard pile to create a meld or add to a meld (either because the top card of the discard pile is not of the same rank or the discard pile is frozen).
  - In this situation, if a player can use the top card of the discard pile to create or add to a meld, the player must do so. 

### Going Out
A player can go out if all the following are true:
- The player has created a canasta (a meld of at least 7 cards).
- The player has created melds out of the remaining cards.
  - The player can, but does not need to discard a card when going out. 

## A Turn
During a turn, each player plays as follows:
- Drawing From stock pile or discard pile
- Melding 
- Going out or discarding

### Drawing From Stock Pile Or Discard Pile
The player draws card(s) in one of two ways:
- The player draws the top card from the stock pile.
  - If the card is a red 3, the player keeps it and draws a replacement card from the stock pile. 
- If the player can use the top card of the discard pile to create a new meld or add to an existing meld, the player can pick up the entire discard pile.
  - **Note** that the player can pick up the discard pile only if the top card is a natural card, i.e., the pile is not frozen. 
    
### Melding
The player either creates a new meld with the drawn card(s) or adds to existing melds.

The rules for melds are as follows:
- A meld must contain at least 3 cards.
  - A meld of at least 7 cards is a canasta.
- At least two cards in a meld must be natural cards of the same rank, e.g., two 7s of any suit.
- At most 3 cards in a meld can be wild cards (2s and Jokers).
- A player can have only one meld of a given rank. 

**Note** that a player's melded cards and red 3s will be visible to the opponent, but not the player's cards that are not in a meld.

### Discard
The player discards a card to the top of the discard pile, face up.

If the player discards a wild card or black 3 to the discard pile, the discard pile is frozen. In this case, Neither player can pick up the discard pile until a natural card is added to the discard pile in a subsequent turn. 

## Score
The point values of cards are as follows:
- Card 	Points
- 4, 5, 6, 7. Black 3 	5
- 8, 9, 10, J, Q, K 	10
- 2, A 	20
- Joker 	50
- Red 3 	100

When a round ends, each player earns points as follows:
- Add points for all the cards in all the melds;
- Add bonus points for red 3 cards;
- If a player goes out, the player earns another 100 points bonus;
- Add 500 bonus points for a canasta made of only natural cards and 300 bonus points for a canasta that contains wildcards;
- Subtract points for all the cards in hand not in a meld. 

## A Game
A game consists of as many rounds as the human player wants to play. The human player is asked before each round whether the player wants to play another round.

- If the human player replies yes, another round is started.
- If the human player replies no, the game is ended and the player with the most points is declared the winner of the game. 
