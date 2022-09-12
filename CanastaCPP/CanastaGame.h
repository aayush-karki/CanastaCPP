/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include "Round.h"

class CanastaGame
{
public:
    // default contructor
    CanastaGame();

    // default destructor
    ~CanastaGame();

private:
    Round m_round;

};

/* *********************************************************************
Function Name: compute
Purpose: To calculate the average grade in a class
Parameters:
            grades[], an array passed by value. It holds individual grades
            size, an integer. It refers to the number of students in the class
Return Value: The average grade in the class, a real value
Algorithm:
            1) Add all the grades
       2) Divide the sum by the number of students in class to calculate the average
Assistance Received: none
********************************************************************* */