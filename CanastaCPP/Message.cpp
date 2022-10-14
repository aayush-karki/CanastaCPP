#include "Message.h"


// declaring the message list 
std::vector<std::string> Message::m_messages;

/* *********************************************************************
Function Name: AddMessage
Purpose: To adds the passed message to the back of the message list
Parameters:
			a_messageToAdd, a string passed by valuee. It holds
				message that is to be the message list.
Return Value: true to indicate a success
Algorithm:
			1) push_back the message to the back of message list
Assistance Received: none
********************************************************************* */
bool Message::AddMessage( std::string a_messageToAdd )
{
	m_messages.push_back( a_messageToAdd );

	return true;
}

/* *********************************************************************
Function Name: ClearMessages
Purpose: To clears the  message list
Parameters: none
Return Value: true to indicate a success
Algorithm:
			1) call clear funciton on message list
Assistance Received: none
********************************************************************* */
bool Message::ClearMessages()
{
	m_messages.clear();

	return true;
}

/* *********************************************************************
Function Name: PrintMessages
Purpose: To print out all the message in the
		message vector.
Parameters: none
Return Value: none
Algorithm:
			1) for all the messages in the message vector print them
Assistance Received: none
********************************************************************* */
void Message::PrintMessages()
{
	if( !m_messages.empty() )
	{
		for( std::string message : m_messages )
		{
			std::cout << message << std::endl;
		}
		
		std::cout << std::endl;
	}
}

