/*  *** excluded headers ***
//#include "Headers\WindowsMessageMap.h"
#include "Headers\app.h"
#include <iostream>
#include "Headers\Keyboard.h"

*/
#include "Headers\Window.h"
#include "Headers\WinExcludes.h"
#include "Headers\ConOut.h"
#include "Headers\ExceptionHandler.h"
#include <sstream>


//main function - this is the entry point.  Used prefixes _In_ and so on for required consistency in CALLBACK calling method.
int CALLBACK WinMain(
	_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		LPSTR		lpCmdLine,
	_In_		int			nShowCmd) 
{
	try
	{
		Window wnd(800, 300, "Some Shitbox");
		ConsoleMSGOut conMsg;
		conMsg.ConMSGOut("Starting Up...\n"); 
		MSG msg;
		BOOL gResult;
		while((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				conMsg.ConMSGOut("Something Happon msg box shown.\n");
				MessageBox(nullptr, "Something Happon!", "Space Key Was Pressed", MB_OK | MB_ICONEXCLAMATION);
			}
		}
		if (gResult == -1)
		{
			return -1;
		}
		return msg.wParam;
		//return App{}.Go();
	}
	catch (const ExceptionHandler& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}
