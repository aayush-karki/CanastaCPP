# Canasta In C Plus Plus Log

## Sep 8, 2022:
- Read and tried to understand the cansata game rules, beanchmarks and other 
	guidelines ( 1.5 hours ).

###### Total: 1.5 hours

## Sep 9, 2022:
- Played multiple games of online canasta from the web to understand and 
	analyse the game. Used the site https://www.cardzmania.com/games/Canasta 
	to campare how its and ours rules differ ( 1 hour and 30 minutes ).

- Read the rubric that was uploaded to the course site and tried to 
	understand it ( 30 minutes ).

- Started a rough draft of class design for the project. Finished 
	the rough draft of card, and deck classes ( 45 minutes ).

###### Total: 2 hours and 45 minutes

## Sep 10, 2022:
- Drafted a rough design for hand class (30 minutes).

- Drafted a rough class design for player, human, and computer classes 
	( 1 hour and 15 minutes ).

- Drafted a rough design for round, and game classes ( 1 hour ).

###### Total: 2 hours and 45 minutes

## Sep 11, 2022:
- Cleaned the rough designed while cross checking with the guidelines 
	( 1 hour and 30 minutes ).

- Played a games of online canasta from https://www.cardzmania.com/games/Canasta 
	to analysis how my class design would fit in the game ( 30 minutes ).

- Created a Visual studio project, started to code the game and set up source 
	control. Created the canasta class and the round class then populated them 
	with funciton declaration and member variables while following the class 
	designs. Also created a class files with class declaration for player class,
	card class, and deck class so that the program compiles (45 minutes).

- Created a enum class called ENUM_CardType to indicate the different card type 
	in a deck ( 15 minutes ).

- Populated the card class with its member variables and member funciton. Tested
	the class. ( 1 hour )

###### Total: 4 hours

## Sep 12, 2022:

- Changed the Card class constructor to accept only two parameter because the 
	point for the card and the type of the card depend on the rank and suit of
	the card ( 30 minutes ).

- Populating the deck class with its constructor and destructor. After
	researching for copy constructor decided to change the data structure 
	for m_stock and m_dealt to vector instead of stack. Copying stack as 
	it was had many steps and the benifit of stack--first in and first out-- was 
	was not worth the trouble ( 1 hour 30 minute ).

- Populating the deck class with its copy constructor and assignment 
	constructor. Researched deep copy and assignment constructor 
	( 1 hour and 30 minutes).

- Populating the deck class with getter function created a Shuffel, DealCard,
	PrintDeck and Cosolidate function.
	( 1 hour ).

###### Total: 4 hours 30 minutes

## Sep 13, 2022:

- Designed an algorithm for Deck constructor when a m_stock is passed as string. 
	Created operator overload for Card Class ( 1 hours 30 minutes ).

- Tested and debugged the Card Class's overloaded operators. Fixed a lhs and 
	rhs mixup, and added a one more logical check for < operator ( 1 hour ).

- Created Deck constructor when m_stock is passed. Refined the design of its 
	algorithm, and tested it. Fixed the bug where the swapping was happening
	with the start of the deck insead of last as we deal the card from the 
	back of the m_stock list ( 2 hour ).

- Set up Hand and player class ( 15 minutes ). 

- Created hand's default constructor. Designed and created an algorithm for
	the hand constructor when a string is passed as hand and a string 
	is passed as melds. In the process created a card constructor that accepts 
	a rank and suit as a parameter ( 1 hour and 30 minutes ).

- Moved the constant rankList and suitList member variable of the Deck Class 
	to a struct name ST_ValidRankList in the "Card.h" file. Created its default
	constructor, and function to check if the passed rank, or suit, or rankSuit 
	is valid or not. in the process found a bug that was overlooked previously
	where the copy constructor was seted up incorred as a result of not testing
	the class properly ( 1 hour ).

- Researched exception handeling and how to make CustomException ( 1 hour ). 

###### Total: 8 hours 15 minutes

## Sep 18, 2022:

- In the process of hand's constructor when a string is passed as hand
	and a string is passed as melds found previously designed algorith to be
	insufficent. So redesigned and implement a new algorithm. Created a 
	PrintHand() funciton to print the hand ( 1 hour and 30 minutes ).

- Created copy contructor and destructor for the hand class ( 30 minutes ).

- Designed and implemented algorithm for aAddCardToMeld funciton. 
	Tested and debugged it ( 1 hour and 30 minutes ).

- Filled the Hand Class with the designed funciton definations and created 
	the declaration for inline functions ( 1 hour and 15 minutes ). 

- Changed the AddCardToMeld funciton to be more generic and made it into
	a private helper function. Designed and implemented AddNaturalCardToMeld(),
	AddWildCardToMeld(), AddRed3CardToMeld() ( 1 hour and 15 minutes )

- Designed, implement, tested and debugged MakeMeld() function. Adjusted 
	AddCardToMeld() funciton to be more generic by added more or conditions
	to its main if logic ( 1 hour ).

- Created TakeOutWildCard(), Discard(), SwaphandPos(), tallyPoints() functions.
	( 1 hour ).

- Finished the Hand class and did a final test and pushed to github 
	( 1 hour and 15 minutes )

###### Total: 8 hours 45 minutes
