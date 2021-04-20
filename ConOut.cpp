#include "Headers\ConOut.h"

// This works using the string type.  
//This function requires handle to console window,
//  message(DWORD), size(UINT), and the remaining 
// parameters are NULL (or nullptr - either way) as per Microsoft specification.  
// Now, a message can be received by this class and output to a console window.

// receives a string, Outputs to console. std::string (and <iostream> at a minimum) are required.

std::string ConsoleMSGOut::ConMSGOut(std::string message)
{
	AllocConsole();
	std::string messageString = message;
	DWORD dwSize = 0;
	WriteConsole(
		GetStdHandle(STD_OUTPUT_HANDLE), 
		message.c_str(), 
		message.size(), nullptr, nullptr);  
	return message;
}
