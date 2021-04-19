#pragma once
#include <consoleapi.h>
#include <processenv.h>
#include <winbase.h>
#include <string>
class ConsoleMSGOut
{
public:
	ConsoleMSGOut(char message);
private:
	ConsoleMSGOut(char message)
	{}
};