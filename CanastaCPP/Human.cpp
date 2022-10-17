/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "Human.h"

/* *********************************************************************
Function Name: operator=
Purpose: To deep-copy the passed Human object's member variables data into
		this Human object
Parameters:
			a_other, a constant object of Human class passed by reference.
				It holds a Human object that is used to assign this
				Human object.
Return Value: its own memory address
Algorithm:
			1) call player's assignemnt operator
			3) copy the m_totalPoint
Assistance Received: none
********************************************************************* */
Human& Human::operator=( const Human& a_other )
{
	// checking for self assignment
	if( this == &a_other )
	{
		return *this;
	}

	Player::operator=( a_other );

	return *this;
}

