/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <vector>
#include <string>
#include <iostream>

class Message
{
public:

	// push backs the message to the end of the message list
	static bool AddMessage(std::string a_messageToAdd);

	// clears the message list
	static bool ClearMessages( );

	// print function to print all the message in the 
	// message vector. This prints the message and clears
	// the message list 
	static void PrintMessages();

private:
	// m_messages holds the messages that player might need 
	// as a result of their action
	static std::vector<std::string> m_messages;
};

