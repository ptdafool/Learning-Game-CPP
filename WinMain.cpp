//#include "Headers\WindowsMessageMap.h"

#include "Headers\WinExcludes.h"
#include <optional>
#include "Headers\ExceptionHandler.h"
#include "Headers\ConOut.h"
//#include "Headers\app.h"
//#include <iostream>

//#include "Headers\Keyboard.h"
//#include "Headers\Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ConsoleMSGOut conMsg;
	switch (msg)
	{
	case WM_SYSKEYUP:
	case WM_SYSKEYDOWN:
	case WM_CHAR:
		conMsg.ConMSGOut("Character pressed.");
		break;
	case WM_MOUSEMOVE:
		conMsg.ConMSGOut("Mouse moved");
		break;
	case WM_CLOSE:
		conMsg.ConMSGOut("Quit Received");
		Sleep(5000);
		PostQuitMessage(69);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//main function - this is the entry point.  Used prefixes _In_ and so on for required consistency in CALLBACK calling method.
int CALLBACK WinMain(
	_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		LPSTR		lpCmdLine,
	_In_		int			nShowCmd) 
{
	try
	{
		const auto pClassName = "Some Shitbox";
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = pClassName;
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		HWND hWnd = CreateWindowEx(
			0, pClassName, "Some Shitbox",
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX,
			200, 200, 640, 480,
			nullptr, nullptr, hInstance, nullptr);
		ShowWindow(hWnd, SW_SHOW);

		MSG msg;
		BOOL gResult;
		while((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (gResult == -1)
		{
			return -1;
		}
		else
		{
			return msg.wParam;
		}
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