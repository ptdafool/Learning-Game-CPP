using namespace std;
#include "Headers\ConOut.h"

char ConMsgOut(char message);

char ConMsgOut(char message)
{
	AllocConsole();
	char* lpBuff = &message;
	DWORD dwSize = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), lpBuff, lstrlen(lpBuff), &dwSize, NULL);
	return ConMsgOut(message);
}


// to figure out why we're getting 'unable to convert const char* to LPCSTR' message when implementing this.  Looks fine here.